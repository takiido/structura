cd ..

cmake -S . -B build -G Ninja
cmake --build build

./build/editor/editor