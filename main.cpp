//create a C++ snake games, and it must run on other IDE
#include <iostream>
#include <chrono>
#include <ncurses.h>
#include "snake.h"
#include "input.h"

inline void waituntil(std::chrono::system_clock::time_point& start,int elapse_time){
	std::chrono::milliseconds ELAPSE_TIME(elapse_time);

	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
	while (current - start < ELAPSE_TIME){
		current = std::chrono::system_clock::now();
	}
}

int main(){
	//initialize ncurses.h
	initscr();

	cbreak();
	noecho();
	//nodelay
	nodelay(stdscr,true);

	//game start
	char control = '\0';
	Snake snake;
	while (true){
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		bool loss = snake.logic(control);
		if (loss){
			help('l');	
			break;
		}
		if (snake.GetLength() == ScreenSize){
			help('s');
			break;
		}
		snake.print();
	
		waituntil(start,170);	
		control = input();
		if (control == 'q'){
			help('q');
			break;
		}
	}
	//end game	
	endwin();	
	return 0;	
}

