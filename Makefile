COMPILER = clang
CFLAGS = -Wall -Wextra -g
# SOURCES = main.c parser.c visualizer.c compiler.c shared.c
SOURCES = $(shell find ./ -name "*.c")
TARGET = brainfart

$(TARGET): $(SOURCES)
	@$(COMPILER) $(CFLAGS) $(SOURCES) -o $(TARGET)


anz:
	@clang $(CFLAGS) --analyze -Xclang -analyzer-output=text $(SOURCES)

clean:
	@rm -f $(TARGET)
