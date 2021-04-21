/*
valuable string to number
*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;



bool compare(string str){
  stack<char> m;
  char first = str[0];
  if(first == '}' || first == ']' || first == ')' || str == ""){
    return false;
  }
  else{
    for(int i=0;i<str.length();i++){
      if(m.empty()){
        m.push(str[i]);
        continue;
      }
      char &s = m.top();
      switch (str[i])
      {
      case '}':
        if(s == '{'){
          m.pop();
        }
        else{
          return false;
        }
        break;
          case ')':
        if(s == '('){
          m.pop();
        }
        else{
          return false;
        }
        break;
            case ']':
        if(s == '['){
          m.pop();
        }
        else{
          return false;
        }
        break;
      
      default:
        m.push(str[i]);
        break;
      }
    }
    return m.empty();
    
  }
  return m.empty();
}

int main(){
  bool value = compare("");

  return 0;
}