CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp) $(wildcard src/*/*/*/*/*.cpp)

output: 
	g++ main.cpp $(CPP_FILES) -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

clean:
	rm main.exe