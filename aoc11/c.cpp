#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

bool in(vector<string>& x, int i, int j){
  if(i < 0 || j < 0 || i >= x.size() || j >= x[i].size() || x[i][j] == ':') return false;
  x[i][j]++;
  return x[i][j] == ':';
}

int step(vector<string>& x){
  set<pair<int,int>> a;
  for(int i = 0; i < x.size(); i++){
    for(int j = 0; j < x[i].size(); j++){
      x[i][j]++;
      if(x[i][j] == ':') a.insert(pair<int,int>(i,j));
    }
  }
  while(!a.empty()){
    pair<int,int> q = *a.begin();
    a.erase(a.begin());
    for(int w = -1; w <= 1; w++){
      for(int y = -1; y <= 1; y++){
        if( y == 0 && w == 0) continue;
        if(in(x,q.first+w,q.second+y)) a.insert(pair<int,int>(q.first+w,q.second+y));
      }
    }
  }
  int o = 0;

  for(int i = 0; i < x.size(); i++){
    for(int j = 0; j < x[i].size(); j++){
      if(x[i][j] == ':'){
        o++;
        x[i][j] = '0';
      }
    }
  }
  return o;
}
  

int main(){
  string l;
  ifstream f("input");
  vector<string> o;

  while(getline(f,l)) o.push_back(l);

  int i = 0;
  int t = 0;
  int t2 = 0;
  while(i < 100||t2 == 0){
    i++;
    int x = step(o);
    if(i <= 100) t += x;
    if(x == 100 && t2 == 0) t2 = i;
  }

  cout << t << endl;
  cout << t2 << endl;

  return 0;
}
