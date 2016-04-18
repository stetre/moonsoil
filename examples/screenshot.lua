-- MoonSOIL example: load_image.lua

soil = require("moonsoil")

ok = soil.save_screenshot("screenshot.bmp", 'bmp', 0, 0, 1024, 768)
assert(ok, soil.last_result())
-- Note: this saves a screenshot of the rendered area. Since in this
-- example we do not have a rendered area, the picture is black.

