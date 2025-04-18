FLAGS = "-Wall"
GCC = "g++"

main: main.cpp bruteforce.o
	${GCC} ${FLAGS} -o min_dist.exe main.cpp bruteforce.o

bruteforce.o: src/bruteforce.cpp inc/algorithms.h inc/point.h
	${GCC} ${FLAGS} -c src/bruteforce.cpp

.PHONY: clean
clean:
	del /s *.o *.exe 