/***
 * author:fkj
 * date:2021.05.11
 * operatingSystem lab  3----pageManage
 **/

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

//最佳置换算法类
class OPT {
  //测试通过
 private:
  //存放所有页面
  std::vector<int> AllPage;
  //使用map存放每个元素的下一次访问时间
  std::map<int, int> nexttime;
  std::vector<int> CurrentPages;
  int size ;
  int success=0;
  int fail = 0;

 public:
  OPT(std::vector<int> AllPage, int size) {
    //构造函数
    // AllPage:用户输入的页号序列
    this->AllPage = AllPage;  //传入所有页面序列
    this->size = size;
    this->CurrentPages;
 while (!this->AllPage.empty()) {
   if(this->CurrentPages.empty()){
     this->CurrentPages.push_back(this->AllPage.front());
     this->AllPage.erase(this->AllPage.begin());
     this->fail++;
   }
   else{
      auto pcb_tmp = this->CurrentPages;
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
      int pcb_size = pcb_tmp.size();

      for (int i = 0; i < pcb_size; i++) {
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
        if (std::find(pcb_tmp.begin(), pcb_tmp.end(), this->AllPage.front()) !=
          pcb_tmp.end()) {
        this->success++;
      }
      else{
        if(this->CurrentPages.size() == this->size){
            this->CurrentPages[replace_index] = this->AllPage.front();
            this->fail++;
        }
        else{
        this->CurrentPages.push_back(this->AllPage.front());
        this->fail++;
        }
      }
     
   
      
   
      //从所有页面索引中删除元素
      this->AllPage.erase(this->AllPage.begin());
    }

  }
  }
    float getInet(){
    return float(this->fail) / float((this->success+this->fail));
  }
  ~OPT();
};

// FIFO先进先出页面置换类
class FIFO {
  //测试完成
 private:
  std::vector<int> AllPage;  //所有页号索引
  std::queue<int> CurrentPages;
  int size;
  int success = 0;
  int fail = 0;
 public:
  FIFO(std::vector<int> AllPage, int size) {
    this->AllPage = AllPage;
    this->size = size;
    while (!this->AllPage.empty()) {
      int allsize = this->AllPage.size();
      bool tag = false;  //在当前物理块中是否存在的标志
      int cu_size = this->CurrentPages.size();
      if(size == 0){
        this->CurrentPages.push(this->AllPage.front());
        this->fail+=1;
      }
      else{

      for (int i = 0; i < cu_size; i++) {
        if (this->AllPage.front() == this->CurrentPages.front()) {
          tag = true;
          this->success++;
          break;
        }
        this->CurrentPages.push(this->CurrentPages.front());
        this->CurrentPages.pop();
      }
       if (!tag) {
         if(cu_size == this->size){
           this->CurrentPages.pop();
         }
        this->CurrentPages.push(this->AllPage.front());
        this->fail++;
      }
      }
     
      this->AllPage.erase(this->AllPage.begin());
    }
  
  }
  float getInet(){
    return float(this->fail) / float((this->success+this->fail));
  }
  ~FIFO();
};

class LRU {
 private:
  std::vector<int> AllPage;
  std::stack<int> CurrentPage;  //当前物理块中页面索引
  int size;
int success=0;
  int fail = 0;
 public:
  LRU(std::vector<int> AllPage, int size) {
    this->AllPage = AllPage;
    this->size = size;
    while(!this->AllPage.empty()) {
      if (this->CurrentPage.empty()) {
        this->fail+= 1;
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
            this->success+=1;
            break;
          } else {
            tmp.pop();
            continue;
          }
        }  
        if(tag){
          //当前不存在，那么删除栈底的，再进行push
          this->fail += 1;
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
  float getInet(){
    return float(this->fail) / float((this->success+this->fail));
  }
  ~LRU();
};

int main() {
  
  sign : std::vector<int> index;
  int num;
  std::cout<<"请输入页号序列:";

  while (std::cin >> num) {
    index.push_back(num);
    if (std::cin.get() == '\n')  //判断是否是回车，break跳出while循环
      break;
  }
  std::cout<<"请输入物理块数:";
  int size = 0;
  std::cin>>size;
  // OPT* op = new OPT(index, size);
  // op->replace();
    OPT *opt = new OPT(index,size);
    FIFO * fifo = new FIFO(index,size);
    LRU *lru = new LRU(index,size);

  while(true){
  std::cout<<"请选择置换算法:\n[1]:最佳置换算法\t[2]:先进先出算法\t\n[3]:最近最久未使用算法\t[4]:重新输入\n[5]:所有算法\t\t[6]:退出"<<std::endl;
  int choice;

    std::cin>>choice;
    switch (choice)
    {
    case 1:  
    std::cout<<"缺页率为:"<<opt->getInet()<<std::endl;
      break;
    case 2:
    std::cout<<"缺页率为:"<<fifo->getInet()<<std::endl;
    break;
    case 3:
    std::cout<<"缺页率为:"<<lru->getInet()<<std::endl;
      break;
      case 4:
      goto sign;
      break;
    case 5:
    std::cout<<"最佳置换算法缺页率为:"<<opt->getInet()<<std::endl;
    std::cout<<"先进先出算法缺页率为:"<<fifo->getInet()<<std::endl;
    std::cout<<"最近最久未使用缺页率为:"<<lru->getInet()<<std::endl;
      break;
      case 6:
      exit(0);
    }

  }
  return 0;
}