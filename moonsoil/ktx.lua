-- The MIT License (MIT)
--
-- Copyright (c) 2017 Stefano Trettel
--
-- Software repository: MoonSoil, https://github.com/stetre/moonsoil
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in all
-- copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
-- SOFTWARE.
-- 

-- *********************************************************************
-- DO NOT require() THIS MODULE (it is loaded automatically by MoonSoil)
-- *********************************************************************

local soil = moonsoil -- require("moonsoil")

-- KTX File Format Specification:
-- https://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/

-- KTX File Identifier --------------------------------------------------------
local KTX_ID = "\xabKTX 11\xbb\r\n\x1a\n"

-- GL Codes (see GL/glcorearb.h) ----------------------------------------------
local glType = {
   [0] = "zero",
   [0x1401] = "unsigned byte",
   [0x1400] = "byte",
   [0x1403] = "unsigned short",
   [0x1402] = "short",
   [0x1405] = "unsigned int",
   [0x1404] = "int",
   [0x140B] = "half float",
   [0x1406] = "float",
   [0x8032] = "unsigned byte 3 3 2",
   [0x8362] = "unsigned byte 2 3 3 rev",
   [0x8363] = "unsigned short 5 6 5",
   [0x8364] = "unsigned short 5 6 5 rev",
   [0x8033] = "unsigned short 4 4 4 4",
   [0x8365] = "unsigned short 4 4 4 4 rev",
   [0x8034] = "unsigned short 5 5 5 1",
   [0x8366] = "unsigned short 1 5 5 5 rev",
   [0x8035] = "unsigned int 8 8 8 8",
   [0x8367] = "unsigned int 8 8 8 8 rev",
   [0x8036] = "unsigned int 10 10 10 2",
   [0x8368] = "unsigned int 2 10 10 10 rev",
   [0x84FA] = "unsigned int 24 8",
   [0x8C3B] = "unsigned int 10f 11f 11f rev",
   [0x8C3E] = "unsigned int 5 9 9 9 rev",
   [0x8DAD] = "float 32 unsigned int 24 8 rev",
}

