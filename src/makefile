OBJS = driver.o bubble_sort.o

all: driver

driver: $(OBJS)
	g++ -g -o driver $(OBJS)

bubble_sort.o: bubble_sort.s
	as -g bubble_sort.s -o bubble_sort.o

driver.o: driver.cpp
	g++ -g -c driver.cpp


numgen: numgen.cpp
	g++ -g numgen.cpp -Wall -Werror -Wextra -o generate-numbers


.PHONY: clean

clean:
	rm *.o driver *_bubblesort.txt
