# cutemino
A block stacking game base on Qt
## Develop
```bash
git clone --recursive https://github.com/26F-Studio/cutemino.git
cd cutemino
mkdir ./cmake-build-debug
cmake -S ./ -B ./cmake-build-debug -G Ninja \
-DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_PREFIX_PATH=C:/Qt/6.4.1/msvc2019_64/lib/cmake
# Use your installed Qt version
cmake --build ./cmake-build-debug --target cutemino -j 4
```