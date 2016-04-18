/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Stefano Trettel
 *
 * Software repository: MoonFLTK, https://github.com/stetre/moonfltk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "internal.h"

/*--------------------------------------------------------------------------*
 | channels                                                                 |
 *--------------------------------------------------------------------------*/

int check_force_channels(lua_State *L, int arg)
    {
    const char *s = luaL_checkstring(L, arg);
#define CASE(CODE,str) if((strcmp(s, str)==0)) return CODE
        CASE(SOIL_LOAD_AUTO, "auto");
        CASE(SOIL_LOAD_L, "luminous");
        CASE(SOIL_LOAD_LA, "luminous/alpha");
        CASE(SOIL_LOAD_RGB, "rgb");
        CASE(SOIL_LOAD_RGBA, "rgba");
#undef CASE
    return luaL_argerror(L, arg, badvalue(L,s));
    }


int check_channels(lua_State *L, int arg)
    {
    const char *s = luaL_checkstring(L, arg);
#define CASE(CODE,str) if((strcmp(s, str)==0)) return CODE
   //   CASE(SOIL_LOAD_AUTO, "auto"); not admitted here
        CASE(SOIL_LOAD_L, "luminous");
        CASE(SOIL_LOAD_LA, "luminous/alpha");
        CASE(SOIL_LOAD_RGB, "rgb");
        CASE(SOIL_LOAD_RGBA, "rgba");
#undef CASE
    return luaL_argerror(L, arg, badvalue(L,s));
    }

int push_channels(lua_State *L, int val)
    {
    switch(val)
        {
#define CASE(CODE,str) case CODE: lua_pushstring(L, str); break
        CASE(SOIL_LOAD_AUTO, "auto");
        CASE(SOIL_LOAD_L, "luminous");
        CASE(SOIL_LOAD_LA, "luminous/alpha");
        CASE(SOIL_LOAD_RGB, "rgb");
        CASE(SOIL_LOAD_RGBA, "rgba");
#undef CASE
        default:
            return unexpected(L);
        }
    return 1;
    }

/*--------------------------------------------------------------------------*
 | face_order                                                               |
 *--------------------------------------------------------------------------*/

int check_face_order(lua_State *L, int arg, char face_order[6]) 
/* "EWUDNS" (east, west, up, down, north, south) */
    {
    size_t len;
    const char *s = luaL_checklstring(L, arg, &len);
    if(len != 6)
        return luaL_argerror(L, arg, "string length must be 6");
    strncpy(face_order, s, 6);
    return 0;
    }


/*--------------------------------------------------------------------------*
 | flags                                                                    |
 *--------------------------------------------------------------------------*/

int check_flags(lua_State *L, int arg)
    {
    unsigned int flags = 0;
    const char *s;

    if(lua_type(L, arg) == LUA_TNUMBER)
        return luaL_checkinteger(L, arg);

    while(lua_isstring(L, arg))
        {
        s = lua_tostring(L, arg++);
#define CASE(CODE,str) if((strcmp(s, str)==0)) do { flags |= CODE; goto done; } while(0)
        CASE(SOIL_FLAG_POWER_OF_TWO, "power of two");
        CASE(SOIL_FLAG_MIPMAPS, "mipmaps");
        CASE(SOIL_FLAG_TEXTURE_REPEATS, "texture repeats");
        CASE(SOIL_FLAG_MULTIPLY_ALPHA, "multiply alpha");
        CASE(SOIL_FLAG_INVERT_Y, "invert y");
        CASE(SOIL_FLAG_COMPRESS_TO_DXT, "compress to dxt");
        CASE(SOIL_FLAG_DDS_LOAD_DIRECT, "dds load direct");
        CASE(SOIL_FLAG_NTSC_SAFE_RGB, "ntsc safe rgb");
        CASE(SOIL_FLAG_CoCg_Y, "ycocg");
        CASE(SOIL_FLAG_TEXTURE_RECTANGLE, "texture rectangle");
#undef CASE
        return (int)luaL_argerror(L, --arg, badvalue(L,s));
        done: ;
        }
    return (int)flags;
    }

int push_flags(lua_State *L, int flags, int pushcode)
    {
    int n = 0;
    if(pushcode)
        { lua_pushinteger(L, flags); return 1; }

#define CASE(CODE,str) if(flags & CODE) do { lua_pushstring(L, str); n++; } while(0)
        CASE(SOIL_FLAG_POWER_OF_TWO, "power of two");
        CASE(SOIL_FLAG_MIPMAPS, "mipmaps");
        CASE(SOIL_FLAG_TEXTURE_REPEATS, "texture repeats");
        CASE(SOIL_FLAG_MULTIPLY_ALPHA, "multiply alpha");
        CASE(SOIL_FLAG_INVERT_Y, "invert y");
        CASE(SOIL_FLAG_COMPRESS_TO_DXT, "compress to dxt");
        CASE(SOIL_FLAG_DDS_LOAD_DIRECT, "dds load direct");
        CASE(SOIL_FLAG_NTSC_SAFE_RGB, "ntsc safe rgb");
        CASE(SOIL_FLAG_CoCg_Y, "ycocg");
        CASE(SOIL_FLAG_TEXTURE_RECTANGLE, "texture rectangle");
#undef CASE
    return n;
    }


/*--------------------------------------------------------------------------*
 | fake_hdr                                                                 |
 *--------------------------------------------------------------------------*/

int check_fake_hdr(lua_State *L, int arg)
    {
    const char *s = luaL_checkstring(L, arg);
#define CASE(CODE,str) if((strcmp(s, str)==0)) return CODE
        CASE(SOIL_HDR_RGBE, "rgbe");
        CASE(SOIL_HDR_RGBdivA, "rgbdiva");
        CASE(SOIL_HDR_RGBdivA2, "rgbdiva2");
#undef CASE
    return luaL_argerror(L, arg, badvalue(L,s));
    }

int push_fake_hdr(lua_State *L, int val)
    {
    switch(val)
        {
#define CASE(CODE,str) case CODE: lua_pushstring(L, str); break
        CASE(SOIL_HDR_RGBE, "rgbe");
        CASE(SOIL_HDR_RGBdivA, "rgbdiva");
        CASE(SOIL_HDR_RGBdivA2, "rgbdiva2");
#undef CASE
        default:
            return unexpected(L);
        }
    return 1;
    }

/*--------------------------------------------------------------------------*
 | image_type                                                               |
 *--------------------------------------------------------------------------*/

int check_image_type(lua_State *L, int arg)
    {
    const char *s = luaL_checkstring(L, arg);
#define CASE(CODE,str) if((strcmp(s, str)==0)) return CODE
        CASE(SOIL_SAVE_TYPE_TGA, "tga");
        CASE(SOIL_SAVE_TYPE_BMP, "bmp");
        CASE(SOIL_SAVE_TYPE_DDS, "dds");
#undef CASE
    return luaL_argerror(L, arg, badvalue(L,s));
    }

int push_image_type(lua_State *L, int val)
    {
    switch(val)
        {
#define CASE(CODE,str) case CODE: lua_pushstring(L, str); break
        CASE(SOIL_SAVE_TYPE_TGA, "tga");
        CASE(SOIL_SAVE_TYPE_BMP, "bmp");
        CASE(SOIL_SAVE_TYPE_DDS, "dds");
#undef CASE
        default:
            return unexpected(L);
        }
    return 1;
    }

