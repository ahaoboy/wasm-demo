#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <emscripten/bind.h>
#include <emscripten.h>
#include <vector>

using namespace emscripten;
using namespace std;

extern "C" {
    int* inc(int* data,int size);
}

extern "C" {
    int* createIntArray(int size);
}

int* inc(int* data,int size){
    int byteSize = sizeof(int) * size;
    cout<<"byteSize:"<<byteSize<<"size:"<<size<<endl;
    int* p2 = (int*)malloc(byteSize);

    memcpy(p2, data, byteSize);
    for(int i=0;i<size;i++)
        p2[i] = data[i]+1;
    
    for(int i=0;i<size;i++)
        cout<<"inc=>"<<i<<" "<<data[i]<<" "<<p2[i]<<endl;
    return p2;
}
 
int* createIntArray(int size){
    return new int[size];
}
 
int main(int argc, char **argv)
{
    // int* p2 = createIntArray(3);
    // int list[] = {1,2,3};
    // int size = 3;
    // int* p = inc(list,size);

    // for(int i=0;i<size;i++)
    // {
    //     cout<<list[i]<<" ==> "<<p[i]<<endl;
    // }
    return 0;
}
// EMSCRIPTEN_BINDINGS(module) {
//  emscripten::function("inc", &inc,emscripten::allow_raw_pointers());
//   emscripten::function("createIntArray", &createIntArray,emscripten::allow_raw_pointers());
  // register bindings for std::vector<int> and std::map<int, std::string>.
//   register_vector<int>("int*");
//   register_map<int, std::string>("int*");
// }
/*
emcc -O3 -s WASM=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
    -s EXPORTED_FUNCTIONS='["_main","_embind_register_function","_inc","_createIntArray"]' \
    -s ASSERTIONS=1 \
    -s ALLOW_MEMORY_GROWTH \
     array.cpp



emcc -O3 -s WASM=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_inc","_createIntArray"]' \
    -s ALLOW_MEMORY_GROWTH \
     array.cpp

*/