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

int main(int argc, char **argv) {
	/* 1) INITIALIZE DATA STRUCTURES */
	/* 2) PLAY GAME */
	int i,bad_parse;
	char buff[1024];
	if (init_()) {
		for (i = 0; i < 10000; i++) {
			/*
			 *
			 game_step("OPEN MAILBOX\0");
			game_step("N\0");
			game_step("N\0");
			game_step("CLIMB THE TREE\0");
			game_step("TAKE EGG\0");
			PRSTAT
			init_();
			printf("inits = %d\n",i);
			*/
			rdline_(buff,1);
			//printf ("%d\n",parse_(buff,1));
			bad_parse = game_step(buff);
			printf("bad parse command? %d\naction index: %d\nobject index: %d\ninstrument index %d\n",bad_parse, prsvec_.prsa,prsvec_.prso,prsvec_.prsi);
		}

	}
	/* 						!IF INIT, PLAY GAME. */
	exit_();
	/* 						!DONE */
} /* MAIN__ */
#endif
