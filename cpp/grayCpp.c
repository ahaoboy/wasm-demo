#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void grayCpp(uint8_t *data, int w, int h)
{
    int i,j;
    uint8_t g;
          int size = w * h;
        for (  i = 0; i < size; i++) {
              j = i * 4;
             g = ((data[j] + data[j + 1] + data[j + 2]) / 3);
            // const g = Number((data[j] + data[j + 1] + data[j + 2]) / 3)
            data[j] = data[j + 1] = data[j + 2] = g;
        }
}


EMSCRIPTEN_KEEPALIVE
uint8_t* create_buffer(int width, int height)
{
    return  (uint8_t *)malloc(width * height * 4 * sizeof(uint8_t));
}

int main(int argc, char **argv)
{
  // int i;
  // for (i = 0; i < 10; i++)
    // printf("hello %d %d \n", i, fib(1));
    create_buffer(1,1);
  return 0;
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


*/