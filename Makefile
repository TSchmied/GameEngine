OBJS = src\TestApp.cpp

CC = g++

INCLUDE_PATHS = -IC:\mingw-w64\dev_libs\SDL2-2.0.12\include\SDL2 -IC:\mingw-w64\dev_libs\SDL2_image-2.0.5\include\SDL2 -IC:\mingw-w64\dev_libs\SDL2_mixer-2.0.4\include\SDL2 

LIBRARY_PATHS = -LC:\mingw-w64\dev_libs\SDL2-2.0.12\lib -LC:\mingw-w64\dev_libs\SDL2_image-2.0.5\lib -LC:\mingw-w64\dev_libs\SDL2_mixer-2.0.4\lib

# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -std=c++17 -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

OBJ_NAME = builds\win64\GameEngine

all : build run
.PHONY: all

build : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.ONESHELL:
run :
	cd builds/win64
	start GameEngine.exe