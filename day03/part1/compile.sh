mkdir -p build && cd build
cmake .. -DCMAKE_CXX_STANDARD=17 \
-DCMAKE_CXX_STANDARD_REQUIRED=ON \
-DCMAKE_CXX_EXTENSIONS=OFF
make && cp ../input.txt . && cp ../final_input.txt . && ./aoc
