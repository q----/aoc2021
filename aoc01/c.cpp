#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

int main(){
  string l;
  ifstream f ("input");

  int p = 10000;
  int o = 0;
  int o2 = 0;

  queue<int> g ({p,p,p});
  
  while(getline(f, l)){
    stringstream s(l);
    int x;
    s >> x;

    if(x > p) o++;
    p = x;
    
    if(x > g.front()) o2++;
    g.pop();
    g.push(x);
  }
  
  cout << o << endl;
  cout << o2 << endl;

  return 0;
}
