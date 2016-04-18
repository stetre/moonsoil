/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Stefano Trettel
 *
 * Software repository: MoonSOIL, https://github.com/stetre/moonsoil
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

static void AddVersions(lua_State *L)
/* Add version strings to the soil table */
    {
    lua_pushstring(L, "_VERSION");
    lua_pushstring(L, "MoonSOIL "MOONSOIL_VERSION);
    lua_settable(L, -3);
    }

static int AddConstants(lua_State *L) /* soil.XXXXX constants for SOIL_XXXXX defines */
    {
#define ADD(c) do { \
    lua_pushinteger(L, SOIL_##c); lua_setfield(L, -2, #c); } while(0)
    ADD(FLAG_POWER_OF_TWO);
    ADD(FLAG_MIPMAPS);
    ADD(FLAG_TEXTURE_REPEATS);
    ADD(FLAG_MULTIPLY_ALPHA);
    ADD(FLAG_INVERT_Y);
    ADD(FLAG_COMPRESS_TO_DXT);
    ADD(FLAG_DDS_LOAD_DIRECT);
    ADD(FLAG_NTSC_SAFE_RGB);
    ADD(FLAG_CoCg_Y);
    ADD(FLAG_TEXTURE_RECTANGLE);
#undef ADD
    return 0;
    }


/*------------------------------------------------------------------------------*
 | Registration                                                                 |
 *------------------------------------------------------------------------------*/

static const struct luaL_Reg Functions[] = 
    {
        { NULL, NULL } /* sentinel */
    };


int luaopen_moonsoil(lua_State *L)
/* Lua calls this function to load the module */
    {
    lua_newtable(L); /* the soil table */
    AddVersions(L);
    AddConstants(L);

    /* add soil functions: */
    luaL_setfuncs(L, Functions, 0);
    moonsoil_open_soil(L);

    return 1;
    }

