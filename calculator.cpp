#include <math.h>

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Caculator {
 private:
 public:
  int priority(char c) {
    switch (c) {
      case '+':
        return 1;
      case '-':
        return 1;
      case '*':
        return 2;
      case '/':
        return 2;
      default:
        return 0;
    }
  }
  int Reverse(string s) {
    vector<char> value;
    stack<char> oper;
    int length = s.length();
    for (int i=0;i<length;i++) {
      if (s[i] == ' ')
        continue;
      else if (isdigit(s[i])) {
        int sum = 0;
        while(isdigit(s[i])){
          sum = sum*10+(s[i]-'0');
          i++;
        }
        value.push_back(sum);
      } else {
        if (oper.empty()) {
          oper.push(s[i]);
        } else {
          while (!oper.empty() && (priority(oper.top()) >= priority(s[i]))) {
            value.push_back(oper.top());
            oper.pop();
          }
          oper.push(s[i]);
        }
      }
      cout<<value[i];
    }
    while (!oper.empty()) {
      
      value.push_back(oper.top());
      oper.pop();
    }

    //计算
    stack<int> result;
    int length_num = value.size();
    for (int i = 0; i < length_num; i++) {
      if (isdigit(value[i])) {
        result.push(value[i] - '0');
      } else {
        int a,b=0;
        if(!result.empty())
           a = result.top();
          result.pop();
        if(!result.empty())  
           b = result.top();
          result.pop();
        switch (value[i]) {
          case '+':
            a += b;
            break;
          case '-':
            a = b - a;
            break;
          case '*':
            a *= b;
            break;
          case '/':
            a = b / a;
            break;
          default:
            break;
        }
        result.push(a);
      }
    }
  
  return result.top();
  }
};
int main() {
  string m = "256+32*2";
  Caculator *A = new Caculator();
  auto res = A->Reverse(m);

  system("pause");
  return 0;
}