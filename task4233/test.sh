#!/bin/sh

g++ -std=c++11 getLargestArea.cpp -o ./a
./a < in > out
diff out ans > state
if [ ! -s state ]; then
    echo "ok!"
else
    echo "wrong..."
    cat state
fi
rm state a
