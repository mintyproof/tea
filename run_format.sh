#!/bin/bash
find src/ -print0 -iname "*.cpp" -o -iname "*.h" | xargs clang-format -i