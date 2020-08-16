#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>
#include <cstring>
#include <emscripten/bind.h>

EMSCRIPTEN_KEEPALIVE 
uint8_t* grayCpp(uint8_t *data, int w, int h)
{   
int dataSize = h * w * 4 * sizeof(uint8_t);
uint8_t* gray =  (uint8_t *)malloc(dataSize);
  memcpy(gray, data,dataSize);
  int i,j;
    uint8_t g;
    int size = w * h;
    for (  i = 0; i < size; i++) {
        j = i * 4;
        g = ((data[j] + data[j + 1] + data[j + 2]) / 3);
        // const g = Number((data[j] + data[j + 1] + data[j + 2]) / 3)
        gray[j] = gray[j + 1] = gray[j + 2] = g;
    }
    return gray;
}
extern "C" uint8_t* EMSCRIPTEN_KEEPALIVE
create_buffer(int width, int height)
{
    // return  (uint8_t *)malloc(width * height * 4 * sizeof(uint8_t));
    return  new uint8_t[width * height * 4 * sizeof(uint8_t)];
}


EMSCRIPTEN_BINDINGS(module){
    emscripten::function("grayCpp",*grayCpp,emscripten::allow_raw_pointers());
    emscripten::function("create_buffer",*create_buffer,emscripten::allow_raw_pointers());
    // emscripten::function("f2",&f2);
    // emscripten::function("f3",&f3);
    // emscripten::register_vector<vector<int>>("vector<vector<int>>");
    // emscripten::register_map<int,bool>("map<int,bool>");
    // emscripten::register_stack<int>("stack<int>");
}
// emcc fib.c -s WASM=1 -s -o fib.html
// emcc fib.cpp -s WASM=1 -s -o fib.html

// emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","fib"]' fib.cpp
// emcc -O3 -s WASM=1   -s ALLOW_MEMORY_GROWTH  -s  EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","create_buffer","grayCpp"]' grayCpp.cpp
// emcc -O3 -s WASM=1   -s ALLOW_MEMORY_GROWTH  -s  EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","create_buffer","grayCpp"]' grayCpp.c


/*

emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
    -I libwebp \
     grayCpp.cpp \
    -s ALLOW_MEMORY_GROWTH \

 emcc -O3 -s WASM=1   -s ALLOW_MEMORY_GROWTH  -s  EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","fib"]' grayCpp.cpp
   emcc -O3 -s WASM=1   -s ALLOW_MEMORY_GROWTH  -s  EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall","create_buffer","grayCpp"]' grayCpp.cpp

emcc -O3  -Wall -Werror --bind -s  EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'  \
    grayCpp.cpp \
    -s ALLOW_MEMORY_GROWTH 
*/