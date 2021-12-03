#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

string o(vector<string> v, int s, bool (*f)(int)){
  int x = 0;
  for(string a : v){
    x += (a[s] == '1')?1:-1;
  }
  vector<string> t;
  char c = (f(x))? '1':'0';
  for(string a : v){
    if(a[s] == c) t.push_back(a);
  }
  if(t.size() == 1) return t[0];
  return o(t,s+1,f);
}

int main(){
  string l;
  ifstream f("input");

  map<int,int> res;
  vector<string> vals;

  while(getline(f,l)){
    for(int i = 0; i < l.size(); i++){
      res[i] += (l[i] == '1')? 1:-1;
    }
    vals.push_back(l);
  }
  
  string s = "";
  for(int i = 0; i < 12; i++){
    s += ((res[i] > 0)?"1":"0");
  }

  cout << [](int x){ return x * (4095 - x); } (stoi(s,0,2)) << endl;

  cout << stoi(o(vals,0,[](int x){ return x >= 0;}),0,2) * stoi(o(vals,0,[](int x){ return x < 0;}),0,2) << endl;
  
  return 0;
}
