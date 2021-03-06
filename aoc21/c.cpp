#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct g{
  int p1;
  int p1s = 0;
  int p2;
  int p2s = 0;
  int t = 0;
  bool p1t = true;
  g(int a, int b){
    p1 = a;
    p2 = b;
  }
};

const bool operator<(const g& lhs, const g& rhs){
  if(lhs.p1s + lhs.p2s != rhs.p1s + rhs.p2s) return lhs.p1s + lhs.p2s < rhs.p1s + rhs.p2s;
  if(lhs.p1s != rhs.p1s) return lhs.p1s < rhs.p1s;
  if(lhs.p2s != rhs.p2s) return lhs.p2s < rhs.p2s;
  if(lhs.p1 != rhs.p1) return lhs.p1 < rhs.p1;
  if(lhs.p2 != rhs.p2) return lhs.p2 < rhs.p2;
  if(lhs.p1t != rhs.p1t) return rhs.p1t;
  return false;
}

g turn(g s, int roll){
  if(s.p1t){
    s.p1 = (s.p1 + roll) % 10;
    s.p1s += (s.p1 == 0)?10:s.p1;
  } else {
    s.p2 = (s.p2 + roll) % 10;
    s.p2s += (s.p2 == 0)?10:s.p2;
  }
  s.p1t = !s.p1t;
  return s;
}

int main(){
  int p1 = 8;
  int p2 = 5;
  g init (p1,p2);

  while(init.p1s < 1000 && init.p2s < 1000) init = turn(init, ++init.t + ++init.t + ++init.t);
  cout <<  min(init.p1s,init.p2s) * init.t << endl;

  g init2 (p1,p2);
  map<g,long long int> s;
  s[init2] = 1;
  g p1w(0,0);
  p1w.p1s = 420;
  g p2w(0,0);
  p2w.p2s = 420;

  vector<int> rolls = {3,4,5,6,7,8,9};
  vector<int> freq  = {1,3,6,7,6,3,1};

  do{
    auto it = s.begin();
    g t = (*it).first;
    long long int x = (*it).second;
    s.erase(it);
    for(int r = 0; r < rolls.size(); r++){
      g c = turn(t, rolls[r]);
      
      if(c.p1s >= 21 || c.p2s >= 21)
        c = (c.p1s >= 21)?p1w:p2w;

      s[c] += x * freq[r]; 
    }
  } while(s.size() > 2);

  cout << ((s[p1w] > s[p2w])?s[p1w]:s[p2w]) << endl;

  return 0;
}
