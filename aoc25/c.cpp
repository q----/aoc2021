#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<pair<int,int>,char> move(map<pair<int,int>,char> q, int s, int g, char c){
  map<pair<int,int>,char> o;
  for(auto t : q){
    if(t.second != c){
      o.insert(t);
      continue;
    }
    pair<int,int> n;
    if(t.second == '>'){
      n = pair<int,int>(t.first.first,(t.first.second + 1)%g);
    } else {
      n = pair<int,int>((t.first.first+1)%s,t.first.second);
    }
    if(!q.count(n)){
      o.insert(pair<pair<int,int>,char>(n,c));
    } else {
      o.insert(t);
    }
  }
  return o;
}


map<pair<int,int>,char> sim(map<pair<int,int>,char> q, int s, int g){
  map<pair<int,int>,char> o = move(q, s, g, '>');
  return move(o, s, g, 'v');
}

void print(map<pair<int,int>,char> q){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 10; j++){
      if(q.count(pair<int,int>(i,j))){
        cout << q[pair<int,int>(i,j)];
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}

int main(){
  string l;
  ifstream f("input");
  map<pair<int,int>,char> q;


  int i = 0;
  while(getline(f,l)){
    for(int j = 0; j < l.size(); j++) if(l[j] != '.') q.insert(pair<pair<int,int>,char>(pair<int,int>(i,j),l[j]));
    i++;
  }
  print(q);
  cout << endl;

  int g = i;
  i = 1;
  map<pair<int,int>,char> t = sim(q, 137, 139);
  print(t);
  while(t != q){
    i++;
    q = t;
    t = sim(q, 137, 139);
  }

  cout << i << endl;

  return 0;
}
