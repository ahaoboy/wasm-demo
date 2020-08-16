#include <emscripten.h>
#include <iostream>
using namespace std;

extern "C"
{
    int *fibArray(int *data, int size);
    int fib(int n);
}

int fib(int n)
{
    return n < 2 ? n : fib(n - 1) + fib(n - 2);
}

int *fibArray(int *data, int size)
{
    int byteSize = sizeof(int) * size;
    cout << "byteSize:" << byteSize << "size:" << size << endl;
    int *ptr = (int *)malloc(byteSize);
    for (int i = 0; i < size; i++)
    {
        ptr[i] = fib(data[i]);
        data[i]++;
    }
    for (int i = 0; i < size; i++)
    {
        cout
            << "inc=>" << i << " " << data[i] << " " << ptr[i] << endl;
    }
    return ptr;
}
int main(int argc, char **argv)
{
    return 0;
}
/*

emcc -O3    \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fibArray","_fib"]' \
    -s ALLOW_MEMORY_GROWTH \
    -s ENVIRONMENT='web' \
    fibArray.cpp


emcc -O3   \
    -s WASM=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fibArray","_fib"]' \
    -s ALLOW_MEMORY_GROWTH \
    -s ENVIRONMENT='web' \
    -s EXPORT_ES6=1 \
    -s MODULARIZE=1 \
    -s STRICT=1 \
    -o fibArray.js \
    --bind \
    fibArray.cpp





emcc -O3   \
    -s WASM=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fibArray","_fib"]' \
    -s ALLOW_MEMORY_GROWTH \
    -o fibArray.js \
    -s STRICT=1 \
    --bind \
    fibArray.cpp

emcc -O3   \
    -s WASM=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fibArray","_fib"]' \
    -s ALLOW_MEMORY_GROWTH \
    -s ENVIRONMENT='web' \
    -o fibArray.js \
    fibArray.cpp

*/