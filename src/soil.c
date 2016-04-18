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

#define checklbuffer(L, arg, lenp)  \
    (const unsigned char *const)luaL_checklstring((L), (arg), lenp)
    
#define ReturnNilErrmsg(L) do   {                                       \
    lua_pushnil(L); lua_pushstring(L, SOIL_last_result());  return 2;   \
} while(0)                                                              \

#define ReturnFalseErrmsg(L) do {                                       \
    lua_pushboolean(L, 0); lua_pushstring(L, SOIL_last_result());   return 2;   \
} while(0)                                                              \

static size_t datalen(int width, int height, int channels)
    {
    return width * height * channels;
    }



static int Load_texture(lua_State *L)
    {
    const char *filename = luaL_checkstring(L, 1);
    int force_channels = check_force_channels(L, 2);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 3, 0);
    unsigned int flags = check_flags(L, 4);

    unsigned int tex = 
        SOIL_load_OGL_texture(filename, force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }


static int Load_cubemap(lua_State *L)
    {
    const char *x_pos_file = luaL_checkstring(L, 1);
    const char *x_neg_file = luaL_checkstring(L, 2);
    const char *y_pos_file = luaL_checkstring(L, 3);
    const char *y_neg_file = luaL_checkstring(L, 4);
    const char *z_pos_file = luaL_checkstring(L, 5);
    const char *z_neg_file = luaL_checkstring(L, 6);
    int force_channels = check_force_channels(L, 7);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 8, 0);
    unsigned int flags = check_flags(L, 9);

    unsigned int tex = SOIL_load_OGL_cubemap(
            x_pos_file, x_neg_file, y_pos_file, y_neg_file, z_pos_file, z_neg_file,
            force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

    
static int Load_single_cubemap(lua_State *L)
    {
    unsigned int tex;
    char face_order[6];
    const char *filename = luaL_checkstring(L, 1);
    int force_channels = check_force_channels(L, 3);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 4, 0);
    unsigned int flags = check_flags(L, 5);
    check_face_order(L, 2, face_order);

    tex = SOIL_load_OGL_single_cubemap(
        filename, face_order, force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }
    
static int Load_hdr_texture(lua_State *L)
    {
    unsigned int tex;
    const char *filename = luaL_checkstring(L, 1);
    int fake_HDR_format = check_fake_hdr(L, 2);
    int rescale_to_max = checkboolean(L, 3);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 4, 0);
    unsigned int flags = check_flags(L, 5);

    tex = SOIL_load_OGL_HDR_texture(
            filename, fake_HDR_format, rescale_to_max, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

static int Load_texture_from_memory(lua_State *L)
    {
    unsigned int tex;
    size_t len;
    const unsigned char *const buffer = checklbuffer(L, 1, &len);
    int force_channels = check_force_channels(L, 2);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 3, 0);
    unsigned int flags = check_flags(L, 4);

    tex = SOIL_load_OGL_texture_from_memory(
        buffer, (int)len, force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

    
static int Load_cubemap_from_memory(lua_State *L)
    {
    unsigned int tex;
    size_t x_pos_len, x_neg_len, y_pos_len, y_neg_len,  z_pos_len, z_neg_len;
    const unsigned char *const x_pos_buffer = checklbuffer(L, 1, &x_pos_len);
    const unsigned char *const x_neg_buffer = checklbuffer(L, 2, &x_neg_len);
    const unsigned char *const y_pos_buffer = checklbuffer(L, 3, &y_pos_len);
    const unsigned char *const y_neg_buffer = checklbuffer(L, 4, &y_neg_len);
    const unsigned char *const z_pos_buffer = checklbuffer(L, 5, &z_pos_len);
    const unsigned char *const z_neg_buffer = checklbuffer(L, 6, &z_neg_len);
    int force_channels = check_force_channels(L, 7);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 8, 0);
    unsigned int flags = check_flags(L, 9);

    tex = SOIL_load_OGL_cubemap_from_memory(
                x_pos_buffer, x_pos_len, x_neg_buffer, x_neg_len,
                y_pos_buffer, y_pos_len, y_neg_buffer, y_neg_len,
                z_pos_buffer, z_pos_len, z_neg_buffer, z_neg_len,
                force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

    
static int Load_single_cubemap_from_memory(lua_State *L)
    {
    unsigned int tex;
    size_t len;
    char face_order[6];
    const unsigned char *const buffer = checklbuffer(L, 1, &len);
    int force_channels = check_force_channels(L, 3);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 4, 0);
    unsigned int flags = check_flags(L, 5);
    check_face_order(L, 2, face_order);

    tex = SOIL_load_OGL_single_cubemap_from_memory(
                buffer, len, face_order, force_channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

    
static int Create_texture(lua_State *L)
    {
    unsigned int tex;
    size_t len;
    const unsigned char *const data = checklbuffer(L, 1, &len); 
    int width = luaL_checkinteger(L, 2); 
    int height = luaL_checkinteger(L, 3); 
    int channels = check_channels(L, 4);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 5, 0);
    unsigned int flags = check_flags(L, 6);

    if(len < datalen(width, height, channels))
        return luaL_argerror(L, 1, "too few bytes of data");

    tex = SOIL_create_OGL_texture(
        data, width, height, channels, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

    
static int Create_single_cubemap(lua_State *L)
    {
    unsigned int tex;
    size_t len;
    char face_order[6];
    const unsigned char *const data = checklbuffer(L, 1, &len); 
    int width = luaL_checkinteger(L, 2); 
    int height = luaL_checkinteger(L, 3); 
    int channels = check_channels(L, 4);
    unsigned int reuse_texture_ID = luaL_optinteger(L, 6, 0);
    unsigned int flags = check_flags(L, 7);
    check_face_order(L, 5, face_order);

    if(len < datalen(width, height, channels))
        return luaL_argerror(L, 1, "too few bytes of data");

    tex = SOIL_create_OGL_single_cubemap(
            data, width, height, channels, face_order, reuse_texture_ID, flags);

    if(tex == 0)
        ReturnNilErrmsg(L);
    lua_pushinteger(L, tex);
    return 1;
    }

static int Save_screenshot(lua_State *L)
    {
    const char *filename = luaL_checkstring(L, 1);
    int image_type = check_image_type(L, 2);
    int x = luaL_checkinteger(L, 3); 
    int y = luaL_checkinteger(L, 4); 
    int width = luaL_checkinteger(L, 5); 
    int height = luaL_checkinteger(L, 6); 

    int res = SOIL_save_screenshot(filename, image_type, x, y, width, height);

    if(res == 0)
        ReturnFalseErrmsg(L);
    lua_pushboolean(L, 1);
    return 1;
    }


    
    
static int Load_image(lua_State *L)
    {
    size_t len;
    unsigned char* data;
    int width, height, channels;
    const char *filename = luaL_checkstring(L, 1);
    int force_channels = check_force_channels(L, 2);

    data = SOIL_load_image(filename, &width, &height, &channels, force_channels);

    if(data == NULL)
        ReturnNilErrmsg(L);

    if(force_channels != SOIL_LOAD_AUTO) channels = force_channels;
    len = datalen(width, height, channels);
    
    lua_pushlstring(L, (char*)data, len);
    lua_pushinteger(L, width);
    lua_pushinteger(L, height);
    push_channels(L, channels);
    SOIL_free_image_data(data);
    return 4;
    }

static int Load_image_from_memory(lua_State *L)
    {
    size_t len;
    unsigned char* data;
    int width, height, channels;
    const unsigned char *const buffer = checklbuffer(L, 1, &len); 
    int force_channels = check_force_channels(L, 2);

    data = SOIL_load_image_from_memory(buffer, len, &width, &height, &channels, force_channels);

    if(data == NULL)
        ReturnNilErrmsg(L);

    if(force_channels != SOIL_LOAD_AUTO) channels = force_channels;
    len = datalen(width, height, channels);
    
    lua_pushlstring(L, (char*)data, len);
    lua_pushinteger(L, width);
    lua_pushinteger(L, height);
    push_channels(L, channels);
    SOIL_free_image_data(data);
    return 4;
    }

static int Save_image(lua_State *L)
    {
    size_t len;
    int res;
    const char *filename = luaL_checkstring(L, 1);
    int image_type = check_image_type(L, 2);
    int width = luaL_checkinteger(L, 3); 
    int height = luaL_checkinteger(L, 4); 
    int channels = check_channels(L, 5);
    const unsigned char *const data = checklbuffer(L, 6, &len); 

//  printf("w=%d h=%d len=%lu data=%p\n", width, height, len, (void*)data);
    if(len < datalen(width, height, channels))
        return luaL_argerror(L, 1, "too few bytes of data");

    res = SOIL_save_image(filename, image_type, width, height, channels, data);

    if(res == 0)
        ReturnFalseErrmsg(L);
    lua_pushboolean(L, 1);
    return 1;
    }


static int Last_result(lua_State *L)
    {
    const char *s = SOIL_last_result();
    if(!s) return 0;
    lua_pushstring(L, s);
    return 1;
    }

static int Channels(lua_State *L)
    {
    int channels = check_channels(L, 1);
    lua_pushinteger(L, channels);
    return 1;
    }


/*------------------------------------------------------------------------------*
 | Registration                                                                 |
 *------------------------------------------------------------------------------*/

static const struct luaL_Reg Functions[] = 
    {
        { "load_texture", Load_texture },
        { "load_cubemap", Load_cubemap },
        { "load_single_cubemap", Load_single_cubemap },
        { "load_hdr_texture", Load_hdr_texture },
        { "load_texture_from_memory", Load_texture_from_memory },
        { "load_cubemap_from_memory", Load_cubemap_from_memory },
        { "load_single_cubemap_from_memory", Load_single_cubemap_from_memory },
        { "create_texture", Create_texture },
        { "create_single_cubemap", Create_single_cubemap },
        { "save_screenshot", Save_screenshot },
        { "load_image", Load_image },
        { "load_image_from_memory", Load_image_from_memory },
        { "save_image", Save_image },
        { "last_result", Last_result },
        { "channels", Channels },
        { NULL, NULL } /* sentinel */
    };

void moonsoil_open_soil(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

