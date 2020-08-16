#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>
#include <iostream>
using namespace std;
extern "C"
{
    uint8_t *grayCpp(uint8_t *data, int w, int h);
}
uint8_t *grayCpp(uint8_t *data, int w, int h)
{
    int byteSize = sizeof(uint8_t) * w * h * 4;
    cout << "byteSize:" << byteSize << endl;
    uint8_t *ptr = (uint8_t *)malloc(byteSize);

    memcpy(ptr, data, byteSize);
    uint8_t g;
    int size = w * h;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        j = i * 4;
        g = (data[j] + data[j + 1] + data[j + 2]) / 3;
        data[j] = data[j + 1] = data[j + 2] = g;
        // ptr[j] = ptr[j + 1] = ptr[j + 2] = g;
    }

    // return ptr;
    return data;
}

int main(int argc, char **argv)
{
    return 0;
}
/*

emcc -O3 -s   \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_grayCpp"]' \
    -s ALLOW_MEMORY_GROWTH \
     grayCpp.cpp

*/