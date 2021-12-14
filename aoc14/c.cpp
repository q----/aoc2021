#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string mid(string t, map<string,string> in){
  string o = "";
  for(int i = 0; i < t.size() - 1; i++){
    o += in[t.substr(i,2)];
  }
  return o;
}

string com(string t, string x){
  string o = "";
  for(int i = 0; i < t.size()-1; i++){
    o += string(1, t[i]) + string(1, x[i]);
  }
  o += string(1, t[t.size() -1]);
  return o;
}

long long int count(string t){
  map<char,long long int> count;

  for(char c : t) count[c]++;
  long long int min = 1000000000000;
  long long int max = 0;
  for(auto c : count){
    min = (min < c.second)?min:c.second;
    max = (max < c.second)?c.second:max;
  }

  return max - min;
}

int main(){
  string l;
  string t;
  ifstream f("input");
  getline(f,t);
  //map<string,int> q;
  //for(int i = 0; i < t.size() - 1; i++)q[t.substr(i,2)]++;



  getline(f,l);
  map<string,string> in;


  while(getline(f,l)){
    string x,y,z;
    stringstream s(l);
    s >> x >> y >> z;
    in.insert(pair<string,string>(x,z));
  }

  for(int i = 0; i < 10; i++){
    string x = mid(t, in);
    t = com(t,x);
  }

  cout << count(t) << endl;

  for(int i = 10; i < 40; i++){
    string x = mid(t, in);
    t = com(t,x);
  }

  cout << count(t) << endl;

  return 0;
}
