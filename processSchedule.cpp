/*
 *funciton:使用时间片轮转法，优先级分配实现进程调度
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define MAXSIZE 20
#define DEFAULT_PRI 100  //默认优先级

enum operation { start, Kill, Block };

class PCB {
 private:
  string process_ID_ex;  //外部ID
  int process_ID_in;     //内部ID
  int status;            //进程状态
  int Priority;          //进程优先级(值越小优先级越高)
  int cpu_time;          //进程所需的时间
  int content[3];       //进程内容
 public:
  PCB() {
    cout << "请输入进程PID(可由数字和字符组成):";
    cin >> process_ID_ex;
    this->process_ID_in = rand();  //随机生成内部进程号
    cout << "请输入进程内容:";
    for (auto a : this->content) {
      cin >> a;
    }
    cout << "请输入进程所需的时间:";
    cin >> this->cpu_time;
    cout << "请输入进程优先级:";
    cin >> this->Priority;
    this->status = 1;  //默认在就绪队列(0阻塞，1就绪，2执行)
  }
  string getexID() { return this->process_ID_ex; }
  int getinID() { return this->process_ID_in; }
  void changeStatus(operation Op) {
    switch (Op) {
      case 0:
        this->status = 1;  //进入就绪队列
        break;
      case 1:
        this->status = 0;  //进入阻塞队列
      case 2:
        this->status = 2;  //执行
      default:
        break;
    }
    this->status == 1;
  }
  int getStatus() { return this->status; }
  string getstatu(int i) {
    switch (i) {
      case 0:
        return "阻塞中";
        break;
      case 1:
        return "未运行";
        break;
      case 2:
        return "正在运行";
        break;
      default:
        break;
    }
  }
  int getTime() { return this->cpu_time; }
  void setTime(int remainder) { this->cpu_time = remainder; }
  int getPri() { return this->Priority; }
  void setPri(int pri) { this->Priority = pri; }
};

void create(vector<PCB*>& Memory, queue<PCB*>& ready) {
  if (Memory.size() >= MAXSIZE)
    cout << "内存已满，请删除或挂起程序" << endl;
  else {
    if (Memory.size() == 0) {
      //内存里面没有进程，直接创建
      PCB* process = new PCB();
      Memory.push_back(process);
      ready.push(process);  //进入就绪队列
      cout << "创建成功" << endl;
    } else {
      //内存里面有进程（不能创建相同进程）
      PCB* process = new PCB();
      for (auto pro : Memory) {
        if (pro->getexID() == process->getexID()) {
          delete process;  //释放掉内存
          cout << "内存中已经存在该进程，拒绝创建!";
        } else {
          Memory.push_back(process);
          ready.push(process);  //进入就绪队列

          cout << "创建成功" << endl;
          break;
        }
      }
    }
  }
}

bool comp(PCB*, PCB*);
class processSchedule {
 private:
  queue<PCB*> ready;  //就绪队列
  // queue<PCB*>* block;  //阻塞队列
  unsigned time;

 public:
  processSchedule(queue<PCB*>& ready) {
    //构造函数，将就绪队列和阻塞队列传入
    this->ready = ready;
    this->time = 0;
  }
  void unittime() {
    cout << "请输入一个时间片:";
    cin >> this->time;
  }
  void distribution(int tag) {
    //进程调度

    if (!this->ready.empty()) {
      switch (tag) {
        case 0:
          //进程在时间片内运行完成，将进程从就绪队列中移除
          this->ready.pop();
          break;
        case 1:
          //进程在时间片内未完成，将进程放在就绪队列最后去
          this->ready.push(this->ready.front());
          this->ready.pop();
          break;
        default:
          break;
      };
    }
  }

  void timeRotation() {
    //时间轮转调度
    if (this->time == 0) {
      this->unittime();
    }
     this->showProcess();
    if (!this->ready.empty()) {
      PCB* first = this->ready.front();
      int need = first->getTime();
      int decline = this->time;
      while (need > 0 && decline > 0) {
        need--;  //所需时间减少
        decline--;  //分配的时间片减少
      }
      if (need == 0) {
        //进程在时间片内运行完成
        this->distribution(0);
        this->timeRotation();
      }
      if ((need != 0) && (decline == 0)) {
        //分配的时间片不足以完成进程将进程放到就绪队列最后
        this->ready.front()->setTime(need);
        this->distribution(1);
        this->timeRotation();
      }
     
    }
    /*是否唤起阻塞队列*/
  }
  void priority() {
    //对当前优先级队列进行排序
    //动态优先级调度
    vector<PCB*> reaArray;

    while (!this->ready.empty()) {
      reaArray.push_back(this->ready.front());
      this->ready.pop();
    }
    sort(reaArray.begin(), reaArray.end(), comp);  //对就绪队列进行优先级排序

    for (auto item : reaArray) {
      this->ready.push(item);
    }  //就绪队列已经按照优先级排好序,此时直接调用队头即可
    this->showProcess();

    this->process();
  }
  void process() {
    while (!this->ready.empty()) {
      int pri = this->ready.front()->getPri();
      int time = this->ready.front()->getTime();
      int temp = time - 1;
      if (temp == 0) {
        //将该进程移除就绪队列
        this->ready.pop();
      } else {
        this->ready.front()->setTime(temp);
        this->ready.front()->setPri(++pri);
      }
      this->priority();  //再次调度
    }
  }
  void showProcess() {
    cout << "外部进程号"
         << "\t"
         << "内部进程号"
         << "\t"
         << "\t"
         << "进程优先级"
         << "\t"
         << "进程还需时间" << endl;
    for (int i = 0; i < this->ready.size(); i++) {
      cout << setw(10) << right << this->ready.front()->getexID() << "\t"
           << setw(10) << right << this->ready.front()->getinID() << "\t"
           << setw(10) << right << this->ready.front()->getPri() << "\t"
           << setw(10) << right << this->ready.front()->getTime() << endl;
      this->ready.push(this->ready.front());
      this->ready.pop();
    }
    cout << "==============================================================="
         << endl;
  }

  ~processSchedule();
};
bool comp(PCB* pcb1, PCB* pcb2) { return pcb1->getPri() <= pcb2->getPri(); }

int main() {
  vector<PCB*> Memory;  //模拟内存
  queue<PCB*> ready;    //就绪队列
  create(Memory, ready);
  create(Memory, ready);
  create(Memory, ready);
  processSchedule* test = new processSchedule(ready);
  test->timeRotation();
  return 0;
};