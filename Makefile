HEADERS = cypher.h decypher.h transform.h tools.h decypher.h

run: main

main: main.o cypher.o tools.o transform.o decypher.o
	gcc -g -o out main.o cypher.o tools.o transform.o decypher.o 

main.o: 
	gcc -c main.c 

tools.o: 
	gcc -c tools.c 

cypher.o: 
	gcc -c cypher.c 

transform.o: 
	gcc -c transform.c 

decypher.o: 
	gcc -c decypher.c 

clean: 
	rm *.o
