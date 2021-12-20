#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

struct sc{
  vector<int> p;
  vector<vector<int>> b;
  int d;
  int r;
  bool f;
  sc(vector<int> a, vector<vector<int>> g, int q, int t, bool qg){
    p = a;
    b = g;
    d = q;
    r = t;
    f = qg;
  }
  sc(vector<vector<int>> a){
    b = a;
    p = {0,0,0};
    d = 1;
    r = 0;
    f = false;
  }
  vector<int>  operator[](const int& rhs);
};

vector<int> operator-(const vector<int>& lhs){
  vector<int> o;
  for(int i = 0; i < lhs.size(); i++) o.push_back(-lhs[i]);
  return o;
}

bool operator<(const vector<int>& lhs, const vector<int>& rhs){
  for(int i = 0; i < 2; i++) if(lhs[i] != rhs[i]) return lhs[i] < rhs[i];
  return lhs[2] < rhs[2];
}

template <typename T>
int acc(vector<int> a, T b, int init = 0){
  return accumulate(a.begin(),a.end(),init,b);
}

bool operator&(const vector<int>& lhs, const vector<int>& rhs){
  auto h = [](int x, int y){return abs(x + y);};
  auto t = [](int x, int y){return abs(x * y);};
  bool x = (acc<decltype(h)>(lhs,h) == acc<decltype(h)>(rhs,h));
  x = x && (acc<decltype(t)>(lhs,t,1) == acc<decltype(t)>(rhs,t,1));
  return x;
}
  
vector<int> operator+(const vector<int>& lhs, const vector<int>& rhs){
  vector<int> o;
  for(int i = 0; i < lhs.size(); i++) o.push_back(lhs[i] + rhs[i]);
  return o;
}

vector<int> operator-(vector<int>& lhs, vector<int>& rhs){
  return lhs + (-rhs);
}

vector<int> sc::operator[](const int& rhs){
  vector<int> t = this->b[rhs];
  if(this->f)  t = -t;
  vector<int> a = {0,1,2};
  a.erase(a.begin() + this->d);
  vector<int> b;
  for(int i = 0; i < 2; i++){
    b.push_back(t[a[i]]);
  }
  for(int i = 0; i < this->r; i++){
    b = {b[1], -b[0]};
  }
  t[0] = t[this->d];
  for(int i = 0; i < 2; i++){
    t[i+1] = b[i];
  }
  return t + this->p;
}

vector<vector<int>> asdg(sc a){
  vector<vector<int>> o;
  for(int i = 0; i < a.b.size()-1; i++){
    for(int j = i+1; j < a.b.size(); j++){
      o.push_back(a.b[i]-a.b[j]);
    }
  }
  return o;
}
        
bool afs(sc a, sc b){
  vector<vector<int>> aa = asdg(a);
  vector<vector<int>> ba = asdg(b);
  int t = 0;
  for(auto x : aa)for(auto y : ba) if(x&y) t++;
  return t >= 12;
}

int d (vector<int> a, vector<int> b){
  vector<int> t = a-b;
  return accumulate(t.begin(),t.end(),0,[](int a, int b){return (abs(a)>abs(b))?abs(a):abs(b);});
}
  
bool inr(sc a, sc b){
  set<vector<int>> v;
  for(int i = 0; i < a.b.size(); i++){
    if(d(a[i],b.p) <= 1000){
      v.insert(a[i]);
    }
  }
  set<vector<int>> v2;
  for(int i = 0; i < b.b.size(); i++){
    if(d(b[i],a.p) <= 1000){
      if(v.insert(b[i]).second) return false;
      v2.insert(b[i]);
    }
  }
  return v.size() == v2.size() && v.size() >= 12;
}

bool inr4(sc a, vector<int> x){
  int s = 0;
  for(int i = 0; i < a.b.size(); i++){
    vector<int> t = a[i];
    t[1] = 0;
    t[2] = 0;
    if(d(t,x) <= 1000) s++;
  }
  return s >= 12;
}

bool inr3(sc a, vector<int> x){
  int s = 0;
  for(int i = 0; i < a.b.size(); i++){
    vector<int> t = a[i];
    t[2] = 0;
    if(d(t,x) <= 1000) s++;
  }
  return s >= 12;
}


bool inr2(sc a, vector<int> x){
  int s = 0;
  for(int i = 0; i < a.b.size(); i++)
    if(d(a[i],x) <= 1000) s++;
  return s >= 12;
}

sc pa(sc a, sc b){
  vector<vector<int>> aa = asdg(a);
  vector<vector<int>> ba = asdg(b);
  int q = 0;
  for(int i = 0; i < a.size(); i++){
    for(int j = i + 1; j < a.size(); j++){
      q++;
      int d = 0;
      for(int k = 0; k < b.size(); k++){
        for(int l = k; l < b.size(); l++){
          d++;
          if(aa[q]&ba[d]){
            
        


  
  

  
  for(int i = -1000; i <= 1000; i++){
    if(!inr4(a,{i,0,0})) continue;
    for(int j = -1000; j <= 1000; j++){
      if(!inr3(a,{i,j,0})) continue;
      for(int k = -1000; k <= 1000; k++){
        if(!inr2(a,{i,j,k})) continue;
        for(int d : {-3,-2,-1,1,2,3}){
          for(int r = 0; r < 4; r++){
            vector<int> qt = {i,j,k};
            sc t = sc((a.p + qt), b.b, abs(d)-1, r, (d < 0));
            if(inr(a,t)) return t;
          }
        }
      }
    }
  }
  b.d = -1;
  return b;
}

vector<sc> align(vector<sc> in){
  vector<sc> o;
  o.push_back(in[0]);
  in.erase(in.begin());
  while(in.size() > 0){
    for(int i = 0; i < in.size(); i++){
      bool fl = false;
      for(sc x : o){
        if(!afs(x,in[i]))continue;
        sc t = pa(x,in[i]);
        if(t.d != -1){
          o.push_back(t);
          in.erase(in.begin() + i);
          cout << o.size() << endl;
          fl = true;
          break;
        }
      }
      if(fl) break;
    }
  }
  return o;
}

int count(vector<sc> in){
  set<vector<int>> tally;
  for(sc x : in){
    for(int i = 0; i < x.b.size(); i++){
      tally.insert(x[i]);
    }
  }
  return tally.size();
}







int main(){
  string l;
  ifstream f("input");

  vector<sc> q;
  vector<vector<int>> t;
  while(getline(f,l)){
    if(l == ""){
      q.push_back(sc(t));
      t.erase(t.begin(),t.end());
      continue;
    }
    if(l[1] == '-') continue;
    for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';
    stringstream s(l);
    int a,b,g;
    s >> a >> b >> g;
    t.push_back({a,b,g});
  }

  cout << count(align(q)) << endl;


  return 0;
}
