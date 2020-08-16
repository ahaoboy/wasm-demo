#include <emscripten.h>
#include <iostream>
#include <map>
#include <stack>
#include <stdlib.h>

using namespace std;

inline void setColor(uint8_t *data, int x, int y, int w, uint8_t *c) {
  for (int i = 0; i < 4; i++) {
    data[(y * w + x) * 4 + i] = c[i];
  }
}

inline uint8_t *getColor(uint8_t *data, int x, int y, int w) {
  return data + (y * w + x) * 4;
}

inline bool compare(uint8_t *c1, uint8_t *c2) {
  int d = abs(c1[0] - c2[0]) + abs(c1[1] - c2[1]) + abs(c1[2] - c2[2]);
  return d < 100;
}

extern "C" {
void fillWasm(uint8_t *data, int x, int y, int w, int h);
}

inline bool canVisit(map<int, bool> &v, int x, int y, int w, int h) {
  if (x < 0 || y < 0 || x >= w || y >= h)
    return 0;
  return !v[(x << 16) + y];
}

inline void setVisit(map<int, bool> &v, int x, int y, bool value) {
  v[(x << 16) + y] = value;
}

void fillWasm(uint8_t *data, int x, int y, int w, int h) {
  int byteSize = w * h * 4;
  uint8_t *dataMock = new uint8_t[byteSize];
  memcpy(dataMock, data, byteSize);

  uint8_t *sourceColor = getColor(dataMock, x, y, w);
  uint8_t fillColor[] = {98, 237, 240, 255};
  uint8_t redColor[] = {255, 0, 0, 255};

  map<int, bool> v;
  int directionSize = 4;
  int direction[4][2] = {
      {0, 1},
      {0, -1},
      {1, 0},
      {-1, 0},
  };

  stack<int *> st;
  int init[3] = {x, y, 0};
  st.push(init);

  int count = 0;
  while (st.size()) {
    count++;
    int *top = st.top();
    int tx = top[0];
    int ty = top[1];
    int td = top[2];
    setColor(data, tx, ty, w, fillColor);
    setVisit(v, tx, ty, 1);

    if (td == directionSize) {

      st.pop();
      continue;
    }

    int dx = direction[td][0];
    int dy = direction[td][1];
    int nx = tx + dx;
    int ny = ty + dy;
    top[2]++;
    if (canVisit(v, nx, ny, w, h) &&
        compare(sourceColor, getColor(dataMock, nx, ny, w))) {
      int *ptr = new int[3];
      ptr[0] = nx;
      ptr[1] = ny;
      ptr[2] = 0;
      st.push(ptr);
      setVisit(v, tx, ty, 1);
    } else if (nx >= 0 && ny >= 0 && nx < w && ny < h &&
               !compare(sourceColor, getColor(dataMock, nx, ny, w))) {
      setColor(dataMock, nx, ny, w, redColor);
    }
  }
  cout << "count:" << count << endl;
}

int main(int argc, char **argv) { return 0; }
/*

emcc -O3 -s   \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' \
    -s EXPORTED_FUNCTIONS='["_main","_fillWasm"]' \
    -s ALLOW_MEMORY_GROWTH \
     fillWasm.cpp

*/