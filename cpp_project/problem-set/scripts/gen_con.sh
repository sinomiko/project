#!/bin/bash
cmake -Bdebug  -DENABLE_COV=YES 

if [ $? -ne 0 ]; then
    echo "generate  cmake file failed"
    exit 1
fi
cmake --build debug -v -j32
if [ $? -ne 0 ]; then
    echo "make failed"
    exit 1
fi
ctest --test-dir debug -V
if [ $? -ne 0 ]; then
    echo "case failed"
    exit 1
fi
# lcov -c -o test.info -d .
lcov  -c -o test.info -d debug  --exclude "*/include/*" --exclude "*/tests/*" --exclude "*/proto/*" --exclude "*/common/*" --exclude "*/util/*" 
if [ $? -ne 0 ]; then
    echo "lcov failed"
    exit 1
fi
genhtml test.info -o output/
if [ $? -ne 0 ]; then
    echo "genhtml failed"
    exit 1
fi
exit 0

