# ps-vita-sdl-hello-world
This project has been tested on real hardware (firmware 3.60).

## How to Build
Install [VITASDK](https://github.com/vitasdk/vdpm) (more information [here](https://vitasdk.org/)).  
To build:
```
cmake .
make
```

## How to get includes in VSCode
Set the following lines in the include path:
```
${workspaceFolder}/**
${VITASDK}/include
${VITASDK}/arm-vita-eabi/include
```

## VitaSdk Documentation
https://docs.vitasdk.org/

## SDL2
https://wiki.libsdl.org/SDL2/README/vita  
https://github.com/libsdl-org/SDL/tree/SDL2

## Safe Time with Vita3k
Instead of always pushing and installing the .vpk to your Vita you can directly run it inside the Vita3k emulator. You can install it from [here](https://github.com/Vita3K/Vita3K) and run the command `make run`. This assumes you have the Vita3k AppImage installed or linked into the workspace and named `Vita3K-x86_64.AppImage`. You can adjust this behavior inside the `CMakeLists.txt`.