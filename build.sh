#! /usr/bin/env -S bash -euo pipefail
g++ -g -O2 -fPIC $(find src -name "*.cpp") -I. -shared -o lib/libbzsf.so
echo Success
ls lib
