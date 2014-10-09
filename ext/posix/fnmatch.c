/***
@module posix.fnmatch
*/
/*
 * POSIX library for Lua 5.1/5.2.
 * (c) Gary V. Vaughan <gary@vaughan.pe>, 2013-2014
 * (c) Reuben Thomas <rrt@sc3d.org> 2010-2013
 * (c) Natanael Copa <natanael.copa@gmail.com> 2008-2010
 * Clean up and bug fixes by Leo Razoumov <slonik.az@gmail.com> 2006-10-11
 * Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br> 07 Apr 2006 23:17:49
 * Based on original by Claudio Terra for Lua 3.x.
 * With contributions by Roberto Ierusalimschy.
 * With documentation from Steve Donovan 2012
 */

#include <config.h>

#include <fnmatch.h>

#include "_helpers.c"


/***
Match a filename against a shell pattern.
@function fnmatch
@string pat shell pattern
@string name filename
@int[opt=0] flags optional
@return true or false
@raise error if fnmatch failed
@see fnmatch(3)
*/
static int
Pfnmatch(lua_State *L)
{
	const char *pattern = luaL_checkstring(L, 1);
	const char *string = luaL_checkstring(L, 2);
	int flags = optint(L, 3, 0);
	int res;
	checknargs(L, 3);
	res = fnmatch(pattern, string, flags);
	if (res == 0)
		lua_pushboolean(L, 1);
	else if (res == FNM_NOMATCH)
		lua_pushboolean(L, 0);
	else
	{
		lua_pushstring(L, "fnmatch failed");
		lua_error(L);
	}
	return 1;
}


static const luaL_Reg posix_fnmatch_fns[] =
{
	LPOSIX_FUNC( Pfnmatch		),
	{NULL, NULL}
};


LUALIB_API int
luaopen_posix_fnmatch(lua_State *L)
{
	luaL_register(L, "posix.fnmatch", posix_fnmatch_fns);
	lua_pushliteral(L, "posix.fnmatch for " LUA_VERSION " / " PACKAGE_STRING);
	lua_setfield(L, -2, "version");

	/* from fnmatch.h */
	LPOSIX_CONST( FNM_PATHNAME	);
	LPOSIX_CONST( FNM_NOESCAPE	);
	LPOSIX_CONST( FNM_PERIOD	);

	return 1;
}