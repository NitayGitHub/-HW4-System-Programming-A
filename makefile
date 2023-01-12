CFLAGS= -Wall -g
CC= gcc
all:graph libgraph.a

graph: main.o libgraph.a
	$(CC) $(CFLAGS) -o graph main.o libgraph.a

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

libgraph.a:directed_graph.o aid_methods.o
	ar -rcs libgraph.a directed_graph.o aid_methods.o

directed_graph.o: directed_graph.c graph.h
	$(CC) $(CFLAGS) -c directed_graph.c

aid_methods.o: aid_methods.c graph.h
	$(CC) $(CFLAGS) -c aid_methods.c

rung: graph
	./graph

clean:
	rm -f *a *.o graph
