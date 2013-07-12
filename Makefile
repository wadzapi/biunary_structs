all: main heap
	g++ -o run main.o heap.o

main: main.cpp
	g++ -c -o main.o main.cpp

heap: heap_obj.hh
	g++ -c -o heap.o heap_obj.hh

debug: maind heapd
	g++ -g -o rund maind.o heapd.o

maind: main.cpp
	g++ -g -c -o maind.o main.cpp

heapd: heap_obj.hh
	g++ -g -c -o heapd.o heap_obj.hh

clean:
	rm ./*.o
