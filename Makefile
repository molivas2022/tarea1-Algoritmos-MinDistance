FLAGS = -Wall
GCC = g++

ALGORITHMS_HEADER = inc/algorithms.h inc/point.h inc/test.h

main: main.cpp bruteforce.o divideandconquer.o test.o
	$(GCC) $(FLAGS) -o min_dist.exe main.cpp bruteforce.o divideandconquer.o test.o

bruteforce.o: src/bruteforce.cpp $(ALGORITHMS_HEADER)
	$(GCC) $(FLAGS) -c src/bruteforce.cpp

divideandconquer.o: src/divideandconquer.cpp $(ALGORITHMS_HEADER)
	$(GCC) $(FLAGS) -c src/divideandconquer.cpp

test.o: src/test.cpp $(ALGORITHMS_HEADER)
	$(GCC) $(FLAGS) -c src/test.cpp	

.PHONY: clean
clean:
	rm -r *.exe *.o	