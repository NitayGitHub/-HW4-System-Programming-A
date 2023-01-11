CFLAGS= -Wall -g
CC= gcc
all:graph libgraph.a

graph: main.o libgraph.a
	$(CC) $(CFLAGS) -o graph main.o libgraph.a

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c
libgraph.a:directed_graph.o
	ar -rcs libgraph.a directed_graph.o
directed_graph.o: directed_graph.c graph.h
	$(CC) $(CFLAGS) -c directed_graph.c
clean:
	rm -f *a *.o graph
