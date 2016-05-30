
## How to install MoonGLFW

### On Ubuntu

Install Lua as described in the installation instructions for 
[MoonFLTK](https://github.com/stetre/moonfltk/).

Download MoonGLFW's [latest release](https://github.com/stetre/moonsoil/releases)
(e.g. moonsoil-0.1.tar.gz).

```sh
$ tar -zxpvf moonsoil-0.1.tar.gz
$ cd moonsoil-0.1
moonsoil-0.1$ make
moonsoil-0.1$ sudo make install
```

### On Windows with MSYS2/MinGW

Set up the MSYS2/MinGW environment and install Lua as described in the installation 
instructions for [MoonFLTK](https://github.com/stetre/moonfltk/).

Download MoonGLFW's [latest release](https://github.com/stetre/moonsoil/releases)
(e.g. moonsoil-0.1.tar.gz).

```sh
$ tar -zxpvf moonsoil-0.1.tar.gz
$ cd moonsoil-0.1
moonsoil-0.1$ make platform=mingw
moonsoil-0.1$ make install platform=mingw
```

