##MoonSOIL: Lua bindings for SOIL

MoonSOIL is a Lua binding library for
the 
[Simple OpenGL Image Library (SOIL)](http://www.lonesock.net/soil.html).

It runs on GNU/Linux and on Windows (MSYS2/MinGW) and requires 
[Lua](http://www.lua.org/) (>=5.3).

SOIL itself is not required because MoonSOIL includes its sources.

_Authored by:_ _[Stefano Trettel](https://www.linkedin.com/in/stetre)_

[![Lua logo](./doc/powered-by-lua.gif)](http://www.lua.org/)

#### License

MIT/X11 license (same as Lua). See [LICENSE](./LICENSE).

#### Documentation, Getting and installing, etc.

See the [Reference Manual](https://stetre.github.io/moonsoil/doc/index.html).

#### Getting and installing

See [INSTALL](./INSTALL.md).

#### Examples

The script below loads an image from file.

```lua
-- MoonSOIL example: load_image.lua

soil = require("moonsoil")

-- Load and image from a file. The image is returned as a binary string.
data, w, h, channels = soil.load_image("dice6.png", 'rgb')
-- Check if an error occurred:
assert(data, soil.last_result())

print(string.format("Loaded %dx%d %s image (%d bytes)", w, h, channels, #data))
```

The script can be executed at the shell prompt with the standard Lua interpreter:

```shell
$ lua load_image.lua
```

The script below loads an image from file directly into an OpenGL texture.

Since SOIL uses OpenGL functions for this purpose, the script also uses 
[MoonGLFW](https://github.com/stetre/moonglfw) and
[MoonGL](https://github.com/stetre/moongl) to create a GL context and
properly initialize it.

```lua
-- MoonSOIL example: load_texture.lua

gl = require("moongl")
glfw = require("moonglfw")
soil = require("moonsoil")

-- SOIL functions create OpenGL textures using OpenGL functions, so
-- prior to use them we need to ensure that OpenGL is initialized.
-- For this purpose, we use MoonGLFW to create a window and make its
-- GL context current. Then we call MoonGL's gl.Init() - which is
-- essentially glewInit() - to initialize OpenGL.
window = glfw.create_window(100, 100)
glfw.make_context_current(window)
gl.init() -- i.e. glewInit()

-- Now OpenGL's function pointers should be properly initialized, and
-- SOIL can use them without causing segmentation faults.

-- Load an image file directly as a new OpenGL texture:
texid, errmsg = soil.load_texture("dice6.png", 'auto', nil, 
   'mipmaps', 'invert y', 'ntsc safe rgb', 'compress to dxt');
assert(texid, errmsg)
print(string.format("Loaded texture %d (should be 1)", texid))
```

Other examples can be found in the **examples/** directory.

#### See also

* Windowing and GUI:
[MoonFLTK](https://github.com/stetre/moonfltk),
[MoonGLFW](https://github.com/stetre/moonglfw),
[MoonGLUT](https://github.com/stetre/moonglut).

* Rendering:
[MoonGL](https://github.com/stetre/moongl).

* Math:
[MoonGLMATH](https://github.com/stetre/moonglmath).

* Image and model loading:
[MoonAssimp](https://github.com/stetre/moonassimp).

* Audio:
[LuaJACK](https://github.com/stetre/luajack).

