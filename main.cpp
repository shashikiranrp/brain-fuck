#include <Env.h>
#include <Interpreter.h>
#include <iostream>
#include <fstream>

using namespace BrainFuck;

int main(int argc, char* argv[]) {
  if (1 >= argc) {
    std::cout << "usage: " << argv[0] << " <file_name> " << std::endl;
    return 1;
  }
  Env env{BrainFuck::DEFAULT_HEAP_SIZE};
  Interpreter interpreter(env);
  std::ifstream fs = std::ifstream(argv[1]);
  std::istream& is = fs;
  interpreter.interact(is);
  return 0;
}
