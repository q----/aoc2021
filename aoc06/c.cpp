#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

map<int,long long int> day(map<int, long long int> q){
  map<int,long long int> o;
  for(int i = 0; i < 9; i++){
    o[i] = q[(i+1) % 9];
  }
  o[6] += q[0];
  return o;
}

int main(){
  string l;
  ifstream f("input");

  getline(f,l);

  for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';
  stringstream s(l);
  int x;
  map<int, long long int> q;
  while(s >> x) q[x]++;

  for(int i = 0; i < 80; i++) q = day(q);

  long long int o = 0;
  for(auto a : q) o += a.second;

  cout << o << endl;

  for(int i = 80; i < 256; i++) q = day(q);
  
  o = 0;
  for(auto a : q) o += a.second;

  cout << o << endl;

  return 0;
}
