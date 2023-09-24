#include <iostream>
#include <string>
#include <chrono>
#include <ncurses.h>
#include "input.h"

const std::chrono::milliseconds ELAPSE_TIME(10);

char input(void){
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	//process input (all input in terminal must be in buffer)
	char control;
	char ch;	
	if ((ch = getch()) != ERR){
		#ifdef DEBUG
		printw("get:%c\n",ch);
		#endif	
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'q'){
			control=ch;
		}
		else{
			control='\0';
		}
	}
	else{
		#ifdef DEBUG
		printw("doesn't get:\n");
		#endif
		control = '\0';
	}
	//clean buffer
	flushinp();

	//wait unitil certaint time
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
	while (current - start < ELAPSE_TIME){
		current = std::chrono::system_clock::now();
	}
	#ifdef DEBUG
	printw("flushed buffer.\n");
	refresh();
	#endif

	return control;	
}
void help(char mode){
	char ch='\0';
	while (ch != 'Y' && ch !='y'){
		clear();
		if (mode == 'q'){
			printw("You quit the game.\nPress Y/y to continue\n");
		}
		else if (mode == 'l'){
			printw("You loss the game.\nPress Y/y to continue\n");
		}
		else if (mode == 's'){
			printw("You win the game.\nPress Y/y to continue\n");
		}
		else{
			printw("Wrong mode.\nPress Y/y to continue\n");
		}	
		refresh();
		std::cin >> ch;
	}
}
