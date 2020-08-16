#include <iostream> 
#include <vector> 
#include <stack>
#include <map>

using namespace std; 
  
// Driver Method 
int main() 
{ 
    // Initializing 2D vector "vect" with 
    // sample values 
    vector<vector<int> > vec{ { 1, 2, 3 }, 
                              { 4, 5, 6 }, 
                              { 7, 8, 9 } }; 
  
    // Removing elements from the 
    // last row of the vector 
    vec[2].pop_back(); 
    vec[1].pop_back(); 
  
    // Displaying the 2D vector 
    for (int i = 0; i < 3; i++) { 
        for ( 
            auto it = vec[i].begin(); 
            it != vec[i].end(); it++) 
            cout << *it << " "; 
        cout << endl; 
    } 


        stack <int>stk;
    //入栈
    for(int i=0;i<50;i++){
        stk.push(i);
    }
    cout<<"栈的大小:"<<stk.size()<<endl;
    while(!stk.empty())
    {
        cout<<stk.top()<<endl;
        stk.pop();
    }
    cout<<"栈的大小:"<<stk.size()<<endl;
    

    std::map<int,bool> m ;
    m[1] = true;
    m[2]= false;
    cout<<"1:"<<m[1]<<endl;
    cout<<"2:"<<m[2]<<endl;
    return 0; 
} 

/*
emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
    v.cpp \
    -s ALLOW_MEMORY_GROWTH 
*/