#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <stack>

using namespace emscripten;

std::vector<int> returnVectorData () {
  std::vector<int> v(10, 1);
  return v;
}

std::map<int, std::string> returnMapData () {
  std::map<int, std::string> m;
  m.insert(std::pair<int, std::string>(10, "This is a string."));
  return m;
}

std::stack<int> returnStackData(){
  std::stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);
  return st;
}

EMSCRIPTEN_BINDINGS(module) {
  function("returnVectorData", &returnVectorData);
  function("returnMapData", &returnMapData);
  function("returnStackData", &returnStackData);

  // register bindings for std::vector<int> and std::map<int, std::string>.
  register_vector<int>("vector<int>");
  register_map<int, std::string>("map<int, string>");
  register_stack<int>("stack<int>");
}

/**
emcc -O3 -s WASM=1   map.cpp \
     \
 
emcc -O3  -Wall -Werror --bind     \
    stack.cpp \
    -s ALLOW_MEMORY_GROWTH
*/