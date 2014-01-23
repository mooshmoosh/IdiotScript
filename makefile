bin/main.o: src/main.cpp 
	g++ -c src/main.cpp -o bin/main.o

bin/test.o: src/test.cpp 
	g++ -c src/test.cpp -o bin/test.o

bin/texteater.o: src/texteater.cpp 
	g++ -c src/texteater.cpp -o bin/texteater.o

bin/instructionlist.o: src/instructionlist.cpp 
	g++ -c src/instructionlist.cpp -o bin/instructionlist.o

idiotscript: bin/main.o bin/texteater.o bin/instructionlist.o 
	g++ bin/main.o bin/texteater.o bin/instructionlist.o -o bin/idiotscript

check: bin/test.o bin/texteater.o bin/instructionlist.o 
	g++ bin/test.o bin/texteater.o bin/instructionlist.o -o bin/test
	bin/test

check_memory: src/test.cpp src/texteater.cpp src/instructionlist.cpp 
	g++ src/test.cpp src/texteater.cpp src/instructionlist.cpp -g -o bin/test_VAL
	valgrind --leak-check=yes --tool=memcheck --track-origins=yes ./bin/test_VAL

