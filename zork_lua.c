/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */
#include<stdio.h>
#define EXTERN
#define INIT
#include "funcs.h"
#include "vars.h"
#define PRSTAT	\
	printf("lives = %d moves = %d score = %d\n",2-state_.deaths, state_.moves, state_.rwscor);

#include "lua.h"
#include "lauxlib.h"

 void stringToUpper(char *str) {
	while (*str != '\0') {
		if(islower((int)*str))
			*str = toupper((int)*str);
		++str;
	}
}

static int fd;
static fpos_t pos;

static void switchStdout(const char *newStream)
{
  fflush(stdout);
  fgetpos(stdout, &pos);
  fd = dup(fileno(stdout));
  if( freopen(newStream, "w", stdout)==NULL)
  	exit_();
}

static void revertStdout()
{
  fflush(stdout);
  dup2(fd, fileno(stdout));
  close(fd);
  clearerr(stdout);
  fsetpos(stdout, &pos);
}

int zorkInit(lua_State *L) {
	switchStdout("game_message.txt");
	init_();
	revertStdout();
	lua_pushstring(L, "game_message.txt"); //return output file name
	return 1;
}

int zorkGameStep(lua_State *L) {
	char* command = lua_tostring(L, 1);
	stringToUpper(command); //assume null terminated string from lua state
	switchStdout("game_message.txt");
	game_step(command);
	revertStdout();
	lua_pushstring(L, "game_message.txt");
	return 1;
}

int zorkInventory(lua_State *L) {
		switchStdout("inventory_message.txt");
		game_step("INVENTORY\0");
		--state_.moves; // reduce step penalty
		revertStdout();
		lua_pushstring(L, "inventory_message.txt"); //return output file name
		return 1;
	}

int zorkGetScore(lua_State *L) {
	lua_pushinteger(L, state_.rwscor);
	return 1;
}

int zorkGetNumMoves(lua_State *L) {
	lua_pushinteger(L, state_.moves);
	return 1;
}

int zorkGetLives(lua_State *L) {
	lua_pushinteger(L, 2 - state_.deaths);
	return 1;
}

int zorkExit(lua_State *L) {
	exit_();
	return 0;
}

int luaopen_zork(lua_State *L) {
	char str[]={"hi from c\n"};
	printf("%s",str);

	luaL_Reg fns[] = {
			{"zorkInit",zorkInit},
			{"zorkGameStep",zorkGameStep},
			{"zorkGetScore",zorkGetScore},
			{"zorkGetLives",zorkGetLives},
			{"zorkGetNumMoves",zorkGetNumMoves},
			{"zorkInventory",zorkInventory},
			{"zorkExit",zorkExit},
			{NULL,NULL}
	};
	luaL_newlib(L, fns);
	return 1;
}
