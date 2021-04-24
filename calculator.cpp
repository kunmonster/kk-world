#include <math.h>

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define INT_MAX 2147483647

class Caculator {
 private:
 public:
  int priority(char c) {
    switch (c) {
      case '+':
        return 2;
      case '-':
        return 2;
      case '*':
        return 3;
      case '/':
        return 3;
      case ')':
        return 1;
      case '(':
        return 4;
      default:
        return 0;
    }
  }
 long Reverse(string s) {
    stack<int> value;
    stack<char> oper;
    int length = s.length();
    for (int i = 0; i < length; i++) {
      if (s[i] == ' ')
        continue;
      else if (isdigit(s[i])) {
        int sum = 0;
        while (isdigit(s[i])) {
          sum = sum * 10 + (s[i] - '0');
          ++i;
        }
        i -= 1;
        value.push(sum);
      } else {
        while (!oper.empty() &&
               this->priority(oper.top()) >= this->priority(s[i]) &&
               oper.top() != '(') {
          int a, b = 0;
          char sign = oper.top();
          if (!value.empty()) {
            b = value.top();
            value.pop();
          }
          if (!value.empty()) {
            a = value.top();
            value.pop();
          }
          switch (sign) {
            case '+':
              a += b;
              break;
            case '-':
              a = a - b;
              break;
            case '*':
              a *= b;
              break;
            case '/':
              a = a / b;
              break;
            default:
              break;
          }
          value.push(a);
          oper.pop();
        }
        if (s[i] == ')') {
          oper.pop();
        } else {
          oper.push(s[i]);
        }
      }
    }
    while (!oper.empty()) {
      long a, b = 0;
      char sign = oper.top();
      if (!value.empty()) {
        b = value.top();
        value.pop();
      }
      if (!value.empty()) {
        a = value.top();
        value.pop();
      }
     
      switch (sign) {
        case '+':
          a += b;
          break;
        case '-':
          a = a - b;
          break;
        case '*':
          a *= b;
          break;
        case '/':
          a = a / b;
          break;
        default:
          break;
      }
      oper.pop();
      value.push(a);
    }
    return value.top();
  }
};
int main() {
  string m = "1*2-3/4+5*6-7*8+9/10";
  Caculator *A = new Caculator();
  int res = A->Reverse(m);

  system("pause");
  return 0;
}