local glInternalFormat = {
   [0x8229] = "r8",
   [0x8F94] = "r8 snorm",
   [0x822A] = "r16",
   [0x8F98] = "r16 snorm",
   [0x822B] = "rg8",
   [0x8F95] = "rg8 snorm",
   [0x822C] = "rg16",
   [0x8F99] = "rg16 snorm",
   [0x2A10] = "r3 g3 b2",
   [0x804F] = "rgb4",
   [0x8050] = "rgb5",
   [0x8D62] = "rgb565",
   [0x8051] = "rgb8",
   [0x8F96] = "rgb8 snorm",
   [0x8052] = "rgb10",
   [0x8053] = "rgb12",
   [0x8054] = "rgb16",
   [0x8F9A] = "rgb16 snorm",
   [0x8055] = "rgba2",
   [0x8056] = "rgba4",
   [0x8057] = "rgb5 a1",
   [0x8058] = "rgba8",
   [0x8F97] = "rgba8 snorm",
   [0x8059] = "rgb10 a2",
   [0x906F] = "rgb10 a2ui",
   [0x805A] = "rgba12",
   [0x805B] = "rgba16",
   [0x8F9B] = "rgba16 snorm",
   [0x8C41] = "srgb8",
   [0x8C43] = "srgb8 alpha8",
   [0x822D] = "r16f",
   [0x822F] = "rg16f",
   [0x881B] = "rgb16f",
   [0x881A] = "rgba16f",
   [0x822E] = "r32f",
   [0x8230] = "rg32f",
   [0x8815] = "rgb32f",
   [0x8814] = "rgba32f",
   [0x8C3A] = "r11f g11f b10f",
   [0x8C3D] = "rgb9 e5",
   [0x8231] = "r8i",
   [0x8232] = "r8ui",
   [0x8233] = "r16i",
   [0x8234] = "r16ui",
   [0x8235] = "r32i",
   [0x8236] = "r32ui",
   [0x8237] = "rg8i",
   [0x8238] = "rg8ui",
   [0x8239] = "rg16i",
   [0x823A] = "rg16ui",
   [0x823B] = "rg32i",
   [0x823C] = "rg32ui",
   [0x8D8F] = "rgb8i",
   [0x8D7D] = "rgb8ui",
   [0x8D89] = "rgb16i",
   [0x8D77] = "rgb16ui",
   [0x8D83] = "rgb32i",
   [0x8D71] = "rgb32ui",
   [0x8D8E] = "rgba8i",
   [0x8D7C] = "rgba8ui",
   [0x8D88] = "rgba16i",
   [0x8D76] = "rgba16ui",
   [0x8D82] = "rgba32i",
   [0x8D70] = "rgba32ui",
   [0x81A5] = "depth component16",
   [0x81A6] = "depth component24",
   [0x81A7] = "depth component32",
   [0x8CAC] = "depth component32f",
   [0x88F0] = "depth24 stencil8",
   [0x8CAD] = "depth32f stencil8",
   [0x8D46] = "stencil index1",
   [0x8D47] = "stencil index4",
   [0x8D48] = "stencil index8",
   [0x8D49] = "stencil index16",
   [0x8225] = "compressed red",
   [0x8226] = "compressed rg",
   [0x84ED] = "compressed rgb",
   [0x84EE] = "compressed rgba",
   [0x8C48] = "compressed srgb",
   [0x8C49] = "compressed srgb alpha",
   [0x8DBB] = "compressed red rgtc1",
   [0x8DBC] = "compressed signed red rgtc1",
   [0x8DBD] = "compressed rg rgtc2",
   [0x8DBE] = "compressed signed rg rgtc2",
   [0x8E8C] = "compressed rgba bptc unorm",
   [0x8E8D] = "compressed srgb alpha bptc unorm",
   [0x8E8E] = "compressed rgb bptc signed float",
   [0x8E8F] = "compressed rgb bptc unsigned float",
   [0x9274] = "compressed rgb8 etc2",
   [0x9275] = "compressed srgb8 etc2",
   [0x9276] = "compressed rgb8 punchthrough alpha1 etc2",
   [0x9277] = "compressed srgb8 punchthrough alpha1 etc2",
   [0x9278] = "compressed rgba8 etc2 eac",
   [0x9279] = "compressed srgb8 alpha8 etc2 eac",
   [0x9270] = "compressed r11 eac",
   [0x9271] = "compressed signed r11 eac",
   [0x9272] = "compressed rg11 eac",
   [0x9273] = "compressed signed rg11 eac",
   [0x93B0] = "compressed rgba astc 4x4",
   [0x93B1] = "compressed rgba astc 5x4",
   [0x93B2] = "compressed rgba astc 5x5",
   [0x93B3] = "compressed rgba astc 6x5",
   [0x93B4] = "compressed rgba astc 6x6",
   [0x93B5] = "compressed rgba astc 8x5",
   [0x93B6] = "compressed rgba astc 8x6",
   [0x93B7] = "compressed rgba astc 8x8",
   [0x93B8] = "compressed rgba astc 10x5",
   [0x93B9] = "compressed rgba astc 10x6",
   [0x93BA] = "compressed rgba astc 10x8",
   [0x93BB] = "compressed rgba astc 10x10",
   [0x93BC] = "compressed rgba astc 12x10",
   [0x93BD] = "compressed rgba astc 12x12",
   [0x93D0] = "compressed srgb8 alpha8 astc 4x4",
   [0x93D1] = "compressed srgb8 alpha8 astc 5x4",
   [0x93D2] = "compressed srgb8 alpha8 astc 5x5",
   [0x93D3] = "compressed srgb8 alpha8 astc 6x5",
   [0x93D4] = "compressed srgb8 alpha8 astc 6x6",
   [0x93D5] = "compressed srgb8 alpha8 astc 8x5",
   [0x93D6] = "compressed srgb8 alpha8 astc 8x6",
   [0x93D7] = "compressed srgb8 alpha8 astc 8x8",
   [0x93D8] = "compressed srgb8 alpha8 astc 10x5",
   [0x93D9] = "compressed srgb8 alpha8 astc 10x6",
   [0x93DA] = "compressed srgb8 alpha8 astc 10x8",
   [0x93DB] = "compressed srgb8 alpha8 astc 10x10",
   [0x93DC] = "compressed srgb8 alpha8 astc 12x10",
   [0x93DD] = "compressed srgb8 alpha8 astc 12x12",
   [0x83F0] = "compressed rgb s3tc dxt1",
   [0x83F1] = "compressed rgba s3tc dxt1",
   [0x83F2] = "compressed rgba s3tc dxt3",
   [0x83F3] = "compressed rgba s3tc dxt5",
   [0x86B0] = "compressed rgb fxt1 3dfx",
   [0x86B1] = "compressed rgba fxt1 3dfx",
   [0x8837] = "compressed luminance alpha 3dc",
   [0x8C4A] = "compressed sluminance",
   [0x8C4B] = "compressed sluminance alpha",
   [0x8C4C] = "compressed srgb s3tc dxt1",
   [0x8C4D] = "compressed srgb alpha s3tc dxt1",
   [0x8C4E] = "compressed srgb alpha s3tc dxt3",
   [0x8C4F] = "compressed srgb alpha s3tc dxt5",
   [0x84E9] = "compressed alpha",
   [0x84EA] = "compressed luminance",
   [0x84EB] = "compressed luminance alpha",
   [0x84EC] = "compressed intensity",
   [0x8C71] = "compressed signed luminance latc1",
   [0x8C70] = "compressed luminance latc1",
   [0x8C72] = "compressed luminance alpha latc2",
   [0x8C73] = "compressed signed luminance alpha latc2",
}

