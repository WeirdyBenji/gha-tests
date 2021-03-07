if exist "build/" (
rmdir build /S /Q
)
mkdir build
cd build
conan install .. --build=missing
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release