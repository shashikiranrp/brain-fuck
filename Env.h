#ifndef ENV_H
#define ENV_H

#include <exception>
#include <string>

namespace BrainFuck {

  const int DEFAULT_HEAP_SIZE = 1024 * 10; // 10 KB
  class Env {
    int heap_size;
    unsigned char* heap;

    public:
      Env(int hs) : heap_size{hs}, heap{new unsigned char[heap_size]{0}} {
      }
      Env(const Env&) = delete;
      Env& operator=(const Env&) = delete;
      Env(Env&& other_env) {
        this->heap_size = other_env.heap_size;
        this->heap = other_env.heap;
        other_env.heap_size = 0;
        other_env.heap = nullptr;
      }
      ~Env() {delete []heap;}
      
      void store(int pos, unsigned char value) {
        if (pos >= this->heap_size) {
          throw std::runtime_error(std::string("store: invalid address: ") + std::to_string(pos));
        } else {
          *(this->heap + pos) = value;
        }
      }

      unsigned char read(int pos) {
        if (pos >= this->heap_size) {
          throw std::runtime_error(std::string("read: invalid address: ") + std::to_string(pos));
        } else {
          return *(this->heap + pos);
        }
      }

      unsigned char incr(int pos) {
        if (pos >= this->heap_size) {
          throw std::runtime_error(std::string("incr: invalid address: ") + std::to_string(pos));
        } else {
          return (*(this->heap + pos))++;
        }
      }

      unsigned char decr(int pos) {
        if (pos >= this->heap_size) {
          throw std::runtime_error(std::string("decr: invalid address: ") + std::to_string(pos));
        } else {
          return (*(this->heap + pos))--;
        }
      }
  };
}
#endif
