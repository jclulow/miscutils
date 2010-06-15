
all: evalue dvalue

ns_crypt.o: ns_crypt.c
	gcc -c -o ns_crypt.o ns_crypt.c

evalue: evalue.c ns_crypt.o
	gcc -lcrypt -o evalue ns_crypt.o evalue.c

dvalue: dvalue.c ns_crypt.o
	gcc -lcrypt -o dvalue ns_crypt.o dvalue.c

clean:
	rm -f dvalue.o evalue.o ns_crypt.o evalue dvalue

