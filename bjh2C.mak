bjh2C:bjh2C.o
	g++ -o bjh2C bjh2C.o
bjh2C.o:bjh2C.cpp
	g++ -c bjh2C.cpp
clean:
	/bin/rm -f bjh2C bjh2C.o
