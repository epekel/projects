CFLAGS = -g

all:		testcollatz testmax testarraymax

testcollatz:	testcollatz.o collatz.o
testmax:	testmax.o max.o
testarraymax:	testarraymax.o arraymax.o

collatz.o:	collatz.s
max.o:		max.s
arraymax.o:	arraymax.s

clean:
	rm -f *.o testcollatz testmax testarraymax

run:	testcollatz testmax testarraymax
	./testcollatz
	./testmax
	./testarraymax

.s.o:;	gcc $(CFLAGS) -c -o $*.o $*.s
