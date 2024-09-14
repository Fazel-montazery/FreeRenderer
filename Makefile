CC := gcc
DEPS := src/main.c include/glad/glad.c src/utils.c src/shader.c
LIBS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
TARGET := bin/main
FLAGS := -O2 -std=c23

all: $(TARGET)

$(TARGET): $(DEPS)
	$(CC) $(DEPS) $(LIBS) -o $(TARGET) $(FLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm $(TARGET) && clear
