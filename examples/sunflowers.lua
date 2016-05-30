-- MoonSOIL example: sunflowers.lua

soil = require("moonsoil")

-- Load an image in grayscale, and save it in another file.
data, w, h, channels = soil.load_image("sunflowers.jpg", 'luminous/alpha')
assert(data, soil.last_result())
ok = soil.save_image("sunflowers.bmp", "bmp", w, h, channels, data)
assert(ok, soil.last_result())

