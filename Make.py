# make.py
# Script that compiles and executes Kvejge projects.

import sys
import fnmatch
import os
from enum import Enum


class Mode(Enum):
    DEV = 1
    PROD = 2


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

    outputPath = os.getcwd() + "/builds/" + mode.name + "/"
    execName = "kvejge_project.exe"  # TODO: MAKE CROSS PLATFORM

    if not os.path.isdir(outputPath):
        os.mkdir(outputPath)

    print("\nCompiling...")
    os.system('g++ ' + ' '.join(cpps) + ' -o ' + outputPath + execName)
    print("\nRunning...")
    os.system(outputPath + execName)


if __name__ == '__main__':
    main(sys.argv[1:])
