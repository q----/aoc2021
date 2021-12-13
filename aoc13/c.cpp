#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>

using namespace std;

set<pair<int,int>> fold(set<pair<int,int>> dots, bool g, int line){
  set<pair<int,int>> o;
  for(auto x : dots){
    o.insert(g?
        pair<int,int>(line - abs(x.first - line), x.second):
        pair<int,int>(x.first, line - abs(x.second - line)));
  }
  return o;
}

int main(){
  string l;
  ifstream f("input");
  set<pair<int,int>> dots;

  while(getline(f,l) && l != ""){
    for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';
    stringstream s(l);
    int x,y;
    s >> x >> y;
    dots.insert(pair<int,int>(x,y));
  }

  bool first = true;
  while(getline(f,l)){
    for(int i = 0; i < l.size(); i++) if(l[i] == '=') l[i] = ' ';
    stringstream s(l);
    string t,t2,t3;
    int line;
    s >> t >> t2 >> t3 >> line;
    dots = fold(dots, t3 == "x", line);
    if(first){
      cout << dots.size() << endl;
      first = false;
    }
  }

  int xmin = 100;
  int xmax = 0;
  int ymin = 100;
  int ymax = 0;
  for(auto x : dots){
    xmin = (xmin < x.first)? xmin: x.first;
    xmax = (xmax < x.first)? x.first: xmax;
    ymin = (ymin < x.second)? ymin: x.second;
    ymax = (ymax < x.second)? x.second: ymax;
  }

  for(int j = ymin; j <= ymax; j++){
    for(int i = xmin; i <= xmax; i++){
      if(dots.count(pair<int,int>(i,j))){
        cout << "#";
      } else {
        cout << " ";
      }
    }
    cout << endl;
  }

  return 0;
}
