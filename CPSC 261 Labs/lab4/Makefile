CFLAGS = -g
CC=gcc -m64

all:	test_endianness test_reverse decode test_read_tree

test_read_tree:	test_read_tree.o read_tree.o which_endianness.o read_data.o reverse_long.o print_tree.o 
	$(CC) -o test_read_tree $(CFLAGS) test_read_tree.o read_tree.o which_endianness.o read_data.o reverse_long.o print_tree.o 

test_endianness: test_endianness.o which_endianness.o
	$(CC) -o test_endianness $(CFLAGS) test_endianness.o which_endianness.o

test_reverse: test_reverse.o reverse_long.o
	$(CC) -o test_reverse $(CFLAGS) test_reverse.o reverse_long.o

decode:	decode.o read_data.o which_endianness.o reverse_long.o
	$(CC) -o decode $(CFLAGS) decode.o read_data.o which_endianness.o reverse_long.o

clean:
	rm -f *.o test_endianness test_reverse decode test_read_tree

run:	test_endianness test_reverse decode test_read_tree
	./test_endianness
	./test_reverse
	./decode little.dat
	./decode big.dat
	./test_read_tree littleendian11.tree
	./test_read_tree littleendian23.tree
	./test_read_tree bigendian13.tree
	./test_read_tree bigendian19.tree
