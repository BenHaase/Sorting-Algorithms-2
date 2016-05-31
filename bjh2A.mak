bjh2A:bjh2A.o
	g++ -o bjh2A bjh2A.o
bjh2A.o:bjh2A.cpp
	g++ -c bjh2A.cpp
clean:
	/bin/rm -f bjh2A bjh2A.o

