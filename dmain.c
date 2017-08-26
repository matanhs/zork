/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */
#ifndef LUA

#include<stdio.h>
#include<assert.h>

#define EXTERN
#define INIT

#include "funcs.h"
#include "vars.h"
#define PRSTAT	\
	printf("lives = %d moves = %d score = %d\n",2-state_.deaths, state_.moves, state_.rwscor);


int main(int argc,char **argv) {
int i;
/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */
	// all output is redirected to the file
	if (init_()) {
		for (i=0;i<100000;i++){
			game_step("OPEN MAILBOX");
		    	game_step("N");
		    	game_step("N");
		    	game_step("CLIMB THE TREE");
		    	game_step("TAKE EGG");
		    	PRSTAT
			printf("loop: %d\n",i);
			init_();
		}
	}
/* 						!IF INIT, PLAY GAME. */
    exit_();
/* 						!DONE */
} /* MAIN__ */
#endif
