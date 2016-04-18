-- MoonSOIL example: load_image.lua

soil = require("moonsoil")

-- Load and image from a file. The image is returned as a binary string.
data, w, h, channels = soil.load_image("dice6.png", 'rgb')
-- Check if an error occurred:
assert(data, soil.last_result())

print(string.format("Loaded %dx%d %s image (%d bytes)", w, h, channels, #data))

