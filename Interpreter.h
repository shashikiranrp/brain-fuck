#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <istream>
#include <Env.h>

namespace BrainFuck {
  
  class Interpreter {
    private:
      Env &rt_heap;
      int heap_pos;

    public:
      Interpreter(const Interpreter&) = delete;
      Interpreter& operator=(const Interpreter&) = delete;
      Interpreter(Env &heap) : rt_heap{heap}, heap_pos{}{
      } 

      void interact(std::istream&);
  };
}

#endif
