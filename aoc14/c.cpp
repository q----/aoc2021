#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <climits>

using namespace std;

long long int count(map<string, long long int> t, string orig){
  map<char,long long int> count;
  count[orig[0]]++;
  count[orig[orig.size()-1]]++;

  for(auto c : t) for(auto x : c.first) count[x] += c.second;

  long long int min = LLONG_MAX;
  long long int max = 0;

  for(auto c : count){
    min = (min < c.second)?min:c.second;
    max = (max < c.second)?c.second:max;
  }

  return (max - min) / 2;
}

map<string,long long int> step(map<string, long long int> q, map<string, string> in){
  map<string, long long int> o;
  for(auto a : q){
    o[a.first[0] + in[a.first]] += a.second;
    o[in[a.first] + a.first[1]] += a.second;
  }
  return o;
}

int main(){
  string l;
  string t;
  ifstream f("input");
  getline(f,t);
  
  map<string,long long int> q;
  for(int i = 0; i < t.size() - 1; i++) q[t.substr(i,2)]++;
  getline(f,l);

  map<string,string> in;
  while(getline(f,l)){
    stringstream s(l);
    string x,y,z;
    s >> x >> y >> z;
    in.insert(pair<string,string>(x,z));
  }

  for(int i = 0; i < 10; i++) q = step(q, in);
  cout << count(q, t) << endl;

  for(int i = 10; i < 40; i++) q = step(q, in);
  cout << count(q, t) << endl;

  return 0;
}
