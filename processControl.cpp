/*
*funciton:实现创建进程，杀死进程，换出换入进程，唤醒，阻塞。
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAXSIZE 20

enum operation{start,kill,Suspended};



class PCB{
private:
  string process_ID_ex; //外部ID
  int process_ID_in; //内部ID
  int status;         //进程状态
  int Priority;       //进程优先级
  // int Pocess_Status;  //处理机状态
  int size;           //进程所需的时间
  int content[10];    //进程内容
public:
  PCB(){
    cout<<"请输入外部进程号(由字符和数字组成):";
    cin>>process_ID_ex;
    this->process_ID_in = rand(); //随机生成内部进程号
    cout<<"请输入进程内容:";
    for(auto a:this->content){
      cin>>a;
    }
    cout<<"请输入进程的大小:";  cin>>this->size;
    cout<<"请输入进程优先级:";  cin>>this->Priority;
    this->status = 1;   //默认在内存中(0不在内存中，1在内存中，2被挂起)
  }
  string getexID(){
    return this->process_ID_ex;
  }
  int getinID(){
  return this->process_ID_in;
  }
  void changeStatus(operation Op){
    switch (Op)
    {
    case 0:
      this->status = 1;  //进入内存
      break;
    case 1:
    this->status = 0;     //杀死
    case 2:
    this->status = 2;     //挂起
    default:
      break;
    }
    this->status == 1;
  }
  void kill(){
    this->status == 0;
  }
  int getStatus(){
   return this->status;
  }
};



vector<PCB*> Memory;     //模拟内存
queue<PCB*>  Suspended_Queen;  //挂起队列



//进程创建
void create(){
    if(Memory.size() >= MAXSIZE)
    cout<<"内存已满，请删除或挂起程序"<<endl;
    else{
      if(Memory.size() == 0){
        //内存里面没有进程，直接创建
        PCB *process = new PCB();
        Memory.push_back(process);       
        cout<<"创建成功"<<endl;
        
      }
      else{
        //内存里面有进程（不能创建相同进程）
        PCB *process = new PCB();
        for(auto pro : Memory){
          if(pro->getexID() == process->getexID()){
                delete process; //释放掉内存
                cout<<"内存中已经存在该进程，拒绝创建!";
          }
          else{
            Memory.push_back(process);
          }
        }
      }
    }
}

void showProcess(){
  if(Memory.size() == 0){
    cout<<"当前内存中无正在运行的进程";
  }
  else{}
  for(auto process : Memory){
    cout<<"外部进程号"<<"\t"<<"内部进程号"<<"\t"<<"进程状态";
    cout<<process->getexID()<<"\t"<<process->getinID()<<"\t"<<process->getStatus();
  }
}


//杀死进程
void kill(){
  int size = Memory.size();
  if(size == 0){
    cout<<"无正在运行的进程";
  }
  else{
    string PID;
    cout<<"请输入需要终止进程的PID:";cin>>PID;
    for(int i=0;i<size;i++){
      auto process = Memory[i];
      if(process->getexID() == PID){
        if(process->getStatus() == 0){
          cout<<"该进程已经不在内存当中"<<endl;
        }
        else if(process->getStatus() == 1){
          process->kill();  //将进程移出内存？此时只是将内存中进程状态改成不在内存中
          cout<<"该进程已成功杀死";
          // Memory.erase(Memory.begin()+i);  //从数组里面移除  
        }
        else{
          cout<<"该进程已被挂起"<<endl;
        }
      }
    }
  }
}

//换出进程
void swap_out(){
  int size = Memory.size();
  if(size == 0){
    cout<<"当前无运行中的进程";
  }
  else{
    string PID;
    cout<<"请输入需要换出进程的PID:"; cin>>PID;
    for(int i = 0;i < size;i++){
      if(Memory[i]->getexID() == PID && Memory[i]->getStatus() == 1){
        Memory[i]->changeStatus(Suspended);  
        Suspended_Queen.push(Memory[i]);        //换出为挂起状态,进入挂起队列中
        Memory.erase(Memory.begin()+i);     
      }
      else{
        cout<<"当前内存中不存在该进程"<<endl;
      }
    }
  }
}







int main(){

showProcess();
system("pause");
return 0;
}