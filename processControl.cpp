/*
*funciton:ʵ�ִ������̣�ɱ�����̣�����������̣����ѣ�������
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAXSIZE 20

enum operation{start,kill,Suspended};



class PCB{
private:
  string process_ID_ex; //�ⲿID
  int process_ID_in; //�ڲ�ID
  int status;         //����״̬
  int Priority;       //�������ȼ�
  // int Pocess_Status;  //�����״̬
  int size;           //���������ʱ��
  int content[10];    //��������
public:
  PCB(){
    cout<<"�������ⲿ���̺�(���ַ����������):";
    cin>>process_ID_ex;
    this->process_ID_in = rand(); //��������ڲ����̺�
    cout<<"�������������:";
    for(auto a:this->content){
      cin>>a;
    }
    cout<<"��������̵Ĵ�С:";  cin>>this->size;
    cout<<"������������ȼ�:";  cin>>this->Priority;
    this->status = 1;   //Ĭ�����ڴ���(0�����ڴ��У�1���ڴ��У�2������)
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
      this->status = 1;  //�����ڴ�
      break;
    case 1:
    this->status = 0;     //ɱ��
    case 2:
    this->status = 2;     //����
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



vector<PCB*> Memory;     //ģ���ڴ�
queue<PCB*>  Suspended_Queen;  //�������



//���̴���
void create(){
    if(Memory.size() >= MAXSIZE)
    cout<<"�ڴ���������ɾ����������"<<endl;
    else{
      if(Memory.size() == 0){
        //�ڴ�����û�н��̣�ֱ�Ӵ���
        PCB *process = new PCB();
        Memory.push_back(process);       
        cout<<"�����ɹ�"<<endl;
        
      }
      else{
        //�ڴ������н��̣����ܴ�����ͬ���̣�
        PCB *process = new PCB();
        for(auto pro : Memory){
          if(pro->getexID() == process->getexID()){
                delete process; //�ͷŵ��ڴ�
                cout<<"�ڴ����Ѿ����ڸý��̣��ܾ�����!";
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
    cout<<"��ǰ�ڴ������������еĽ���";
  }
  else{}
  for(auto process : Memory){
    cout<<"�ⲿ���̺�"<<"\t"<<"�ڲ����̺�"<<"\t"<<"����״̬";
    cout<<process->getexID()<<"\t"<<process->getinID()<<"\t"<<process->getStatus();
  }
}


//ɱ������
void kill(){
  int size = Memory.size();
  if(size == 0){
    cout<<"���������еĽ���";
  }
  else{
    string PID;
    cout<<"��������Ҫ��ֹ���̵�PID:";cin>>PID;
    for(int i=0;i<size;i++){
      auto process = Memory[i];
      if(process->getexID() == PID){
        if(process->getStatus() == 0){
          cout<<"�ý����Ѿ������ڴ浱��"<<endl;
        }
        else if(process->getStatus() == 1){
          process->kill();  //�������Ƴ��ڴ棿��ʱֻ�ǽ��ڴ��н���״̬�ĳɲ����ڴ���
          cout<<"�ý����ѳɹ�ɱ��";
          // Memory.erase(Memory.begin()+i);  //�����������Ƴ�  
        }
        else{
          cout<<"�ý����ѱ�����"<<endl;
        }
      }
    }
  }
}

//��������
void swap_out(){
  int size = Memory.size();
  if(size == 0){
    cout<<"��ǰ�������еĽ���";
  }
  else{
    string PID;
    cout<<"��������Ҫ�������̵�PID:"; cin>>PID;
    for(int i = 0;i < size;i++){
      if(Memory[i]->getexID() == PID && Memory[i]->getStatus() == 1){
        Memory[i]->changeStatus(Suspended);  
        Suspended_Queen.push(Memory[i]);        //����Ϊ����״̬,������������
        Memory.erase(Memory.begin()+i);     
      }
      else{
        cout<<"��ǰ�ڴ��в����ڸý���"<<endl;
      }
    }
  }
}







int main(){

showProcess();
system("pause");
return 0;
}