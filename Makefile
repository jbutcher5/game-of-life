CC      = clang
INCLUDE = src
OBJ     = build
SRC     = src
SRCS    += $(shell find $(SRC) -type f -name '*.c')
OBJS    = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     = game-of-life 
CFLAGS  = -I$(INCLUDE) -std=c99 -Wall -Wextra -Werror -pedantic
LDLIBS  = -lm -lraylib

.PHONY: clean

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p "$(@D)"
	@echo "Compiling: $< -> $@"
	$(CC) -c -g $(CFLAGS) $< -o $@

$(OBJ)/%.o: %.c
	@echo "Compiling: $< -> $@"
	$(CC) -c -g $(CFLAGS) $< -o $@

$(EXE): $(OBJS) $(OBJ)/main.o
	@echo "Building final executable: $@"
	$(CC) $^ -g $(LDLIBS) -o $@

$(OBJ):
	mkdir -p $@

blackbox: $(OBJS) $(OBJ)/test.o
	$(CC) $^ -g $(LDLIBS) -lrt -o blackbox

format: $(SRC)
	clang-format $^ -i

clean:
	@echo "$(SRCS) | $(OBJS)"
	rm -rf $(OBJ) $(EXE)
