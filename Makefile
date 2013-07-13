all: main heap
	g++ -o run main.o heap.o

main: main.cpp
	g++ -c -o main.o main.cpp

heap: memory_heap.cpp
	g++ -c -o heap.o memory_heap.cpp

debug: maind heapd
	g++ -o rund maind.o heapd.o

maind: main.cpp
	g++ -g -c -o maind.o main.cpp

heapd: memory_heap.cpp
	g++ -g -c -o heapd.o memory_heap.cpp

clean:
	rm ./*.o
