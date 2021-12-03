#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

int conv(string s){
  int x= 0;
  int y = 0;
  int t = 1;
  for(int i = s.size()-1; i >= 0; i--){
    if(s[i] == '1'){
      y += t;
    } else {
      x += t;
    }
    t *= 2;
  }
  return x * y;
}


int main(){
  string l;
  ifstream f("input");

  map<int,int> res;
  

  while(getline(f,l)){
    for(int i = 0; i < l.size(); i++){
      res[i] += (l[i] == '1')? 1:-1;
      
    }
  }
  stringstream s;

  for(int i = 0; i < 12; i++){
    s << (res[i] > 0)?1:0;
  }

  cout << conv(s.str()) << endl;

  


  return 0;
}
