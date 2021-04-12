calc: main.o atoi.o dynamic_array.o
	g++ main.o atoi.o dynamic_array.o -o calc

main: main.c
	g++ -c main.c

atoi: dynamic_array.c
	g++ -c dynamic_array

clean:
	rm main.o atoi.o dynamic_array.o

