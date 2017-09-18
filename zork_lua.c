#ifdef LUA
#define EXTERN
#define INIT
#include<stdio.h>
#include "funcs.h"
#include "vars.h"
#define PRSTAT	\
	printf("lives = %d moves = %d score = %d\n",2-state_.deaths, state_.moves, state_.rwscor);
#define BUFF_SIZE 78
#ifdef LUAJIT // lua  5.1
#include "lua.h"
#include "lauxlib.h"
#else
#include "lua-5.3/lua.h"
#include "lua-5.3/lauxlib.h"
#endif // lua5.1

void stringToUpper(char *str,char *dest) {
	int i = 0;
	while (str[i] != '\0' && i < BUFF_SIZE) {
		if(islower((int)str[i]))
			dest[i] = toupper((int)str[i]);
		else
			dest[i] = str[i];
		++i;
	}
	dest[i] = '\0';
}

static int fd;
static fpos_t pos;

static void switchStdout(const char *newStream)
{
	fflush(stdout);
	fgetpos(stdout, &pos);
	fd = dup(fileno(stdout));
	if(freopen(newStream, "w", stdout) == NULL){
		printf(stderr,"error opening stream %s\n",newStream);
		exit(0);
	}
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
	char* command = (char*) lua_tostring(L, 1);
	char buff[78];
	stringToUpper(command,buff); //assume null terminated string from lua state
	switchStdout("game_message.txt");
	int bad_command = game_step(buff);
	revertStdout();
	lua_pushstring(L, "game_message.txt");
	lua_pushnumber(L,bad_command);
	return 2;
}

int zorkInventory(lua_State *L) {
	switchStdout("inventory_message.txt");
	game_step("INVENTORY\0");
	--state_.moves; // reduce step penalty
	revertStdout();
	lua_pushstring(L, "inventory_message.txt");//return output file name
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
	char str[]= {"zork c init SUCCESSFUL\n"};
	printf("%s",str);
	luaL_Reg fns[] = {
		{	"zorkInit",zorkInit},
		{	"zorkGameStep",zorkGameStep},
		{	"zorkGetScore",zorkGetScore},
		{	"zorkGetLives",zorkGetLives},
		{	"zorkGetNumMoves",zorkGetNumMoves},
		{	"zorkInventory",zorkInventory},
		{	"zorkExit",zorkExit},
		{	NULL,NULL}
	};
#ifdef LUAJIT // lua  5.1
	luaL_register(L,"zork", fns);
#else // lua 5.3
	luaL_newlib(L, fns);
#endif
	return 1;
}

#endif
