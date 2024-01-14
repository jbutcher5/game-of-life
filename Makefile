CC      = clang
INCLUDE = src
OBJ     = build
SRC     = src
SRCS    += $(shell find $(SRC) -type f -name '*.c')
OBJS    = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     = game-of-life
TESTEXE = blackbox
CFLAGS  = -I$(INCLUDE) -std=c99 -Wall -Wextra -Werror -pedantic -mpopcnt
LDLIBS  = -lm -lraylib

.PHONY: clean

# Compile all .c files within src/ to obj files 
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p "$(@D)"
	@echo "Compiling: $< -> $@"
	$(CC) -c -g $(CFLAGS) $< -o $@

# Compile all .c files at the top level of the directory to obj files 
$(OBJ)/%.o: %.c
	@mkdir -p "$(@D)"
	@echo "Compiling: $< -> $@"
	$(CC) -c -g $(CFLAGS) $< -o $@

# In the case of building the executable link main.o with the other obj files
$(EXE): $(OBJS) $(OBJ)/main.o
	@echo "Building final executable: $@"
	$(CC) $^ -g $(LDLIBS) -o $@

$(OBJ):
	mkdir -p $@

# In the case of building the blackbox link test.o with the other obj files
$(TESTEXE): $(OBJS) $(OBJ)/test.o
	$(CC) $^ -g $(LDLIBS) -lrt -o $(TESTEXE) 

format: $(SRC)
	clang-format $^ -i

clean:
	rm -rf $(OBJ) $(EXE) $(TESTEXE)
