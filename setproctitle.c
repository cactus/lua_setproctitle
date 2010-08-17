/*
 * Copyright 2009 elij
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
**/

#include "config.h"
#define LUA_LIB
#define luacronkite_c
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#ifdef HAVE_SYS_PRCTL_H
#include <sys/prctl.h>          /* for Linux >= 2.6.9 */
#include <linux/prctl.h>
#endif

static int setproctitle(lua_State *L);
static int getproctitle(lua_State *L);
LUALIB_API int luaopen_setproctitle(lua_State *L);

static int setproctitle(lua_State *L) {
    int n = lua_gettop(L);
    if (n != 1) {
        lua_pushstring(L, "Wrong number of arguments");
        lua_error(L);
    }
    if (!lua_isstring(L, 1)) {
        lua_pushstring(L, "incorrect argument type");
        lua_error(L);
    }
    const char *psreqname = luaL_checkstring(L, 1);
    int slen = strlen(psreqname);
    int len = 255;
    if ( slen < 255) {
        len = slen;
    }
    char *psname = calloc(256, sizeof(char));
    strncpy(psname, psreqname, len); 
    prctl(PR_SET_NAME, (char *) psname, 0, 0, 0);
    return 0;
}

static int getproctitle(lua_State *L) {
    int n = lua_gettop(L);
    if (n != 0) {
        lua_pushstring(L, "Wrong number of arguments");
        lua_error(L);
    }

    char *psname = calloc(256, sizeof(char));
    prctl(PR_GET_NAME, (char *) psname, 0, 0, 0);
    lua_pushstring(L, psname);
    free(psname);
    return 1;
}

static const struct luaL_Reg ck_fcs[] = {
    {"setproctitle", setproctitle},
    {"getproctitle", getproctitle},
    {NULL, NULL} /* sentinal */
};

LUALIB_API int luaopen_setproctitle(lua_State *L) {
    lua_newtable(L);
    luaL_register(L, NULL, ck_fcs);
    return 1;
}

