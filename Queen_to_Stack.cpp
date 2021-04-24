#include <iostream>
#include <queue>

class stack {
 public:
  std::queue<int> q;
  stack(){};
  void push(int m) {
    if (q.empty()) {
      q.push(m);
    } else {
      int size = q.size();
      int i = 0;
      q.push(m);
      while (i < size) {
        q.push(q.front());
        q.pop();
        i++;
      }
    }
  }
  void pop() {
    if(!q.empty())
      q.pop();
   }
  int top(){
    if(!q.empty()){
      return q.front();
    }
    else{
      return 0;
    }
  }
  bool empty(){
    return q.empty();
  }
};

int main() {
  stack *MyStack = new stack();
  MyStack->push(2);
  MyStack->push(3);
  std::cout<<MyStack->top()<<"\n";
  MyStack->pop();
  std::cout<<MyStack->top();
  return 0;
}