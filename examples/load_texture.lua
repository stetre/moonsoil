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

