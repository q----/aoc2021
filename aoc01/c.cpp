#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
  string l;
  ifstream f ("input");

  int p = 10000;
  int o = 0;
  int o2 = -3;

  int g = 0;
  int h = 0;
  int i = 0;
  
  while(getline(f, l)){
    stringstream s(l);
    int x;
    s >> x;

    if(x > p) o++;
    p = x;
    
    if(x > g) o2++;
    g = h;
    h = i;
    i = x;
  }
  
  cout << o << endl;
  cout << o2 << endl;
  return 0;
}
