#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
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
  vector<pair<int,int>> d = {pair<int,int>(0,0)};

  vector<pair<int,int>> dir = {pair<int,int>(1,0),  pair<int,int>(0,1), pair<int,int>(-1,0),  pair<int,int>(0,-1)};
  set<pair<int,int>> v;
  v.insert(d[0]);

  while(a[pair<int,int>(x.size()-1,x[0].size()-1)] == INT_MAX){
    int min = INT_MAX;
    int minidx;
    for(int i = 0; i < d.size(); i++){
      if(a[d[i]] < min){
        min = a[d[i]] - (x[d[i].first][d[i].second]-'0')*(d[i].first + d[i].second)/10;
        minidx = i;
      }
    }

    for(auto g : dir){
      auto m = g + d[minidx];
      if(m.first < 0 || m.first >= x.size() || m.second < 0 || m.second >= x[0].size()) continue;
      a[m] = [](int x, int y){return (x < y)?x:y;}(a[m], a[d[minidx]] + x[m.first][m.second] - '0');
      if(v.insert(m).second) d.push_back(m);
    }
    d.erase(d.begin() + minidx);
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
