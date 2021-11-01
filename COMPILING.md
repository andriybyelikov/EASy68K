# Compiling

Guides for tested build environments.

## Arch Linux

Arch ships with version 3.0.5, so the decision is to link statically.

### GCC

- Compile and install wxWidgets 3.1.5 with `--disable-shared` and `--with-gtk=3`
- cd into wxEdit68K
- mkdir build
- cd build
- cmake ..
- make -j{number of threads to use, empty to use all}
- ./wxEdit68K should run

### Mingw-w64

Todo write guide, but have already successfully cross compiled on Arch with Mingw-w64.

---

## Windows

### Visual Studio

- Download and extract source to C:\wxWidgets-3.1-5
- Go to  C:\wxWidgets-3.1-5\build\msw
- Open solution, latest is vc16
- Batch build necessary configurations
- cd into wxEdit68K
- mkdir build
- cd build
- cmake ..
- Open generated solution
- Set wxEdit68K as initial project
- Click the play icon and it should run

## TODO

- Possible vcpkg build guide, however available build crashes on richtext