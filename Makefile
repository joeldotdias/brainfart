COMPILER = clang
CFLAGS = -Wall -Wextra -g
SOURCES = $(shell find ./ -name "*.c")
TARGET = brainfart

$(TARGET): $(SOURCES)
	@$(COMPILER) $(CFLAGS) $(SOURCES) -o $(TARGET)


anz:
	@clang $(CFLAGS) --analyze -Xclang -analyzer-output=text $(SOURCES)

clean:
	@rm -f $(TARGET)
