/*
 *funciton:ʵ�ִ������̣�ɱ�����̣�����������̣����ѣ�������
 */
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define MAXSIZE 20

enum operation { start, Kill, Block };

class PCB {
 private:
  string process_ID_ex;  //�ⲿID
  int process_ID_in;     //�ڲ�ID
  int status;            //����״̬
  int Priority;          //�������ȼ�
  int size;              //���������ʱ��
  int content[10];       //��������
 public:
  PCB() {
    cout << "���������PID(�������ֺ��ַ����):";
    cin >> process_ID_ex;
    this->process_ID_in = rand();  //��������ڲ����̺�
    cout << "�������������:";
    for (auto a : this->content) {
      cin >> a;
    }
    cout << "��������̵Ĵ�С:";
    cin >> this->size;
    cout << "������������ȼ�:";
    cin >> this->Priority;
    this->status = 1;  //Ĭ�����ڴ���(0�����ڴ��У�1���ڴ��У�2������)
  }
  string getexID() { return this->process_ID_ex; }
  int getinID() { return this->process_ID_in; }
  void changeStatus(operation Op) {
    switch (Op) {
      case 0:
        this->status = 1;  //�����ڴ�
        break;
      case 1:
        this->status = 0;  //ɱ��
      case 2:
        this->status = 2;  //����
      default:
        break;
    }
    this->status == 1;
  }
  int getStatus() { return this->status; }
  string getstatu(int i) {
    switch (i) {
      case 0:
        return "δ����";
        break;
      case 1:
        return "��������";
        break;
      case 2:
        return "������";
        break;
      default:
        break;
    }
  }
};

vector<PCB*> Memory;      //ģ���ڴ�
queue<PCB*> Block_Queen;  //��������

//���̴���
void create() {
  if (Memory.size() >= MAXSIZE)
    cout << "�ڴ���������ɾ����������" << endl;
  else {
    if (Memory.size() == 0) {
      //�ڴ�����û�н��̣�ֱ�Ӵ���
      PCB* process = new PCB();
      Memory.push_back(process);
      cout << "�����ɹ�" << endl;
    } else {
      //�ڴ������н��̣����ܴ�����ͬ���̣�
      PCB* process = new PCB();
      for (auto pro : Memory) {
        if (pro->getexID() == process->getexID()) {
          delete process;  //�ͷŵ��ڴ�
          cout << "�ڴ����Ѿ����ڸý��̣��ܾ�����!";
        } else {
          Memory.push_back(process);
          cout << "�����ɹ�" << endl;
          break;
        }
      }
    }
  }
}

//�������еĽ���
void showProcess() {
  if (Memory.size() == 0) {
    cout << "��ǰ�ڴ������������еĽ���";
  } else {
    cout << "�ⲿ���̺�"
         << "\t"
         << "�ڲ����̺�"
         << "\t"
         << "����״̬" << endl;
    for (auto process : Memory) {
      cout << setw(10) << right << process->getexID() << "\t" << setw(10)
           << right << process->getinID() << "\t" << setw(8) << right
           << process->getstatu(process->getStatus())<< endl;
    }
  }
}

//ɱ������
void kill() {
  int size = Memory.size();
  if (size == 0) {
    cout << "���������еĽ���";
  } else {
    string PID;
    cout << "��������Ҫ��ֹ���̵�PID:";
    cin >> PID;
    for (int i = 0; i < size; i++) {
      auto process = Memory[i];
      if (process->getexID() == PID) {
        if (process->getStatus() == 0) {
          cout << "�ý����Ѿ������ڴ浱��" << endl;
        } else if (process->getStatus() == 1) {
          process->changeStatus(
              Kill);  //�������Ƴ��ڴ棿��ʱֻ�ǽ��ڴ��н���״̬�ĳɲ����ڴ���
          Memory.erase(Memory.begin() + i);  //�����������Ƴ�
          cout << "�ý���PID:" + PID + "�ѳɹ�ɱ��";
        } else {
          cout << "�ý����ѱ�����" << endl << endl;
        }
      }
    }
  }
}

//��������
void swap_out() {
  int size = Memory.size();
  if (size == 0) {
    cout << "��ǰ�������еĽ���";
  } else {
    string PID;
    cout << "��������Ҫ�������̵�PID:";
    cin >> PID;
    for (int i = 0; i < size; i++) {
      if (Memory[i]->getexID() == PID && Memory[i]->getStatus() == 1) {
        Memory[i]->changeStatus(Block);
        Block_Queen.push(Memory[i]);  //����Ϊ����״̬,��������������
        Memory.erase(Memory.begin() + i);
        cout<<"�����ɹ��ý����ѽ�����������";
        break;
      } else {
        cout << "��ǰ�ڴ��в����ڸý���" << endl << endl;
      }
    }
  }
}

//���ѽ���
void weakup() {
  if (Block_Queen.empty()) {
    cout << "��������û�������Ľ���(�޿ɻ��ѵĽ���)" << endl;
  } else {
    string PID;
    cout << "��������Ҫ���ѽ��̵�PID:";
    cin >> PID;
    int queue_size = Block_Queen.size();
    for (int i = 0; i < queue_size; i++) {
      if (Block_Queen.front()->getexID() == PID) {
        Block_Queen.front()->changeStatus(start);
        Memory.push_back(Block_Queen.front());
        Block_Queen.pop();
        cout << "����PID:" + PID + "�ɹ�";
      } else {
        Block_Queen.push(Block_Queen.front());
        Block_Queen.pop();
      }
    }
  }
}

void Draw() {
  cout << "----------------------------------------------------" << endl;
  cout << "                      ���̹���                      " << endl
       << endl
       << endl
       << endl;
  cout << "    1.��������                        2.�������еĽ���" << endl
       << endl;
  cout << "    3.��������                        4.ɱ������" << endl << endl;
  cout << "    5.���ѽ���                        6.�˳�����" << endl
       << endl
       << endl;
  cout << "----------------------------------------------------" << endl
       << endl
       << endl;
  int a = 0;
  while (true) {
    cout << endl << "��ѡ�����:";
    cin >> a;
    switch (a) {
      case 1:
        create();
        break;
      case 2:
        showProcess();
        break;
      case 3:
        swap_out();
        break;
      case 4:
        kill();
        break;
      case 5:
        weakup();
        break;
      case 6:
        exit(0);
        break;
      default:
        break;
    }
  }
}

int main() {
  Draw();
  system("pause");
  return 0;
}