#include <iostream>
#include <ncurses.h>
#include "snake.h"
#include <random>

bool Body::MoveHead(char control){
	int new_x;
	int new_y;
	char new_direction = (control != '\0' ? control : direction);
	switch (new_direction){
		case 'w' :
			new_x = GetHeadPosition('x') - 1;
			new_y = GetHeadPosition('y');
			break;
		case 'a' :
			new_x = GetHeadPosition('x');
			new_y = GetHeadPosition('y') - 1;
			break;
		case 's' :
			new_x = GetHeadPosition('x') + 1;
			new_y = GetHeadPosition('y');
			break;
		case 'd' :
			new_x = GetHeadPosition('x');
			new_y = GetHeadPosition('y') + 1;
			break;
		default:
			std::cout<<"Error control appears in MoveHead()"<<std::endl;
			exit(1);
			break;
	}
	snake_body.push_front(Position(new_x,new_y));
	direction = new_direction;
	++length;
	return (new_x > -1 && new_x < Long && new_y > -1 && new_y < Width);
}
void Body::MoveTail(void){
	snake_body.pop_back();
	--length;
}
Food::Food(int snake_X,int snake_Y) : food(0,0)
{
	//initialize valid region
	for (int i=0;i<Long;i++){
		for (int j=0;j<Width;j++){
			if (!(i==snake_X && j==snake_Y)){
				valid_region[i].push_back(Position(i,j));
			}
		}
	}
	//Generate food Position
	GenerateFood();	
}
void Food::AddValid(int X,int Y){
	valid_region[X].push_back(Position(X,Y));	
}
void Food::RemoveValid(int X,int Y){
	std::list<Position>::iterator it = valid_region[X].begin();
	while (it != valid_region[X].end() && it->GetPosition('y') != Y){
		++it;
	}
	if (it != valid_region[X].end()){
		valid_region[X].erase(it);
	}
}
void Food::GenerateFood(void){
	int X = RandomInt(0,Long-1);
	int Y = RandomInt(0,Width-1);
	int pace = 0;
	int row = 0;
	while (pace < X){
		if (valid_region[row].size() != 0 ){
			++pace;
		}
		++row;
		if (row >= Long){
			row %= Long;
		}
	}
	int column = Y % valid_region[row].size();
	//find generate position
	std::list<Position>::iterator it;
	int index;
	for (it = valid_region[row].begin(),index=0; it != valid_region[row].end() && index < column; ++it,++index){
		;
	}	
	if (it == valid_region[row].end()){
		std::cout<<"error int GenerateFood()"<<std::endl;
		exit(1);
	}
	//set food position
	food.SetPosition(it->GetPosition('x'),it->GetPosition('y')); 
}
int Food::RandomInt(int leftbound,int rightbound){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(leftbound,rightbound);
	return distribution(gen);
}

Snake::Snake(): Body((Long-1)/2,(Width-1)/2),Food((Long-1)/2,(Width-1)/2)
{	
	//screen
	for (int i=0;i<Long;i++){
		for (int j=0;j<Width;j++){
			Screen[i][j] = 0;
		}
	}	
	Screen[(Long-1)/2][(Width-1)/2] = 1;	
}
bool Snake::logic(char control){
	//update snake
	bool outside = !MoveHead(control);	
	if (outside){
		return true;//loss
	}
	//test eat and update snake
	if (GetFoodPosition('x') == GetHeadPosition('x') && GetFoodPosition('y') == GetHeadPosition('y')){
		RemoveValid(GetHeadPosition('x'),GetHeadPosition('y'));
		GenerateFood();		
	}
	else{
		Screen[GetTailPosition('x')][GetTailPosition('y')] = 0;
		RemoveValid(GetHeadPosition('x'),GetHeadPosition('y'));
		AddValid(GetTailPosition('x'),GetTailPosition('y'));
		MoveTail();
	}
	if (Screen[GetHeadPosition('x')][GetHeadPosition('y')] == 1){
		return true;//loss	
	}
	Screen[GetHeadPosition('x')][GetHeadPosition('y')] = 1;
	return false; //continue

		
}
void Snake::print(void){
	clear();
	for (int j=0;j<Width+2;j++){
		printw("#");
	}
	printw("\n");
	for (int i=0;i<Long;i++){
		printw("#");
		for (int j=0;j<Width;j++){
			if (i == GetFoodPosition('x') && j == GetFoodPosition('y')){
				printw("$");
			}
			else if (Screen[i][j]){
				printw("*");
			}
			else{
				printw(" ");
			}
		}
		printw("#\n");
	}
	for (int j=0;j<Width+2;j++){
		printw("#");
	}
	printw("\nsnake length: %d",GetLength());
	refresh();
}

