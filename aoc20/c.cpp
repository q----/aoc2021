#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

vector<pair<int,int>> expand(pair<int,int> a){
  vector<pair<int,int>> o;
  for(int i = -2; i <= 2; i++){
    for(int j = -2; j <= 2; j++){
      o.push_back(pair<int,int>(a.first+i,a.second+j));
    }
  }
  return o;
}

map<pair<int,int>,bool> step(map<pair<int,int>,bool> q, vector<bool> g){
  set<pair<int,int>> c;
  for(auto a: q){
    vector<pair<int,int>> t = expand(a.first);
    c.insert(t.begin(),t.end());
  }
  map<pair<int,int>,bool> o;
  for(auto a : c){
    int idx2 = 0;
    for(int j = a.second - 1; j <= a.second + 1; j++){
      for(int i = a.first - 1; i <= a.first + 1; i++){
        int idx = 0;
        for(int v = -1; v <= 1; v++){
          for(int m = -1; m <= 1; m++){
            idx = 2 * idx + (q[pair<int,int>(i+m,j+v)]?1:0);
          }
        }
        idx2 = 2 * idx2 + g[idx];
      }
    }
    if(g[idx2]){
      o.insert(pair<pair<int,int>,bool>(a,true));
    }
  }
  return o;
}



int main(){
  string l;
  ifstream f("input");
  vector<bool> g;
  getline(f,l);
  for(int x = 0; x < l.size(); x++) g.push_back(l[x] == '#');
  getline(f,l);
  map<pair<int,int>,bool> q;
  
  int i = 0;
  while(getline(f,l)){
    for(int j = 0; j < l.size(); j++){
      if(l[j] == '#'){
        q.insert(pair<pair<int,int>,bool>(pair<int,int>(j,i),true));
      }
    }
    i++;
  }

  q = step(q,g);
  cout << q.size() << endl;

  for(int t = 1; t < 25; t++) q = step(q,g);
  cout << q.size() << endl;

  return 0;
}
