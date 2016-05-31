bjh2B:bjh2B.o
	g++ -o bjh2B bjh2B.o
bjh2B.o:bjh2B.cpp
	g++ -c bjh2B.cpp
clean:
	/bin/rm -f bjh2B bjh2B.o
