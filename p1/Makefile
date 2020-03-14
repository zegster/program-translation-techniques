CC         = g++
CFLAGS     = -Wall -g -std=c++11

MASTER_SRC = main.cpp
SRC        = token.h scanner.h testScanner.h

MASTER_OBJ = $(MASTER_SRC:.cpp=.o)
OBJ        = $(SRC:.h=.o)

MASTER     = scanner

OUTPUT    = $(MASTER)
all: $(OUTPUT)


%.o: %.cpp $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MASTER): $(MASTER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(MASTER_OBJ) $(OBJ) -o $(MASTER)


.PHONY: clean
clean:
	/bin/rm -f $(OUTPUT) *.o *.dat
