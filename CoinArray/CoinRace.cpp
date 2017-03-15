#pragma once
#include <conio.h>
#include <iostream>



class Map {
public:
	char **map;
	int row_dyn;
	int col_dyn;
	void modificadorCelda(char map[][columna], int fila, int columna)const;
};




namespace Input{
	enum class Key{
		NONE, W, A, S, D, ENTER, ESC
	};
		static Key getKey(){
		if (_kbhit()){
			switch (_getch()){
			case 87: case 119:
				return Key::W; // w and W
			case 65: case 97:
				return Key::A; // a and A
			case 83: case 115:
				return Key::S; // s and S
			case 68: case 100:
				return Key::D; // d and D
			case 13:
				return Key::ENTER; // carriage return
			case 27:
				return Key::ESC; // escape
			}
		}
		return Key::NONE;
	}
};