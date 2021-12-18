#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string explode(string c){
  int b = 0;
  int x = 0;
  int z = 0;
  for(int i = 0; i < c.size(); i++){
    if(c[i] == ',') z = i;
    if(c[i] == '['){
      b++;
      x = i;
      continue;
    }
    if(c[i] == ']'){
      b--;
      if(b < 4) continue;
      int q = -1;
      int e = -1;
      int g,j;
      for(g = x; g > 0; g--){
        if(c[g] < '0' || c[g] > '9') continue;
        q = g;
        while(c[g-1] >= '0' && c[g-1] <= '9') g--;
        break;
      }
      for(j = i; j < c.size(); j++){
        if(c[j] < '0' || c[j] > '9') continue;
        e = j;
        while(c[j+1] >= '0' && c[j+1] <= '9') j++;
        break;
      }
      int w = -1;
      if(q != -1){
        w = stoi(c.substr(g,q-g+1));
        w += stoi(c.substr(x+1,z-x-1));
      }
      int y = -1;
      if(e != -1){
        y = stoi(c.substr(e,j-e+1));
        y += stoi(c.substr(z+1, i-z-1));
      }
      string o = "";
      if(w != -1){
        o += c.substr(0,g) + to_string(w) + c.substr(q+ 1, x - q-1);
      } else {
        o += c.substr(0,x);
      }
      if(y != -1){
        o += "0" + c.substr(i+1,e-i-1) + to_string(y) + c.substr(j+1);
      } else {
        o += "0" + c.substr(i+1);
      }
      return o;
    }
  }

  return c;
}

string reduce(string c){
  for(int i = 0; i < c.size() - 1; i++){
    if(c[i] < '0' || c[i] > '9') continue;
    if(c[i+1] < '0' || c[i] > '9') continue;
    if(stoi(c.substr(i,2)) <= 9) continue;
    c = c.substr(0,i) + "[" + to_string(stoi(c.substr(i,2))/2) + "," + to_string(stoi(c.substr(i,2))/2 + stoi(c.substr(i,2)) % 2) + "]" + c.substr(i+2);
    break;
  }
  return c;
}

string sa(string c){
  string o;
  do{
    o = c;
    c = explode(c);
    
    if(o!=c) continue;
    c = reduce(c);
  }while(o != c);
  return c;
}

int mag(string c){
  int x = -1;
  int z = -1;
  int i;
  for(i = 0; i < c.size(); i++){
    if(c[i] == '[') x = i;
    if(c[i] == ',') z = i;
    if(c[i] == ']'){
      int l = 3 * stoi(c.substr(x+1,z-x -1)) + 2 * stoi(c.substr(z+1,i-z-1));
      c = c.substr(0,x) + to_string(l) + c.substr(i+1);
      return mag(c);
    }
  }

  return stoi(c);
}

int main(){
  string l,c;
  ifstream f("input");
  vector<string> num;
  getline(f,c);
  num.push_back(c);

  c = sa(c);

  while(getline(f,l)){
    num.push_back(l);
    c = "[" + c + "," + l + "]";
    c = sa(c);
  }

  cout << mag(c) << endl;

  int max = 0;

  for(int i = 0; i < num.size(); i++){
    for(int j = 0; j < num.size(); j++){
      if(i == j) continue;
      int x = mag(sa("[" + sa(num[i]) + "," + num[j] + "]"));
      max = (max > x)?max:x;
    }
  }

  cout << max << endl;

  return 0;
}
