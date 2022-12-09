@echo off
gcc src/*.c -I include -o bin/main -L lib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
bin\main.exe %*
del bin\main.exe
echo:
echo program exit with code %errorlevel%
@echo on