local glFormat = {
   [0] = "zero",
   [0x1901] = "stencil index",
   [0x1902] = "depth component",
   [0x84F9] = "depth stencil",
   [0x1903] = "red",
   [0x1904] = "green",
   [0x1905] = "blue",
   [0x8227] = "rg",
   [0x1907] = "rgb",
   [0x1908] = "rgba",
   [0x80E0] = "bgr",
   [0x80E1] = "bgra",
   [0x8D94] = "red integer",
   [0x8D95] = "green integer",
   [0x8D96] = "blue integer",
   [0x8228] = "rg integer",
   [0x8D98] = "rgb integer",
   [0x8D99] = "rgba integer",
   [0x8D9A] = "bgr integer",
   [0x8D9B] = "bgra integer",
}

local function unknown(val) return string.format("unknown (0x%.8X)", val) end
local MALFORMATTED = "malformatted file"

--==============================================================================

function soil.load_ktx(filename)
-- Loads a KTX file, decodes it and returns a table with the decoded contents.
-- filename = full path to the .ktx file to be loaded.

   local f, msg = io.open(filename, "rb")
   assert(f, msg)

   local t = {}
   t.filename = filename

   -- Identifier (12 bytes) ---------------------------------------------------
   local identifier = f:read(12)
   assert(identifier, MALFORMATTED)
   assert(identifier == KTX_ID, "invalid file identifier")
   
   -- Endianness (uint32) -----------------------------------------------------
   local pfx -- prefix for subsequent string.unpack()s
   local endianness = f:read(4)
   assert(endianness , MALFORMATTED)
   local swap_needed = string.unpack("I4", endianness) ~= 0x04030201
   if endianness == "\x01\x02\x03\x04" then
      t.little_endian = true
      pfx = '<' 
   elseif endianness == "\x04\x03\x02\x01" then 
      t.little_endian = false
      pfx = '>'
   else 
      error("invalid endianness value")
   end

   -- Reads next uint32 field from f, and unpacks it with the correct endianness:
   local function read_u32()
      local val = f:read(4)
      assert(val, MALFORMATTED)
      return string.unpack(pfx.."I4", val)
   end

   -- Read the other header fields ----------------------------------------------
   local val = read_u32()
   t.gl_type = glType[val] or unknown(val)
   t.gl_type_size = read_u32()

   -- If swap_needed, we need to endian-swap texture data in chunks of t.gl_type_size bytes
   if t.gl_type_size == 0 or t.gl_type_size == 1 then swap_needed = false end
   assert(not swap_needed, "endian-swap of texture data is not supported yet") -- @@TODO

   val = read_u32()
   t.gl_format = glFormat[val] or unknown(val)
   val = read_u32()
   t.gl_internal_format = glInternalFormat[val] or unknown(val)
   val = read_u32()
   t.gl_base_internal_format = glFormat[val] or unknown(val)
   t.pixel_width = read_u32()
   t.pixel_height = read_u32()
   t.pixel_depth = read_u32()
   t.array_elements = read_u32()
   t.faces = read_u32()
   t.mipmap_levels = read_u32()
   local nbytes = read_u32()
   t.key_value_data = f:read(nbytes) -- bytesOfKeyValueData
   assert(t.key_value_data, MALFORMATTED)

   -- Deduce the texture type -------------------------------------------------
   local TextureType = {
   -- whdaf
      P0001 = '1d',
      P00P1 = '1d array',
      PP001 = '2d',
      PP0P1 = '2d array',
      PPP01 = '3d',
      PP006 = 'cube map',
      PP0P6 = 'cube map array',
   -- w = width, h = height, d = depth, a = array elements, f = faces, 
   -- P = positive, number = value
   -- All other combinations are invalid
   }

   local whdaf = ((t.pixel_width > 0) and "P" or "0")
               ..((t.pixel_height > 0) and "P" or "0")
               ..((t.pixel_depth > 0) and "P" or "0")
               ..((t.array_elements > 0) and "P" or "0")
               ..(t.faces)
   t.texture_type = TextureType[whdaf]
   assert(t.texture_type, "cannot deduce texture type (whdaf="..whdaf..")")

   -- When extracting the texture data, some fields must be set to 1 if they
   -- have a zero value (see (*) note in the spec):
   local function fix_zero(x) return x == 0 and 1 or x end

   local levels = fix_zero(t.mipmap_levels)
   local arrays = fix_zero(t.array_elements)
   local faces = t.faces
   local depth = fix_zero(t.pixel_depth)
   local height = fix_zero(t.pixel_height)
   local width = fix_zero(t.pixel_width)

   t.levels = {}
   for ml = 1, levels do
      local lvl = {}
      local size = read_u32()
      local padding = 3 - ((size+3)%4) -- length of padding
      lvl.width = width
      lvl.height = height
      lvl.depth = depth
      if ml == 1 then 
         t.pixels_per_byte = (width*height*depth)/size 
         -- should be >1 for compressed types, =1 otherwise
      end

      if t.texture_type == 'cube map' then
         lvl.face_size = size
         lvl.cube_padding = padding
         lvl.data = f:read((size+padding)*6)
         assert(lvl.data, MALFORMATTED)
      else
         lvl.size = size
         lvl.mip_padding = padding
         lvl.data = f:read(size+padding)
         assert(lvl.data, MALFORMATTED)
      end
      t.levels[ml] = lvl
      width = width>>1
      if height > 1 then height = height>>1 end
      if depth > 1 then depth = depth>>1 end
   end

   f:close()
   return t
