#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int abs(int i){
  return (i < 0)? -i:i;
}

long long int tri(int i){
  long long int o = 0;
  for(i = abs(i); i >0; i--) o+= i;
  return o; 
}

int main(){
  string l;
  ifstream f("input");
  vector<int> c;
  getline(f,l);
  for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';

  stringstream s(l);

  int x;
  
  while(s>>x) c.push_back(x);

  int q = 10000000;
  long long int q2 = 10000000000000;


  for(int o = 0; o < 1000; o++){

    int out = 0;
    long long int out2 = 0;

    for(int i : c) out += abs(i-o);
    for(int i : c) out2 += tri(i-o);

    if(out < q) q = out;
    if(out2 < q2) q2 = out2;
  }

  cout << q << endl;
  cout << q2 << endl;


  return 0;
}
