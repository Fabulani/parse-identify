cd build
cmake .. -G "Visual Studio 17 2022" 
cmake --build . --config Debug
.\Debug\ParseIdentify.exe ..\data\identify1.bin
.\Debug\ParseIdentify.exe ..\data\identify2.bin
.\Debug\ParseIdentify.exe ..\data\identify3.bin
cd ..