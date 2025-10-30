cd ..
rm -rf build
rm -f compile_commands.json
cmake -S . -B build -G Ninja
cmake --build build
ln -sf build/compile_commands.json .