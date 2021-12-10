#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  string l;
  ifstream f("input");
  int o = 0;
  vector<long long int> c;

  while(getline(f,l)){
    bool fl = true;
    while(fl){
      for(int i = 0; i < l.size(); i++){
        for(string chunk : {"<>", "()", "[]", "{}"}){ 
          if(l.substr(i,2) == chunk){
            l.erase(i,2);
            i = l.size();
            break;
          }
        }
        if(i == l.size()-1) fl = false;
      }
    }
    size_t found = l.find_first_not_of("{<([");
    if(found != string::npos){
      if(l[found] == ']') o += 57;
      if(l[found] == ')') o += 3;
      if(l[found] == '}') o += 1197;
      if(l[found] == '>') o += 25137;
    } else {
      string q = "";
      for(int i = l.size()-1; i>= 0; i--){
        if(l[i] == '(') q += "1";
        if(l[i] == '[') q += "2";
        if(l[i] == '{') q += "3";
        if(l[i] == '<') q += "4";
      }
      c.push_back(stoll(q,nullptr,5));
    }
  }

  cout << o << endl;

  sort(c.begin(), c.end());
  cout << c[c.size()/2] << endl;

  return 0;
}
