#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

struct c{
  int xb,yb,zb;
  int xe,ye,ze;
  c(int ab, int bb, int cb, int ae, int be, int ce){
    xb = ab;
    yb = bb;
    zb = cb;
    xe = ae;
    ye = be;
    ze = ce;
  }

  int vol(){
    return (xe-xb+1)*(ye-yb+1)*(ze-zb+1);
  }

  bool mutex(c a){
    vector<int> d = {xb,xe,a.xb,a.xe};
    if(is_sorted(d.begin(),d.end())) return true;
    d = {a.xb,a.xe,xb,xe};
    if(is_sorted(d.begin(),d.end())) return true;
    d = {yb,ye,a.yb,a.ye};
    if(is_sorted(d.begin(),d.end())) return true;
    d = {a.yb,a.ye,yb,ye};
    if(is_sorted(d.begin(),d.end())) return true;
    d = {zb,ze,a.zb,a.ze};
    if(is_sorted(d.begin(),d.end())) return true;
    d = {a.zb,a.ze,zb,ze};
    if(is_sorted(d.begin(),d.end())) return true;
    return false;
  }
};

bool operator<(const c& a, const c& b){
  if(a.xb != b.xb) return a.xb < b.xb;
  if(a.xe != b.xe) return a.xe < b.xe;
  if(a.yb != b.yb) return a.yb < b.yb;
  if(a.ye != b.ye) return a.ye < b.ye;
  if(a.zb != b.zb) return a.zb < b.zb;
  return a.ze < b.ze;
}

pair<set<c>,set<c>> add(c a, c b){
  set<c> o;
  set<c> ob;
  if(a.mutex(b)){
    o.insert(a);
    ob.insert(b);
    return pair<set<c>,set<c>>(o,ob);
  }
  vector<int> x ({a.xb + (a.xb>=b.xb), a.xe - (a.xe <= b.xe), b.xb, b.xe});
  vector<int> y ({a.yb + (a.yb>=b.yb), a.ye - (a.ye <= b.ye), b.yb, b.ye});
  vector<int> z ({a.zb + (a.zb>=b.zb), a.ze - (a.ze <= b.ze), b.zb, b.ze});
  sort(x.begin(),x.end());
  sort(y.begin(),y.end());
  sort(z.begin(),z.end());
  x[3]++;
  y[3]++;
  z[3]++;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      for(int k = 0; k < 3; k++){
        c t = c(x[i],y[j],z[k],x[i+1]-1,y[j+1]-1,z[k+1]-1);
        bool am = a.mutex(t);
        bool bm = b.mutex(t);
        if(!bm){
          ob.insert(t);
          continue;
        }
        if(!am){
          o.insert(t);
        }
      }
    }
  }
  return pair<set<c>,set<c>>(o,ob);
}
  

  


int main(){
  string l;
  ifstream f("input");
  set<c> q;

  while(getline(f,l)){
    string b = "=.,xyz";
    for(int i = 0; i < l.size(); i++) if(b.find(l.substr(i,1)) != string::npos) l[i] = ' ';
    stringstream s(l);
    string t;
    int xb,xe,yb,ye,zb,ze;
    s >> t >> xb >> xe >> yb >> ye >> zb >> ze;
    set<c> n = {c(xb,yb,zb,xe,ye,ze)};
    set<c> temp;
    for(c x : q){
      set<c> ne;
      for(c y : n){
        pair<set<c>,set<c>> w = add(x,y);
        temp.insert(w.first.begin(),w.first.end());
        ne.insert(w.second.begin(),w.second.end());
      }
      n = ne;
    }
    q = temp;
    if(t == "on") q.insert(n.begin(),n.end());
    cout << q.size() << endl << endl;
  }

  int o = 0;
  for(auto g : q){
    o += g.vol();
  }

  cout << o << endl;

  return 0;
}
