#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
  string l;
  ifstream f ("input");
  int h = 0;
  int d = 0;
  int a = 0;

  while(getline(f,l)){
    stringstream s(l);
    string i;
    int x;
    s >> i >> x;

    if(i == "up"){
      a -= x;
    } else if(i == "down"){
      a += x;
    } else if(i == "forward"){
      h += x;
      d += x * a;
    }
  }

  cout << h * a << endl;
  cout << h * d << endl;

  return 0;
}
