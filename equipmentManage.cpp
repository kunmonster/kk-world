#include <iostream>
#include <queue>
#include <string>
using namespace std;

enum Status { BUSY, FREE };

struct CHCT {
  string chct_id;
  Status statu = FREE;
};

struct COCT {
  string control_id;
  Status statu = FREE;
  CHCT* pipe;
};

struct DCT {
  string device_id;
  string type;
  Status statu = FREE;
  COCT* control;
  queue<int> processque;
};

void add();
vector<DCT*> alldct;
vector<COCT*> allcontrol;
vector<CHCT*> allpipe;

void apply(int process) {
  string deviced;
  cout << "请输入想申请的设备的id" << endl;
  cin >> deviced;
  DCT* dct = new DCT;
  bool dct_have = false;
  if (alldct.empty()) {
    //添加设备
    cout << "系统中无当前设备！将自动为您添加" << endl;
    DCT* dct_temp = new DCT;
    dct_temp->device_id = deviced;
    dct_temp->statu = BUSY;
    dct = dct_temp;
    cout << "添加成功!" << endl;
  } else {
    //直接申请设备
    for (auto item : alldct) {
      if (item->device_id == deviced) {
        //找到设备
        if (item->statu == FREE) {
          //未被占用 申请成功
          dct_have = true;
          item->statu = BUSY;
          dct = item;
        } else {
          item->processque.push(process);  //等待队列;
        }
      }
      if (!dct_have) {
        cout << "系统中无当前设备！将自动为您添加" << endl;
        add();
        dct = alldct.back();
        dct->statu = BUSY;
        dct_have = true;
      }
    }
  }
  COCT* coct_tmp;
  string control_id;
  cout << "请输入控制器id:" << endl;
  cin >> control_id;
  if (allcontrol.empty()) {
    //控制器为空 添加一个控制器
    COCT* coct_temp = new COCT;
    coct_temp->control_id = control_id;
    coct_temp->statu = BUSY;
    coct_temp->pipe = nullptr;
    coct_tmp = coct_temp;
    allcontrol.push_back(coct_tmp);
  } else {
    for (auto item_con : allcontrol) {
      if (item_con->control_id == control_id) {
        if (item_con->statu == FREE) {
          //申请成功
          coct_tmp->statu = BUSY;
          coct_tmp = item_con;
        } else {
          //被占用
          cout << "当前控制器被占用";
        }
      }
    }
  }
  dct->control = coct_tmp;
  cout << "请输入通道ID:" << endl;
  string pipeid;
  cin >> pipeid;
  if (!allpipe.empty()) {
    for (auto item_pipe : allpipe) {
      if (item_pipe->chct_id == pipeid) {
        if (item_pipe->statu == FREE) {
          //通道分配成功
          item_pipe->statu = BUSY;
          coct_tmp->pipe = item_pipe;
        } else {
          cout << "当前通道被占用";
        }
      }
    }
  } else {
    CHCT* chct_tmp = new CHCT;
    chct_tmp->chct_id = pipeid;
    chct_tmp->statu = BUSY;
    allpipe.push_back(chct_tmp);
    coct_tmp->pipe = chct_tmp;
  }
  cout << "申请成功!"<< endl;
  if (!dct_have) alldct.push_back(dct);
}

void release() {
  bool tag = false;
  bool relasetag = false;
  string id;
  cout << "请输入想释放的设备的id" << endl;
  cin >> id;
  for (auto item : alldct) {
    if (item->device_id == id) {
      //找到设备
      tag = true;
      if (item->statu == BUSY) {
        cout << "当前设备被占用,是否强行释放?\t[Y]:是\t[N]:否" << endl;
        char c;
        cin >> c;
        if (c == 'Y') {
          COCT* newcoct = nullptr;
          CHCT* newchct = nullptr;

          //级联解除占用
          item->statu = FREE;
          item->control->statu = FREE;
          item->control->pipe->statu = FREE;
          item->control->pipe = newchct;
          item->control = newcoct;

          cout << "释放设备成功!" << endl;

        } else {
          cout << "释放失败!" << endl;
          break;
        }
      } else {
        item->statu == FREE;
        cout << "当前设备无需释放!" << endl;
        break;
      }
      tag = true;
      break;
    } else {
      continue;
    }
  }
  if (!tag) {
    cout << "无该设备";
  }
}

void del() {
  bool tag = false;
  bool deltag = true;
  cout << "请输入需要删除设备的ID:" << endl;
  string id;
  cin >> id;
  for (auto item : alldct) {
    if (item->device_id == id) {
      tag = true;
      if (item->statu == BUSY) {
        cout << "当前设备被占用,是否强行删除?\t[Y]:是\t[N]:否"<<endl;
        char c;
        cin >> c;
        if (c == 'Y') {
          deltag = true;
        } else {
          deltag = false;
          cout << "删除失败!" << endl;
          break;
        }
      }
      
      if (deltag) {
        tag = true;
        COCT* newcoct = nullptr;
        CHCT* newchct = nullptr;
        //级联删除
        if (item->control != nullptr) {
          item->statu = FREE;
          item->control->statu = FREE;
          item->control->pipe->statu = FREE;
          item->control->pipe = newchct;
          item->control = newcoct;
        }
          cout << "删除成功!" << endl;
        delete item;
      }
      break;
    } else {
      continue;
    }
  }
  if (!tag) {
    cout << "该设备不存在!" << endl;
  }
}

void add() {
  bool inputtag = false;
  string id;
  string type;
reinput:
  cout << "请输入添加设备的ID:" << endl;
  cin >> id;
  for (auto item : alldct) {
    if (item->device_id == id) {
      cout << "当前id已经存在!请重新输入!" << endl;
      inputtag = true;
      break;
    } else
      continue;
  }
  if (inputtag) {
    goto reinput;
  }
  DCT* new_dct = new DCT;
  new_dct->device_id = id;
  new_dct->type = "default_type";
  new_dct->statu = FREE;
  new_dct->control = nullptr;
  cout << "添加成功!" << endl;
  alldct.push_back(new_dct);
}

int main() {
  while (true) {
    int processid;
    cout << "请输入进程号:" << endl;
    cin >> processid;
    cout << "请选择操作:" << endl;
    cout << "[1]:申请设备\t[2]:添加设备" << endl;
    cout << "[3]:释放设备\t[4]:删除设备" << endl;
    cout << "[5]:所有设备\t[6]:退出程序" << endl;
    int c;
    cin>>c;
    if (c == 1) {
      apply(processid);
    } else if (c == 2) {
      add();
    } else if (c == 3) {
      release();
    } else if (c == 4) {
      del();
    } else if (c == 5) {
      cout << "device_id\tstatu" << endl;
      for (auto item : alldct) {
        cout << item->device_id << "\t\t" << item->statu << endl;
      }
    } else if (c == 6) {
      exit(0);
    } else {
      continue;
    }
  }
  return 0;
}