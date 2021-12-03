#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

int conv(string s){
  int y = 0;
  int t = 1;
  for(int i = s.size()-1; i >= 0; i--){
    if(s[i] == '1'){
      y += t;
    }
    t *= 2;
  }
  return y;
}

string n(string s){
  string o = "";
  for(char c : s){
    o = o + ((c == '1')?'0':'1');
  }
  return o;
}

string o(vector<string> v, int s){
  int x = 0;
  for(string a : v){
    x += (a[s] == '1')?1:-1;
  }
  vector<string> t;
  char c = (x >= 0)? '1':'0';
  for(string a : v){
    if(a[s] == c) t.push_back(a);
  }
  if(t.size() == 1) return t[0];
  return o(t,s+1);
}

string co(vector<string> v, int s){
  int x = 0;
  for(string a : v){
    x += (a[s] == '1')?1:-1;
  }
  vector<string> t;
  char c = (x >= 0)? '0':'1';
  for(string a : v){
    if(a[s] == c) t.push_back(a);
  }
  if(t.size() == 1) return t[0];
  return co(t,s+1);
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
  stringstream s;

  for(int i = 0; i < 12; i++){
    s << (res[i] > 0)?1:0;
  }

  cout << conv(s.str()) * conv(n(s.str())) << endl;

  cout << conv(o(vals,0)) * conv(co(vals,0)) << endl;
  
  return 0;
}
