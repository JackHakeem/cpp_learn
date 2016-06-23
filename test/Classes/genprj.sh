#!/bin/sh

ctags -R . -h ".c.h.cpp.hpp.lua.proto"


find -L . -name "*.h" -o -name "*.cpp" -o -name "*.proto" -o -name "*.c" -o -name "*.hpp" -o -name "*.lua" > ./cscope.files
cscope -bqk -i cscope.files -f cscope.out
