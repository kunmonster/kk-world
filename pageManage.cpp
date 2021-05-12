#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

//物理块类
class PCB {
 private:
  std::vector<int> currentPage;

 public:
  PCB(int size) {
    //为物理块分配大小
    //参数size为物理块的大小
    this->currentPage.resize(size);
  }
  void push(int pageindex, int index) {
    //将页号写入物理块(模拟内存)
    //参数为[pageindex,index]
    // pageindex:页号
    // index:页号在物理块中的位置索引

    this->currentPage[index] = pageindex;
  }
  void pop(int index) {
    //弹出页面(根据策略)
    //弹出根据算法选定的换出的页面
    // index:要删除的位置索引
    this->currentPage.erase(this->currentPage.begin() + index);
  }
  int getSize() {
    //获取物理块大小的接口
    return this->currentPage.size();
  }
  std::vector<int> getCurrent() {
    //获取当前物理块
    return this->currentPage;
  }
  ~PCB();
};

//最佳置换算法类
class OPT {
  //测试通过
 private:
  //存放所有页面
  std::vector<int> AllPage;

  //使用map存放每个元素的下一次访问时间
  std::map<int, int> nexttime;
  PCB* pcb;

 public:
  OPT(std::vector<int> AllPage, int size) {
    //构造函数
    // AllPage:用户输入的页号序列
    this->AllPage = AllPage;  //传入所有页面序列
    this->pcb = new PCB(size);

    for (int i = 0; i < size; i++) {
      //根据物理块的大小将页号传入
      this->pcb->push((this->AllPage[i]), i);
    }
    for (int i = 0; i < size; i++) {
      this->AllPage.erase(this->AllPage.begin());
    }
  }

  void replace() {
    //将当前物理块中的下一次调度时间最远的页号置换出物理块
    while (!this->AllPage.empty()) {
      auto pcb_tmp = this->pcb->getCurrent();
      int allsize = this->AllPage.size();
      for (int i = 0; i < pcb_tmp.size(); i++) {
        if (std::find(this->AllPage.begin(), this->AllPage.end(), pcb_tmp[i]) ==
            this->AllPage.end()) {
          //在所有页面索引中，没有当前的页号，在map中将此页号的下一次出现的最早时间设为极大
          this->nexttime.insert(std::pair<int, int>(pcb_tmp[i], 100000));
        } else {
          for (int j = 0; j < allsize; j++) {
            if (this->AllPage[j] != pcb_tmp[i]) {
              continue;
            } else {
              this->nexttime.insert(std::pair<int, int>(pcb_tmp[i], j));
            }
          }
        }
      }
      //用于比较的下一次最早访问时间
      int replace_value = 0;
      //需要换换出换入位置的索引
      int replace_index = 0;
      //物理块的大小
      int size = pcb_tmp.size();

      for (int i = 0; i < size; i++) {
        int tmp = this->nexttime[pcb_tmp[i]];
        //将下一次调度时间最晚的进程在物理块的索引赋值给replace_index
        if (replace_value < tmp) {
          replace_value = tmp;
          replace_index = i;
        }
      }
      //将nexttime清空
      this->nexttime.erase(this->nexttime.begin(), this->nexttime.end());

      // this->pcb->pop(replace_index); //换出操作。再换入下一个进程需要的页面
      if (std::find(pcb_tmp.begin(), pcb_tmp.end(), this->AllPage.front()) ==
          pcb_tmp.end()) {
        this->pcb->push(this->AllPage.front(), replace_index);
      }
      //从所有页面索引中删除元素
      this->AllPage.erase(this->AllPage.begin());
    }
  }
  ~OPT();
};

// FIFO先进先出页面置换类
class FIFO {
  //测试完成
 private:
  std::vector<int> AllPage;  //所有页号索引
  std::queue<int> CurrentPages;

