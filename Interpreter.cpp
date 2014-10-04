#include <iostream>
#include <vector>
#include <string>
#include <Interpreter.h>

void BrainFuck::Interpreter::interact(std::istream& token_stream) 
{
  std::vector<unsigned char> token_buffer{};
  while (token_stream.good()) {
    unsigned char chr = (unsigned char) token_stream.get();
    if (chr == '<' || chr == '>' || 
        chr == '.' || chr == ',' ||
        chr == '[' || chr == ']' ||
        chr == '+' || chr == '-') {
      token_buffer.push_back(chr);
    }
  }

  int token_stream_len = token_buffer.size();
  for (int token_pos = 0; token_pos < token_stream_len;) {
    unsigned char next_token = token_buffer[token_pos];
    switch(next_token) {
      case '>':
        ++this->heap_pos;
        break;

      case '<':
        --this->heap_pos;
        if (0 > this->heap_pos) {
          throw std::runtime_error("token position went out of range!");
        }
        break;

      case '+':
        this->rt_heap.incr(this->heap_pos);
        break;

      case '-':
        this->rt_heap.decr(this->heap_pos);
        break;

      case '.':
        std::cout.put((char) this->rt_heap.read(this->heap_pos));
        break;

      case ',':
        if (std::cin.good()) {
          this->rt_heap.store(this->heap_pos, (unsigned char) std::cin.get());
        }
        break;

      case '[':
        if (!this->rt_heap.read(this->heap_pos)) {
          while(']' != token_buffer[token_pos]) {
            ++token_pos;
            if (token_pos >= token_stream_len) {
              throw std::runtime_error(std::string("fatal: syntax error"));
            }
          }
          ++token_pos;
          continue;
        }
        break;

      case ']':
        if (this->rt_heap.read(this->heap_pos)) {
          while('[' != token_buffer[token_pos]) {
            --token_pos;
            if (token_pos < 0) {
              throw std::runtime_error(std::string("fatal: syntax error"));
            }
          }
          continue;
        }
        break;

      default:
        throw std::runtime_error(std::string("invalid token: ") + std::string(1,next_token));
    }
    ++token_pos;
  }
}
