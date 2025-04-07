# AUTOMATICALLY GENERATED FILE. MODIFY WITH CAUTION.
CONFER_PATH ?= $~/.local/share/confer
CC = gcc
.PHONY : clean

OBJ_FILES = obj/assertions.o obj/build.o obj/children.o obj/print.o
TARGETS =  $(OBJ_FILES)

CC_OPTIONS = -pedantic
CC_INCLUDE = -I./include
WARN = -Wall -Wextra
CFLAGS = $(CC_INCLUDE) $(CC_OPTIONS) $(WARN)
obj/confer.o: $(OBJ_FILES)
	@echo "📦 $(OBJ_FILES) -> $@"
	@ld -r $(OBJ_FILES) -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	@echo "🔨 $< -> $@"
	@$(CC) -I./include -c $< -o $@ $(CFLAGS)

./bin/test: test/test.c $(OBJ_FILES)
	@mkdir -p bin
	@$(CC) "test/test.c" $(OBJ_FILES) $(CFLAGS) -I./test -I$(CONFER_PATH)/include -o "./bin/test"

clean:
	rm ${TARGETS}
