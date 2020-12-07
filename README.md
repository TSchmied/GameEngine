<img src="branding/logo_color.png" alt="kvejge logo" style="zoom:50%;" />

# **REWRITE IN PROGRESS**

## Done
 - OOP structure design
 - Logger util
 - Compilation using SDL2
 - WebAssembly support
 - Event handling [IN PROGRESS]

## To do
 - OOP structure design implementation
 - Timer util
 - Textures
 - Renderer class
 - Texturepacks
 - Animated textures
 - Audio nodes


# Building

1. Install SDL 2 dev libraries for your platform from [here](https://www.libsdl.org/download-2.0.php)

2. Run `python make.py` to build and run the project

## Switching build configuration

Build configurations can be edited in ./kvejgeide/projectsettings.json  
To switch to a different build configuration when building, use the `-config` flag.  
`python make.py -config=wasm_dev

# Building for the web (WebAssembly)

If your browser of choice does not support cold-loading WASM files, host the generated HTML file on a local server.


# Features
 - Texturepacks - render specific cell simply by specifying its ID
 - Animated textures - compatible with texturepacks
