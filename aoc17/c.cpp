#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int tri(int t){
  return t * (t-1)/2;
}

int ypo(int y, int t){
  return y * t - tri(t);
}

int xpo(int x, int t){
  return (t<x)?tri(x)-tri(x-t):tri(x);
}

int xmx(int x){
  return xpo(x,x);
}

int ymx(int y){
  return ypo(y,y);
}

double quad(double a, double b, double c){
  return (-b + sqrt(b*b - 4 * a * c))/2/a;
}

int xmxinv(int g){
  return ceil(quad(1,-1,2*g));
}

bool valid(int x, int y, vector<int> min, vector<int> max){
  //should be something that can be done wrt getting a range for t that only includes values that are good for y in this way
  //int tmx = ceil(quad(-0.5, ((double) y) + 0.5, -1 * max[1]));
  //int tmn = floor(quad(-0.5, ((double) y) + 0.5, -1 * min[1]));
  //cout << tmn << " " << tmx << endl;
  for(int t = 0; t <= 10000; t++){
    if(ypo(y,t) > max[1]) continue;
    if(ypo(y,t) < min[1]) break;
    if(xpo(x,t) > max[0]) break;
    if(xpo(x,t) >= min[0] && xpo(x,t) <= max[0]) return true;
  }
  return false;
}
  

pair<int,int> mx(vector<int> min, vector<int> max){
  int m = 0;
  int p = 0;
  for(int x = xmxinv(min[0]); x <= max[0] + 1; x++){
    for(int y = min[1]; y < 400; y++){
      if(valid(x,y,min,max)){
        m = (m > ymx(y))?m:ymx(y);
        p++;
      }
    }
  }
  return pair<int,int>(m,p);
}

int main(){
  vector<int> min ({56,-162});
  vector<int> max ({76,-134});

  pair<int,int> ans = mx(min,max);
  cout << ans.first << endl;
  cout << ans.second << endl;
  
  return 0;
}
