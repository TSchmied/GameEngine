# make.py
# Script that compiles and executes Kvejge projects.

import sys
import fnmatch
import os
import json


def main(argv):
    buildConfig = ""
    compileArgs = ""
    executableName = ""
    executableExtension = ""
    afterCommand = ""
    cpps = []
    compiler = ""

    for arg in argv:
        if arg.startswith("-config="):
            buildConfig = (arg.partition("-config="))[2]

    with open(os.getcwd() + "/.kvejgeide/projectsettings.json") as projectSettings:
        projectSettingsData = json.load(projectSettings)
        executableName = projectSettingsData["executableName"]
        for bc in projectSettingsData["buildConfigs"]:
            if buildConfig == "":
                buildConfig = bc["name"]
            if bc["name"] == buildConfig:
                compileArgs = bc["compileArgs"]
                executableExtension = bc["executableExtension"]
                cpps = []
                for cpp in bc["cpps"]:
                    cpps.append("src/" + cpp)
                if "afterCommand" in bc:
                    afterCommand = bc["afterCommand"]

    with open(os.getcwd() + "/.kvejgeide/settings.json") as settings:
        settingsData = json.load(settings)
        for bcCompiler in settingsData["buildConfigCompiler"]:
            if bcCompiler["config"] == buildConfig:
                compiler = bcCompiler["compiler"]

    outputPath = os.getcwd() + "/builds/" + buildConfig + "/"

    if not os.path.isdir(outputPath):
        os.makedirs(outputPath)

    print("\nCompiling...")

    includePaths = "-IC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\include\\SDL2 -IC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\include\\SDL2"
    libraryPaths = "-LC:\\mingw-w64\\dev_libs\\SDL2-2.0.12\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_image-2.0.5\\lib -LC:\\mingw-w64\\dev_libs\\SDL2_mixer-2.0.4\\lib"
    os.system("{compiler} {cpps} {includePaths} {libraryPaths} -std=c++17 {compileArgs} -o {outputPath}{executableName}{executableExtension}"
              .format(compiler=compiler, cpps=" ".join(cpps), includePaths=includePaths, libraryPaths=libraryPaths, compileArgs=compileArgs, outputPath=outputPath, executableName=executableName, executableExtension=executableExtension))
    if afterCommand != "":
        print("\nRunning afterCommand...")
        os.system(afterCommand.format(compiler=compiler, executableName=executableName, executableExtension=executableExtension, cwd=outputPath, compileArgs=compileArgs)) 
    print("\nRunning...")

    os.system(outputPath + executableName + executableExtension)


if __name__ == '__main__':
    main(sys.argv[1:])
