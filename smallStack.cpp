/*************
  Date:2021.3.27s
  the smallest stack
  链表头插法,并在每个节点中存入当前节点作为栈顶时的最小值
*************/

#include<iostream>
using namespace std;

struct node
{
  int value;
  int min;
  struct node *next = nullptr;
};


class MinStack{
  private:
  node* head;
  public:
  MinStack(){
    this->head = new node; //初始化头指针
  };
   void pop(){
     if(this->head->next !=  nullptr){
       node *tmp = this->head->next->next;
      delete this->head->next;
      this->head->next = tmp;       
     }
  };
  int top(){
      return this->head->next->value;

  };

  void push(int val){
    //头插法入栈
    node *temp = new node;
    temp->value = val;
    if(this->head->next == nullptr){
      temp->min = val;  
    }
    else{
      temp->min = val < this->head->next->min ? val : this->head->next->min;
    }
    temp->next = this->head->next;
    this->head->next = temp;

  };
  int getmin(){
      return this->head->next->min;
      }
};
int main(){
  MinStack *s = new MinStack();
  s->push(2);
  s->push(5);
  s->push(-3);
  cout<<s->top()<<endl;
  cout<<s->getmin()<<endl;
  s->pop();
  cout<<s->top()<<endl;
  cout<<s->getmin()<<endl;
  system("pause");
  return 0;
}