CLANG_CXX = $(shell which clang++)

C++11=$(CLANG_CXX) -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat

all: link test

compile: Env.h Interpreter.h Interpreter.cpp main.cpp
	$(C++11) -c -I. Interpreter.cpp main.cpp

link: compile
	$(C++11) Interpreter.o main.o -o brain_fuck

test: HelloWorld.bf
	@echo "Testing..."
	./brain_fuck HelloWorld.bf
	exit $$?
clean:
	rm -f *.o brain_fuck
