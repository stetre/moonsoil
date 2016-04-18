-- MoonSOIL example: cubemap.lua

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

-- Load 6 images into a new OpenGL cube map, forcing RGB 
texid, errmsg = soil.load_cubemap(
	"dice1.png", "dice2.png",	"dice3.png", "dice4.png", "dice5.png",	"dice6.png",
	'rgb', nil, 'mipmaps')
assert(texid, errmsg)
print(string.format("Loaded texture %d (should be 1)", texid))
	
-- Load and split a single image into a new OpenGL cube map, default format
-- face order = East South West North Up Down => "ESWNUD", case sensitive!
texid, errmsg = soil.load_single_cubemap(
		"dice.png",	"EWUDNS", 'auto', nil, 'mipmaps')
assert(texid, errmsg)
print(string.format("Loaded texture %d (should be 2)", texid))

data, w, h, channels = soil.load_image("dice.png", 'rgb')
assert(data, soil.last_result())
print(string.format("Loaded %dx%d %s image (%d bytes)", w, h, channels, #data))

ok = soil.save_image("dice.dds", "dds", w, h, channels, data)
assert(ok, soil.last_result())



