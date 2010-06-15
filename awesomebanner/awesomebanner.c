/*
 * Copyright (c) 2010, Joshua M. Clulow. All rights reserved.
 *
 * This file is distributable under the BSD license.
 *    (see ../BSD_LICENSE)
 */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <curses.h>
#include <string.h>

#include "bannerfont.h"

WINDOW *g_screen;
int g_requireinit = 0;

void die(int rc, char* msg) {
	clear();
	refresh();
	endwin();
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	exit(rc);
}

void setupcurses() {
	g_screen = initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_GREEN);
	noecho();
	cbreak();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);
}

void printletter(char letter, int x, int y, int cp_on, int cp_off) {
	int i, j;
	for (i = 0; i < nlines; i++) {
		char xx = ctbl[letter][i];
		move(i + y, x);
		for (j = 0; j < pospch; j++) {
			if (((xx << j) & 0100) != 0) {
				attron(COLOR_PAIR(cp_on));
				addch(' ');
			} else {
				attron(COLOR_PAIR(cp_off));
				addch(' ');
			}
		}
	}
}

void printstring(char *str, int x, int y, int cp_on, int cp_off) {
	int q, l;
	l = strlen(str);
	for (q = 0; q < l; q++) {
		printletter(str[q], x + q * pospch, y, cp_on, cp_off);
	}
}

int pstrwidth(char *str) {
	return strlen(str) * pospch;
}

void setupscreen() {
	bkgd(COLOR_PAIR(1));
	clear();
	// poke the display so that it doesn't assume black bg...
	attron(COLOR_PAIR(4));
	move(0, 0);
	addch(' ');
	// reset to 'normal'
	attron(COLOR_PAIR(1));
	refresh();
}

void sigrsz(int sig) {
	// post request to reinit curses
	g_requireinit = 1;
}

void hsig(int sig) {
	char outstr[100];
	snprintf(outstr, 100, "awesomebanner: Terminating on signal.\n");
	die(15, outstr);
}

void setupsignals() {
	struct sigaction sa;

	sa.sa_handler = hsig;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigrsz;
	sigaction(SIGWINCH, &sa, NULL);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s \"<banner string>\"\n", argv[0]);
		exit(1);
	}
	setupsignals();
	setupcurses();
	setupscreen();

	for (;;) {
		int x, y;
		
		if (g_requireinit) {
			endwin();
			setupcurses();
			setupscreen();
			g_requireinit = 0;
		}
	
		x = rand() % (COLS - pstrwidth(argv[1]));
		y = rand() % (LINES - nlines);

		clear();
		printstring(argv[1], x, y, 3, 1);
		refresh();
		
		sleep(1);
	}
}


