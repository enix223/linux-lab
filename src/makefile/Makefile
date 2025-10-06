SRC = $(wildcard src/*.c)
INC = ./inc
OBJ = $(patsubst src/%.c, out/%.o, $(SRC))
TARGET = out/main

out/%.o: src/%.c
	gcc -c $< -I $(INC) -o $@

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@

clean:
	-rm -rf $(OBJ) $(TARGET)

.PHONY: clean TARGET
