OBJ = main.o bubble.o insert.o select.o quick.o merge.o radix.o heap.o
CFLAGS = -std=c99

%.o: %.c sort.h
	gcc -c -o $@ $< $(CFLAGS)
sort: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
