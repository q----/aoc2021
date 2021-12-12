#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

int path(map<string,vector<string>>& paths, string loc, map<string,int> p, bool rep){
  p[loc]++;
  int o = 0;
  for(auto x : paths[loc]){
    bool rtmp = rep;
    if(p[x] && x[0] >= 'a'){
      if(rtmp) continue;
      rtmp = true;
    }
    o += ((x == "end")?1:path(paths, x, p, rtmp));
  }
  return o;
}

int main(){
  string l;
  ifstream f("input");
  map<string,vector<string>> paths;

  while(getline(f,l)){
    for(int i = 0; i < l.size(); i++) if(l[i] == '-') l[i] = ' ';
    stringstream s(l);
    string x;
    string y;
    s >> x >> y;
    if(y != "start" && x != "end") paths[x].push_back(y);
    if(x != "start" && y != "end") paths[y].push_back(x);
  }

  map<string,int> v;
  cout << path(paths, "start", v, true) << endl;
  cout << path(paths, "start", v, false) << endl;

  return 0;
}
