INCLUDE = ./include/
SRC = ./src/
OBJ = ./obj/
BIN = ./bin/
TEST = ./test/

LIBPATH= ./lib/
LIBNAME = threadpool
LIB = $(LIBPATH)lib${LIBNAME}.a

FLAG = -Wall -I$(INCLUDE) -Wextra

.PHONY : all clean test

all : $(LIB)


$(LIB) : $(OBJ)queue.o $(OBJ)alloc.o $(OBJ)threadpool.o
	ar rcs $@ $^

$(OBJ)queue.o : $(SRC)queue.c $(INCLUDE)queue.h
	gcc $(FLAG) -c $< -o $@

$(OBJ)alloc.o : $(SRC)alloc.c $(INCLUDE)alloc.h
	gcc $(FLAG) -c $< -o $@

$(OBJ)threadpool.o: $(SRC)threadpool.c $(INCLUDE)threadpool.h
	gcc $(FLAG) -c $< -o $@

$(BIN)sum_divisor.exe : $(TEST)sum_divisor.c  $(LIB)
	gcc $(FLAG) $<  -L$(LIBPATH) -l$(LIBNAME) -lm -o $@

test : $(BIN)sum_divisor.exe
	bin/sum_divisor.exe

clean :
	rm -f $(OBJ)*.o
	rm -f $(BIN)*.exe
	rm -f $(LIB)
	