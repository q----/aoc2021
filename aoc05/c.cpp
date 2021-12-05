#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct line{
  int x1;
  int x2;
  int y1;
  int y2;
  line(int a, int b, int c, int d){
    x1 = a;
    x2 = c;
    y1 = b;
    y2 = d;
  }
};

bool h(line& a){
  return a.x1 == a.x2 || a.y1 == a.y2;
}

line p(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';
  stringstream s(l);
  string t;
  int a,b,c,d;
  s >> a >> b >> t >> c >> d;
  return line(a,b,c,d);
}

void add(map<pair<int,int>,int>& field, line& a){
  if(a.x1 == a.x2){
    int s = (a.y1 < a.y2)?a.y1:a.y2;
    int l = (a.y1 > a.y2)?a.y1:a.y2;
    for(int i = s; i <= l; i++){
      field[pair<int,int>(a.x1,i)]++;
    }
    return;
  }
  if(a.y1 == a.y2){
    int s = (a.x1 < a.x2)?a.x1:a.x2;
    int l = (a.x1 > a.x2)?a.x1:a.x2;
    for(int i = s; i <= l; i++){
      field[pair<int,int>(i,a.y1)]++;
    }
    return;
  }
  int y = a.y1; //8,0 -> 0,8
  if(a.x1 < a.x2){
    for(int i = a.x1; i <= a.x2; i++){
      field[pair<int,int>(i,y)]++;
      if(a.y1 < a.y2)y++;
      else y--;
    }
  } else {
    for(int i = a.x1; i >= a.x2; i--){
      field[pair<int,int>(i,y)]++;
      if(a.y1 < a.y2)y++;
      else y--;
    }
  }
}

int count(map<pair<int,int>,int>& field){
  int o = 0;
  for(auto a : field){
    if(a.second >= 2)
      o++;
  }
  return o;
}

int main(){
  string l;
  ifstream f("input");

  vector<line> hl;
  vector<line> vl;

  while(getline(f,l)){
    line t = p(l);
    if(h(t)) hl.push_back(t);
    else vl.push_back(t);
  }

  map<pair<int,int>,int> field;

  for(auto x : hl){
    add(field, x);
  }

  cout << count(field) << endl;

  for(auto x : vl){
    add(field, x);
  }

  cout << count(field) << endl;

  return 0;
}
