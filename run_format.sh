#!/bin/bash
find src/ -iname *.cpp -o -iname *.h | xargs clang-format -i