 public:
  FIFO(std::vector<int> AllPage, int size) {
    this->AllPage = AllPage;
    for (int i = 0; i < size; i++) {
      this->CurrentPages.push(this->AllPage.front());
      this->AllPage.erase(this->AllPage.begin());
    }
  }
  void replace() {
    while (!this->AllPage.empty()) {
      int allsize = this->AllPage.size();
      int size = this->CurrentPages.size();
      bool tag = false;  //在当前物理块中是否存在的标志
      for (int i = 0; i < size; i++) {
        if (this->AllPage.front() == this->CurrentPages.front()) {
          tag = true;
          break;
        }
        this->CurrentPages.push(this->CurrentPages.front());
        this->CurrentPages.pop();
      }
      if (!tag) {
        this->CurrentPages.pop();
        this->CurrentPages.push(this->AllPage.front());
      }
      this->AllPage.erase(this->AllPage.begin());
    }
  }
  ~FIFO();
};

class LRU {
 private:
  std::vector<int> AllPage;
  std::stack<int> CurrentPage;  //当前物理块中页面索引
  int size;

 public:
  LRU(std::vector<int> AllPage, int size) {
    this->AllPage = AllPage;
    this->size = size;
    for (int i = 0; i < size; i++) {
      if (this->CurrentPage.empty()) {
        this->CurrentPage.push(this->AllPage.front());
        this->AllPage.erase(this->AllPage.begin());
      } else {
        auto tmp = this->CurrentPage;
        bool tag = true;
        for (int k = 0; k < this->CurrentPage.size(); k++) {
          if (this->AllPage.front() == tmp.top()) {
            for (int j = 0; j < (k+1); j++) {
              tmp.push(this->CurrentPage.top());
              this->CurrentPage.pop();
            }
            tmp.pop();
            for (int j = 0; j < (k+1); j++) {
              this->CurrentPage.push(tmp.top());
              tmp.pop();
            }
            tag = false;
            break;
          } else {
            tmp.pop();
            continue;
          }
        }
        if(tag){
          //当前不存在，那么删除栈底的，再进行push
          if(this->CurrentPage.size() == this->size){
          std::stack<int> tmp;
          int tmpsize = this->CurrentPage.size();
          for(int i=0;i<tmpsize-1;i++){
           tmp.push(this->CurrentPage.top());
           this->CurrentPage.pop();
          }
          this->CurrentPage.pop();
          int tmp_size = tmp.size();
          for(int j = 0;j<tmp_size;j++){
            this->CurrentPage.push(tmp.top());
            tmp.pop();
          }
          }
          this->CurrentPage.push(this->AllPage.front());
        }
        this->AllPage.erase(this->AllPage.begin());
        continue;
      }
    }
  }

  void replace() {
    
    while (!this->AllPage.empty()) {
    auto tmpstack = this->CurrentPage;
    bool del_tag = true;

      for (int i = 0; i < this->CurrentPage.size(); i++) {
        if (this->AllPage.front() == tmpstack.top()) {
          //在当前页面中存在下一个访问的页面
          for (int j = 0; j < (i+1); j++) {
            tmpstack.push(this->CurrentPage.top());
            this->CurrentPage.pop();
          }
          tmpstack.pop();
          for (int j = 0; j < (i+1); j++) {
            this->CurrentPage.push(tmpstack.top());
            tmpstack.pop();
          }
          del_tag = false;
          break;
        } else {
          tmpstack.pop();
          continue;
        }
      }
      if(del_tag){
        int size1 = this->CurrentPage.size();
        int size2 = this->size;
        if(size1 == size2){
          std::stack<int> tmp;
          int tmpsize = this->CurrentPage.size();
          for(int i=0;i<tmpsize-1;i++){
           tmp.push(this->CurrentPage.top());
           this->CurrentPage.pop();
          }
          this->CurrentPage.pop();
          int tmp_size = tmp.size();
          for(int j = 0;j<tmp_size;j++){
            this->CurrentPage.push(tmp.top());
            tmp.pop();
          }
          }
          
        this->CurrentPage.push(this->AllPage.front());
      
      }
      this->AllPage.erase(this->AllPage.begin());
    }
  }

  LRU();
  ~LRU();
};

int main() {
  int size = 5;
  std::vector<int> index;
  int num;
  while (std::cin >> num) {
    index.push_back(num);
    if (std::cin.get() == '\n')  //判断是否是回车，break跳出while循环
      break;
  }
  // OPT* op = new OPT(index, size);
  // op->replace();

  LRU* lru = new LRU(index, size);
  lru->replace();
  return 0;
}