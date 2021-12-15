#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <climits>

using namespace std;

const pair<int,int> operator+(const pair<int,int>& lhs, const pair<int,int>& rhs){
  pair<int,int> o;
  o.first = lhs.first + rhs.first;
  o.second = lhs.second + rhs.second;
  return o;
}

int ah(vector<string> x){
  bool fl = true;
  map<pair<int,int>,int> a;
  for(int i = 0; i < x.size(); i++){
    for(int j = 0; j < x[i].size(); j++){
      a[pair<int,int>(i,j)] = INT_MAX;
    }
  }
  a[pair<int,int>(0,0)] = 0;
  auto c = [&a](pair<int,int> x, pair<int,int> y){return a[x] > a[y];};
  priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(c)> d(c, {pair<int,int>(0,0)});

  vector<pair<int,int>> dir = {pair<int,int>(1,0),  pair<int,int>(0,1), pair<int,int>(-1,0),  pair<int,int>(0,-1)};
  set<pair<int,int>> v;
  v.insert(d.top());

  while(a[pair<int,int>(x.size()-1,x[0].size()-1)] == INT_MAX){
    auto curr = d.top();
    d.pop();

    for(auto g : dir){
      auto m = g + curr;
      if(m.first < 0 || m.first >= x.size() || m.second < 0 || m.second >= x[0].size()) continue;
      a[m] = [](int x, int y){return (x < y)?x:y;}(a[m], a[curr] + x[m.first][m.second] - '0');
      if(v.insert(m).second) d.push(m);
    }
  }

  return a[pair<int,int>(x.size()-1,x[0].size()-1)];
}

string inc(string x){
  string o = "";
  for(char c : x){
    char g = c + 1;
    if( g == ':') g = '1';
    o += g;
  }
  return o;
}

vector<string> t5(vector<string> x){
  for(int i = 0; i < x.size(); i++){
    string t = x[i];
    for(int j = 1; j < 5; j++){
      t = inc(t);
      x[i] += t;
    }
  }
  int q = x.size();
  for(int j = 0; j < 4; j++){
    for(int i = 0; i < q; i++){
      x.push_back(inc(x[j * q + i]));
    }
  }
  return x;
}

int main(){
  string l;
  ifstream f("input");
  vector<string> x;
  while(getline(f,l)) x.push_back(l);

  cout << ah(x) << endl;
  cout << ah(t5(x)) << endl;

  return 0;
}
