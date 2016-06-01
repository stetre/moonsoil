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

/********************************************************************************
 * internal common header                                                       *
 ********************************************************************************/

#ifndef internalDEFINED
#define internalDEFINED


#include <string.h>
#include <stdlib.h>
#include "moonsoil.h"
//#include <SOIL/SOIL.h>
#include "SOIL.h"

#define TOSTR_(x) #x
#define TOSTR(x) TOSTR_(x)

/* Note: all the dynamic symbols of this library (should) start with 'moonsoil_' .
 * The only exception is the luaopen_moonsoil() function, which is searched for
 * with that name by Lua.
 * MoonSOIL's string references on the Lua registry also start with 'moonsoil_'.
 */

#if 0
/* .cc */
#define  moonsoil_
#endif

/* utils.cc */
double moonsoil_now(void);
void moonsoil_sleep(double seconds);
#define noprintf moonsoil_noprintf
int noprintf(const char *fmt, ...);
#define printstack moonsoil_printstack
void printstack(lua_State *L, const char* fmat, ...);
#define notavailable moonsoil_notavailable
int notavailable(lua_State *L, ...);
#define checkboolean moonsoil_checkboolean
int checkboolean(lua_State *L, int arg);
#define optboolean moonsoil_optboolean
int optboolean(lua_State *L, int arg, int d);
#define testchar moonsoil_testchar
int testchar(lua_State *L, int arg, char *c_);
#define checkascii moonsoil_checkascii
char checkascii(lua_State *L, int arg);
#define pushascii moonsoil_pushascii
int pushascii(lua_State *L, char c);
#define checkindex moonsoil_checkindex
int checkindex(lua_State *L, int arg);
#define optindex moonsoil_optindex
int optindex(lua_State *L, int arg, int optval);
#define pushindex moonsoil_pushindex
void pushindex(lua_State *L, int val);
#define checkpositiveinteger moonsoil_checkpositiveinteger
int checkpositiveinteger(lua_State *L, int arg);
#define checkoption_hint moonsoil_checkoption_hint 
int checkoption_hint(lua_State *L, int arg, const char *def, const char *const lst[]);

/* enum.cc */
#define check_force_channels moonsoil_check_force_channels
int check_force_channels(lua_State *L, int arg);
#define check_channels moonsoil_check_channels
int check_channels(lua_State *L, int arg);
#define push_channels moonsoil_push_channels
int push_channels(lua_State *L, int val);
#define check_flags moonsoil_check_flags
int check_flags(lua_State *L, int arg);
#define push_flags moonsoil_push_flags
int push_flags(lua_State *L, int flags, int pushcode);
#define check_face_order moonsoil_check_face_order
int check_face_order(lua_State *L, int arg, char face_order[6]);
#define check_fake_hdr moonsoil_check_fake_hdr
int check_fake_hdr(lua_State *L, int arg);
#define push_fake_hdr moonsoil_push_fake_hdr
int push_fake_hdr(lua_State *L, int val);
#define check_image_type moonsoil_check_image_type
int check_image_type(lua_State *L, int arg);
#define push_image_type moonsoil_push_image_type
int push_image_type(lua_State *L, int val);

/* main.c */
int luaopen_moonsoil(lua_State *L);
void moonsoil_open_soil(lua_State *L);

/*------------------------------------------------------------------------------*
 | Debug and other utilities                                                    |
 *------------------------------------------------------------------------------*/

/* Dynamic referencing on the Lua registry */

#define reference(L, dst, arg) do {                 \
    lua_pushvalue((L), (arg));                      \
    (dst) = luaL_ref((L), LUA_REGISTRYINDEX);       \
} while(0)

#define unreference(L, ref) do {                    \
    if((ref)!=LUA_NOREF) {                          \
        luaL_unref((L), LUA_REGISTRYINDEX, (ref));  \
        (ref) = LUA_NOREF; }                        \
} while(0)

#define pushvalue(L, ref) /* returns LUA_TXXX */    \
    lua_rawgeti((L), LUA_REGISTRYINDEX, (ref)) 

extern int moonsoil_trace_objects;
#define DBG_CREATE(T, p) \
    if(moonsoil_trace_objects) printf("creating "#T" %p\n", (void*)(p))
#define DBG_DELETE(T, p) \
    if(moonsoil_trace_objects) printf("deleting "#T" %p\n", (void*)(p))



/* If this is printed, it denotes a suspect bug: */
#define UNEXPECTED_ERROR "unexpected error (%s, %d)", __FILE__, __LINE__
#define MEMORY_ERROR "cannot allocate memory (%s, %d)", __FILE__, __LINE__
#define NOT_AVAILABLE do { return luaL_error(L, "function not available"); } while(0)

#define unexpected(L) luaL_error((L), UNEXPECTED_ERROR)
#define memoryerror(L) luaL_error((L), MEMORY_ERROR)
#define badvalue(L,s)   lua_pushfstring((L), "invalid value '%s'", (s))

#if defined(DEBUG) 
/*--------------------------------------------------------------------*/

#define TR_STACK(L) printstack((L),"%s %d\n",__FILE__,__LINE__)

#define checkoption checkoption_hint
#define DBG printf

#define TR() do {                                           \
    printf("trace %s %d\n",__FILE__,__LINE__);              \
} while(0)

#define BK() do {                                           \
    printf("break %s %d\n",__FILE__,__LINE__);              \
    getchar();                                              \
} while(0)

#else  /* NO DEBUG */
/*--------------------------------------------------------------------*/

#define TR_STACK(L) (void)(L)
#define checkoption luaL_checkoption
#define DBG noprintf
#define TR()
#define BK()

#endif /* DEBUG */
/*--------------------------------------------------------------------*/

#endif /* internalDEFINED */
