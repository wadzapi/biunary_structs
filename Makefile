all: main
	g++ -o run main.o

main: sequence main.cpp
	g++ -c -o main.o

sequence: sequence.hh
	g++ -c -o sequence.gch sequence.hh

debug: maind 
	g++ -o run maind.o

maind: sequenced main.cpp
	g++ -g -c -o maind.o main.cpp

sequenced: sequence.hh
	g++ -g -c -o sequenced.gch sequence.hh

clean:
	rm ./*.gch
	rm ./*.o
