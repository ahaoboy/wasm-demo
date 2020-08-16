#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream> 
#include <vector> 
#include <stack>
#include <map>

using namespace std; 
using namespace emscripten;

map<int,bool> f1(){
    map<int,bool> m;
    for(int i=0;i<5;i++)
        m[i] = i & 1;
    return m;    
}

stack<int> f2(){
    stack<int> stk;
   for(int i=0;i<3;i++){
        stk.push(i);
    }

    return stk;
}

vector<vector<int>> f3(){
    vector<vector<int> > vec{ { 1, 2, 3 }, 
                              { 4, 5, 6 }, 
                              { 7, 8, 9 } }; 

                              return vec;
}


EMSCRIPTEN_BINDINGS(module){
    emscripten::function("f1",&f1);
    emscripten::function("f2",&f2);
    emscripten::function("f3",&f3);
    emscripten::register_vector<vector<int>>("vector<vector<int>>");
    emscripten::register_map<int,bool>("map<int,bool>");
    emscripten::register_stack<int>("stack<int>");
}
// Driver Method 
int main() 
{ 
    // Initializing 2D vector "vect" with 
    // sample values 
    vector<vector<int>> vec = f3();
  
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

        stack <int> stk =f2();
    //入栈
 
    cout<<"栈的大小:"<<stk.size()<<endl;
    while(!stk.empty())
    {
        cout<<stk.top()<<endl;
        stk.pop();
    }
    cout<<"栈的大小:"<<stk.size()<<endl;
    

    std::map<int,bool> m =  f1() ;
    cout<<"1:"<<m[1]<<endl;
    cout<<"2:"<<m[2]<<endl;
    cout<<"3:"<<m[3]<<endl;
    cout<<"4:"<<m[4]<<endl;
    return 0; 
} 

/*
emcc -O3  -Wall -Werror --bind -s WASM=1    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
    std.cpp \
    -s ALLOW_MEMORY_GROWTH 
*/