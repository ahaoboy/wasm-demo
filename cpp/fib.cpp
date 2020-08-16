#include <emscripten.h>

extern "C"
{
    int fib(int n);
}

int fib(int n)
{
    return n < 2 ? n : fib(n - 1) + fib(n - 2);
}
int main(int argc, char **argv)
{
    return 0;
}
/*

emcc -O3 -s   \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fib"]' \
    -s ALLOW_MEMORY_GROWTH \
     fib.cpp

*/