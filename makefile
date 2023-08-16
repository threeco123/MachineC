CC = g++
FILES = main.cpp pda.cpp state.cpp transition.cpp
EXE = NPDA

build: $(FILES)
	$(CC) -o $(EXE) $(FILES)

clean:
	rm -f *.o core

rebuild: clean build


