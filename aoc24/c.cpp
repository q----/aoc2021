#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void parse(string l, vector<int>& r, string n, int& i){
  stringstream s(l);
  string a,b,c;
  int g;
  s >> a >> b;
  if(a == "inp"){
    r[b[0]-'w'] = n[i] - '0';
    i++;
    return;
  } else {
    s >> c;
    if(c[0] > '9'){
      g = r[c[0]-'w'];
    } else {
      g = stoi(c);
    }
    if(a == "add"){
      r[b[0]-'w'] += g;
    } else if(a == "mul"){
      r[b[0]-'w'] *= g;
    } else if(a == "div"){
      r[b[0]-'w'] /= g;
    } else if(a == "mod"){
      r[b[0]-'w'] %= g;
    } else {
      r[b[0]-'w'] = (r[b[0]-'w'] == g)?1:0;
    }
  }
}
  

bool test(string l, vector<string>& inst){
  vector<int> r = {0,0,0,0};
  int i = 0;
  for(auto t : inst){
    parse(t,r,l, i);
  }
  return (r[3]==0);
}

bool testabv(string l, vector<int>& l7, vector<int>& l6, vector<int>& l17){
  int z = 0;
  for(int i = 0; i < l.size(); i++){
    bool t = (z%26 + l7[i] == l[i]-'0');
    z = z/l6[i] * ((t)?1:26) + (t)?0:(l[i]-'0'+l17[i]);
  }
  return z == 0;
}


int main(){
  string l;
  ifstream f("input");

  vector<string> inst;
  while(getline(f,l)) inst.push_back(l);

  long long int high = 39494195799979;
  long long int low = 13161151139617;

  if(test(to_string(high),inst)){
    cout << high << endl;
  } else {
    cout << "uh oh!" << endl;
  }
  if(test(to_string(low),inst)){
    cout << low << endl;
  } else {
    cout << "uh oh!" << endl;
  }


  return 0;
}
