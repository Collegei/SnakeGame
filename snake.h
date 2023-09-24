#ifndef SNAKE
#define SNAKE
#include <iostream>
#include <deque>
#include <list>
#include "config.h"

class Position{
	public:
		//initial
		Position(int x,int y):X(x),Y(y){}
		//set 
		void SetPosition(int x,int y){
			X = x;
			Y = y;
		}
		//get
		int GetPosition(char coordinate) const{
			if (coordinate == 'x'){
				return X;
			}
			else if (coordinate == 'y'){
				return Y;
			}
			else{
				std::cout<<"invalid argument for GetPosition()"<<std::endl;
				exit(1);
			}
		}
		bool operator==(const Position& other) const{
			return X == other.GetPosition('x') && Y == other.GetPosition('y');
		}
	private:
		int X;
		int Y;
};

class Body{
	public:
		Body(int X,int Y):length(1),direction('w')
		{
			snake_body.push_front(Position(X,Y));
		}
		//get 
		int GetHeadPosition(char coordinate){
			if (coordinate == 'x' || coordinate == 'y'){
				return snake_body.front().GetPosition(coordinate);
			}
			std::cout<<"invalid argument for GetHeadPosition()"<<std::endl;
			exit(1);
		}
		int GetTailPosition(char coordinate){	
			if (coordinate == 'x' || coordinate == 'y'){
				return snake_body.back().GetPosition(coordinate);
			}
			std::cout<<"invalid argument for GetTailPosition()"<<std::endl;	
			exit(1);
		}
		int GetLength(void){return length;}
		//other
		bool MoveHead(char control); //move and return valid or not (update length)
		void MoveTail(void);
	protected:
		std::deque<Position> snake_body;		
		int length;
		char direction;

};

class Food{
	public:
		Food(int snake_X,int snake_Y);
		//get
		int GetFoodPosition(char coordinate){
			if (coordinate == 'x' || coordinate == 'y'){
				return food.GetPosition(coordinate);
			}
			std::cout<<"invalid argument for GetFoodPosition()"<<std::endl;
			exit(1);
		}
		//add and remove valid region
		void AddValid(int X,int Y);
		void RemoveValid(int X,int Y);
		//generate
		int RandomInt(int leftbound,int rightbound);
		void GenerateFood(void);	
	protected:
		Position food;
		std::list<Position> valid_region[Long];
};

class Snake : public Body, public Food
{
	public:
		Snake();
		void print(void);
		bool logic(char control);
	private:
		bool Screen[Long][Width];	
};

#endif
