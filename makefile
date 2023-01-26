CC=gcc
CFLAGS=-g -Wall -Wextra
SRC=src
OBJ=obj
TEST=tests
HDRDIR=include
LIBDIR=lib
BINDIR=bin

BIN=$(BINDIR)/main.exe

LIBFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%.exe,$(TESTS))
TESTOBJS=$(filter-out $(OBJ)/main.o,$(OBJS))

all : $(BIN)

release : CFLAGS=-Wall -O2 -DNDEBUG
# release : clean
release : $(BIN)

automated : CFLAGS=-Wall -O2 -DNDEBUG -DAUTOMATED_RUNS
automated : $(BIN)

run : $(BIN)
	./$(BIN)

test: $(TESTBINS)

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBDIR) $(LIBFLAGS) -o $(BIN)

$(OBJ)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -I $(HDRDIR) -c $< -o $@

$(TEST)/bin/%.exe : $(TEST)/%.c $(TESTOBJS)
	$(CC) $(CFLAGS) -I $(HDRDIR) $< $(TESTOBJS) -L $(LIBDIR) $(LIBFLAGS) -o $@
	./$@


clean : 
	del /q $(BINDIR)\*.exe $(OBJ)\*.o

clean_test:
	del /q $(TEST)\bin\*.exe