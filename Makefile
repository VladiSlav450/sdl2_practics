# Определяем переменные
OBJECTS = SDL_game_main.cpp game.cpp erproc.cpp global.cpp

CC = g++

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJECTS_NAME = gangbang

# Цель по умолчанию
all: $(OBJECTS)
	$(CC) $(OBJECTS) -w $(LINKER_FLAGS) -o $(OBJECTS_NAME)
# Очистка сгенерированных файлов
clean:
	rm -f $(OBJECTS_NAME)
