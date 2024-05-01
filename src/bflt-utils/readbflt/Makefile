#CC=gcc
#CFLAGS=-Wall
TARGET=readbflt

$(TARGET): readbflt.o
	$(CC) $(CFLAGS) $(LDFLAGS) *.o main.c -o $(TARGET)

$(TARGET).o:
	$(CC) $(CFLAGS) $(LDFLAGS) $(TARGET).c -c

clean:
	rm -f $(TARGET) *.o
