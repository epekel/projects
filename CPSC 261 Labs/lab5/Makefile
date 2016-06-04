CFLAGS = -g -O3 -Wall

all:		time_nothing time_read time_fread time_write time_fwrite time_is_smooth

time_nothing:	time_nothing.o 
	$(CC) -o time_nothing $(CFLAGS) time_nothing.o 

time_read:	time_read.o 
	$(CC) -o time_read $(CFLAGS) time_read.o 

time_fread:	time_fread.o 
	$(CC) -o time_fread $(CFLAGS) time_fread.o 

time_write:	time_write.o 
	$(CC) -o time_write $(CFLAGS) time_write.o 

time_fwrite:	time_fwrite.o 
	$(CC) -o time_fwrite $(CFLAGS) time_fwrite.o 

time_is_smooth:	time_is_smooth.o is_smooth.o
	$(CC) -o time_is_smooth $(CFLAGS) time_is_smooth.o is_smooth.o

is_smooth.o:	is_smooth.s
	$(CC) -c $(CFLAGS) is_smooth.s

clean:
	rm -f *.o time_is_smooth time_nothing time_read time_fread time_write time_fwrite

run:	time_is_smooth
	./time_is_smooth
