#include <emscripten/bind.h>
#include <string>
#include <vector>

using namespace emscripten;
using namespace std;

vector<int> returnVectorData () {
  vector<int> v(10, 1);
  return v;
}

map<int, string> returnMapData () {
  map<int, string> m;
  m.insert(pair<int, string>(10, "hello map"));
  return m;
}

EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("returnVectorData", &returnVectorData);
  emscripten::function("returnMapData", &returnMapData);

  // register bindings for vector<int> and map<int, string>.
  emscripten::register_vector<int>("vector<int>");
  emscripten::register_map<int, string>("map<int, string>");
}

/**
emcc -O3 -Wall -Werror --bind   map.cpp


emcc -O3  -Wall -Werror --bind     \
    map2.cpp \
    -s ALLOW_MEMORY_GROWTH 

*/