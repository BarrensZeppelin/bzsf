#! /usr/bin/env -S bash -euo pipefail

FILES=$(find src -name "*.cpp")
mkdir -p build

for f in $FILES; do
	g++ -c -g -O2 -I. $f -o "build/$(basename ${f%.cpp}.o)"
done

ar rcs lib/libbzsf.a build/*.o

# We can also compile a shared library?
# g++ -g -O2 -fPIC $FILES -I. -shared -o lib/libbzsf.so

echo Success
ls lib
