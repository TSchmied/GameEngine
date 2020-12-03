<img src="branding/logo_color.png" alt="kvejge logo" style="zoom:50%;" />

# **REWRITE IN PROGRESS**

## Done
 - OOP structure design
 - Logger util [IN PROGRESS]
 - Compilation using SDL2
 - WebAssembly support

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

2. Run `python make.py` to build and run the project (to switch to production, use the flag "-mode=PROD")

# Building for the web (WebAssembly)

1. Install Emscripten for your platform from [here](https://emscripten.org/docs/getting_started/downloads.html)

2. Run `python make.py -target=WASM` to build the project (to switch to production, use the flag "-mode=PROD")

3. If your browser of choice does not support cold-loading WASM files, host the generated HTML file on a local server.


# Features
 - Texturepacks - render specific cell simply by specifying its ID
 - Animated textures - compatible with texturepacks
