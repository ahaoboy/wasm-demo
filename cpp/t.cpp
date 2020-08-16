#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

int main() {
  printf("hello, world!\n");
      int direction[4][2] = {
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
    }; 

  for(int i=0;i<4;i++)
  cout<<direction[i][0]<<"__"<<direction[i][1]<<endl;

  stack<int*> st;
  int a[3] = {1,2,3};
  st.push(a);
  
  int* p1 = st.top();
  cout<<p1[0]<<"--"<<p1[1]<<"--"<<p1[2]<<endl;
  cout<<st.size()<<endl;
  return 0;
}