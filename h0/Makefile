CC         = gcc
CFLAGS     = -Wall -g

SRC        = functionOne.h functionTwo.h functionThree.h
MASTER_SRC = main.c

OBJ        = $(SRC:.h=.o)
MASTER_OBJ = $(MASTER_SRC:.c=.o)

MASTER     = main

OUTPUT    = $(MASTER)
all: $(OUTPUT)


%.o: %.c $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MASTER): $(MASTER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(MASTER_OBJ) $(OBJ) -o $(MASTER)


.PHONY: clean
clean:
	/bin/rm -f $(OUTPUT) *.o *.dat
