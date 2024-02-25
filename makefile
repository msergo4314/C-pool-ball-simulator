CC = clang
CFLAGS = -std=c99 -Wall -pedantic -fpic
LDFLAGS = -shared
TARGET = libphylib.so
# TARGET_2 = A1.exe
OBJ = phylib.o
# OBJ_2 = A1test1.o

all: $(TARGET) $(TARGET_2)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@
	clang A1test1.c -o A1.exe -lm

# $(TARGET_2): $(OBJ_2)
# 	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ): phylib.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.gch *.exe *.out *.o *.so

# CC = clang
# CFLAGS = -Wall -std=c99 -pedantic -fpic

# all: libphylib.so

# libphylib.so: phylib.o
	# $(CC) $(CFLAGS) phylib.o -shared -o libphylib.so

# phylib.o:  phylib.c phylib.h
	# $(CC) $(CFLAGS) -c phylib.c -o phylib.o

# clean:
	# rm -f *.o *.so *.exe *.out