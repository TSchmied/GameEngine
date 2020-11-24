OBJS = engine_test.cpp

CC = g++

INCLUDE_PATHS = -IC:\mingw-w64\dev_libs\SDL2-2.0.12\include\SDL2

LIBRARY_PATHS = -LC:\mingw-w64\dev_libs\SDL2-2.0.12\lib

# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OBJ_NAME = Builds\GameEngine

all : build run
.PHONY: all

build : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run :
	Builds\GameEngine.exe