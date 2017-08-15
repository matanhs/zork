/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */
#include<stdio.h>
#include<assert.h>
#define EXTERN
#define INIT

#include "funcs.h"
#include "vars.h"
#define PRSTAT	\
	printf("lives = %d moves = %d score = %d\n",2-state_.deaths, state_.moves, state_.rwscor);


int main(int argc,char **argv) {
/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */
	char string[BUFSIZ];

	FILE* out = freopen("game_output.txt", "w", stdout);
	if (out==NULL) exit_();

	setbuf(stdout, string);
	// all output is redirected to the file
	if (init_()) {
    	game_step("OPEN MAILBOX\0");
    	game_step("READ LEAFLET\0");
    	game_step("N\0");
    	game_step("N\0");
    	game_step("CLIMB THE TREE\0");
    	game_step("TAKE EGG\0");
    	PRSTAT
	init_();
    	PRSTAT
    fclose(out);
	}
/* 						!IF INIT, PLAY GAME. */
    exit_();
/* 						!DONE */
} /* MAIN__ */
