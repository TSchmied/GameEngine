# make.py
# Script that compiles and executes Kvejge projects.

import sys
import fnmatch
import os
from enum import Enum


class Mode(Enum):
    DEV = 1
    PROD = 2


SETTINGS_COMPILER = "g++"
SETTINGS_INCLUDE_PATHS = "-IC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\include\\SDL2"
SETTINGS_LIBRARY_PATHS = "-LC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\lib"
SETTINGS_EXECUTABLE_NAME = "kvejge_project.exe"  # TODO: MAKE CROSS PLATFORM
SETTINGS_COMPILER_FLAGS = "-std=c++17"
SETTINGS_COMPILER_DEV_FLAGS = ""
SETTINGS_COMPILER_PROD_FLAGS = "-w"
SETTINGS_LINKER_FLAGS = "-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer"


def main(argv):
    mode = Mode.DEV
    for arg in argv:
        if arg.startswith("-mode="):
            newmodestr = (arg.partition("-mode="))[2]
            if newmodestr in Mode.__members__:
                mode = Mode[newmodestr]
            else:
                print("Incorrect mode. Available modes:")
                for member in Mode.__members__:
                    print(member)
                print("...defaulting to " + mode.name)

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

    outputPath = os.getcwd() + "/builds/" + mode.name + "/"

    if not os.path.isdir(outputPath):
        os.mkdir(outputPath)

    print("\nCompiling...")
    os.system(SETTINGS_COMPILER + " " + ' '.join(cpps) + " " + SETTINGS_INCLUDE_PATHS + " " + SETTINGS_LIBRARY_PATHS +
              " " + compilerFlags + " " + SETTINGS_LINKER_FLAGS + ' -o ' + outputPath + SETTINGS_EXECUTABLE_NAME)
    print("\nRunning...")
    os.system(outputPath + SETTINGS_EXECUTABLE_NAME)


if __name__ == '__main__':
    main(sys.argv[1:])
