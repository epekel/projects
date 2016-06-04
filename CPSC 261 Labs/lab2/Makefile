CC = gcc
CFLAGS = -O2 -g

linked-list-test: linked-list.o main.o
	$(CC) $(CFLAGS) -o $@ linked-list.o main.o

linked-list-instructor: linked-list.o main-instructor.o
	$(CC) $(CFLAGS) -o $@ linked-list.o main-instructor.o
clean:
	/bin/rm *.o linked-list-test linked-list-instructor

linked-list.o: linked-list.h linked-list.c
main.o: linked-list.h main.c
main-instructor.o: linked-list.h main-instructor.c
