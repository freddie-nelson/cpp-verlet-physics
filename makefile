output: 
	g++ main.cpp ./src/*.cpp -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

clean:
	rm main.exe