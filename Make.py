# make.py
# Script that compiles and executes Kvejge projects.

import sys
import fnmatch
import os
from enum import Enum


class Mode(Enum):
    DEV = 1
    PROD = 2
    
class Target(Enum):
    WIN = 1
    WASM = 2


SETTINGS_COMPILER = "g++"
SETTINGS_WASM_COMPILER = "emcc"
SETTINGS_INCLUDE_PATHS = "-IC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\include\\SDL2"
SETTINGS_LIBRARY_PATHS = "-LC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\lib"
SETTINGS_EXECUTABLE_NAME = "kvejge_project"
SETTINGS_COMPILER_FLAGS = "-std=c++17"
SETTINGS_COMPILER_DEV_FLAGS = "-Wall -Wextra"
SETTINGS_COMPILER_PROD_FLAGS = "-w -Wl,-subsystem,windows"
SETTINGS_LINKER_FLAGS = "-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer"


def main(argv):
    mode = Mode.DEV
    target = Target.WIN
    for arg in argv:
        if arg.startswith("-mode="):
            newmodestr = (arg.partition("-mode="))[2]
            if newmodestr in Mode.__members__:
                mode = Mode[newmodestr]
            else:
                print("Invalid mode. Available modes:")
                for member in Mode.__members__:
                    print(member)
                print("...defaulting to " + mode.name)
        elif arg.startswith("-target="):
            newtargetstr = (arg.partition("-target="))[2]
            if newtargetstr in Target.__members__:
                target = Target[newtargetstr]
            else:
                print("Invalid target. Available targets:")
                for member in Target.__members__:
                    print(member)
                print("...defaulting to " + target.name)

    cppsIgnored = []
    for line in open("src/.kvejgeignore"):
        cppsIgnored.append(line)

    cpps = []
    for file in os.listdir("src/"):
        if fnmatch.fnmatch(file, "*.cpp"):
            if file not in cppsIgnored:
                cpps.append("src/" + file)

    compilerFlags = SETTINGS_COMPILER_FLAGS
    if mode == Mode.DEV:
        compilerFlags += " " + SETTINGS_COMPILER_DEV_FLAGS
    elif mode == Mode.PROD:
        compilerFlags += " " + SETTINGS_COMPILER_PROD_FLAGS

    outputPath = os.getcwd() + "/builds/" + target.name + "/" + mode.name + "/"

    if not os.path.isdir(outputPath):
        os.makedirs(outputPath)

    print("\nCompiling...")
    if target == Target.WIN:
        os.system(SETTINGS_COMPILER + " " + ' '.join(cpps) + " " + SETTINGS_INCLUDE_PATHS + " " + SETTINGS_LIBRARY_PATHS + " " + compilerFlags + " " + SETTINGS_LINKER_FLAGS + ' -o ' + outputPath + SETTINGS_EXECUTABLE_NAME)
        print("\nRunning...")
        os.system(outputPath + SETTINGS_EXECUTABLE_NAME + ".exe")
    elif target == Target.WASM:
        os.system(SETTINGS_WASM_COMPILER + " " + ' '.join(cpps) + " -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2 " + compilerFlags + " -c -o " + outputPath + SETTINGS_EXECUTABLE_NAME + ".o")
        print("\nGenerating HTML...")
        os.system(SETTINGS_WASM_COMPILER + " " + outputPath + SETTINGS_EXECUTABLE_NAME + ".o -o " + outputPath + SETTINGS_EXECUTABLE_NAME + ".html -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2")
        print("\nIf your browser doesn't supprt cold-loading .wasm files, host the generated HTML file on a local server.")

if __name__ == '__main__':
    main(sys.argv[1:])
