clang -o .\bin\main.exe -I inc -I .\SDL2-2.0.20\include -L .\SDL2-2.0.20\lib\x64 .\src\*.c -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32