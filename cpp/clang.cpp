#include <iostream>
#include <string>
#include <utility>

template <class... T> auto pack(T... t) {
  // Now legal in  C++20
  return [... t = std::move(t)](auto &&f) { f(t...); };
};

// Forgive me Kate Gregory
void f(int age, const std::string &name) {
  std::cout << "I am " << name << " and am " << age << " years old\n";
}
int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << " Provide my age then my name\n";
    return -1;
  }

  int age = std::stoi(argv[1]);
  std::string name = argv[2];
  auto func = pack(age, name);
  func(f);
  return 0;
}