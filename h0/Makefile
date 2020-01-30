CC         = gcc
CFLAGS     = -Wall -g

HELPER     = helper.h
SRC        = f1.h f23.h
MASTER_SRC = main.c

OBJ        = $(SRC:.h=.o)
MASTER_OBJ = $(MASTER_SRC:.c=.o)

MASTER     = main

OUTPUT    = $(MASTER)
all: $(OUTPUT)


%.o: %.c $(SRC)	$(HELPER)
	$(CC) $(CFLAGS) -c $< -o $@

$(MASTER): $(MASTER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(MASTER_OBJ) $(OBJ) -o $(MASTER)


.PHONY: clean
clean:
	/bin/rm -f $(OUTPUT) *.o *.dat