end

function soil.ktx_data(t)
   local data = {}
   for _, lvl in ipairs(t.levels) do
      data[#data+1] = lvl.data
   end
   return table.concat(data)
end


function soil.ktx_tostring(t)
   local s = {}
   table.insert(s, "filename: ".. t.filename)
   table.insert(s, "little_endian: " .. tostring(t.little_endian))
   table.insert(s, "texture_type: " .. t.texture_type)
   table.insert(s, "gl_type: " .. t.gl_type)
   table.insert(s, "gl_type_size: " .. t.gl_type_size)
   table.insert(s, "gl_format: " .. t.gl_format)
   table.insert(s, "gl_internal_format: " .. t.gl_internal_format)
   table.insert(s, "gl_base_internal_format: " .. t.gl_base_internal_format)
-- table.insert(s, "pixel_width: " .. t.pixel_width)
-- table.insert(s, "pixel_height: " .. t.pixel_height)
-- table.insert(s, "pixel_depth: " .. t.pixel_depth)
   table.insert(s, "array_elements: " .. t.array_elements)
   table.insert(s, "faces: " .. t.faces)
   table.insert(s, "mipmap_levels: " .. t.mipmap_levels)
--   table.insert(s, "pixels_per_byte: " .. t.pixels_per_byte)
   table.insert(s, "#key_value_data: " .. #t.key_value_data)

   for i, lvl in ipairs(t.levels) do
      local ss = "level["..i.."] ("..lvl.width.." x "..lvl.height .." x "..lvl.depth..")"
      if t.texture_type == 'cube map' then
            ss = ss..", face_size: "..lvl.face_size..", cube_padding: "..lvl.cube_padding
               .. ", #data: "..#lvl.data
         assert(#lvl.data == 6*(lvl.face_size + lvl.cube_padding))
      else
            ss = ss..", size: "..lvl.size .. ", mip_padding: "..lvl.mip_padding
               ..", #data: "..#lvl.data
         assert(#lvl.data == lvl.size + lvl.mip_padding)
      end
      table.insert(s, ss)
   end
   return table.concat(s, '\n')
end

