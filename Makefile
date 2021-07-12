
graph: output.o eps_graph.o
	gcc output.o eps_graph.o -lm -o graph

output.o: output.c
	gcc -c output.c

eps_graph.o: eps_graph.c eps_graph.h
	gcc -c eps_graph.c

clean:
	rm *.o graph