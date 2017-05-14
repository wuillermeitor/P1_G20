#include "CoinRace.h"
#include <cstdlib>
#include <iostream>
#include <ctime>


void Map::inicio(const dificultad & difficulty) {
	dimensiones = { static_cast<int>(difficulty)*(5 + rand() % 5),
		static_cast<int>(difficulty)*(5 + rand() % 5) };

	infoMap = new symbols*[dimensiones.y];
	for (int i = 0; i < dimensiones.y; i++) {
		infoMap[i] = new symbols[dimensiones.x];
		for (int j = 0; j < dimensiones.x; j++) {
			infoMap[i][j] = symbols::EMPTY;
		}
	}
}

symbols Map::posicion(const coordenadas & location) {
	return infoMap[location.y][location.x];
}

void Map::modificar(const coordenadas & target, const symbols & value) {
	infoMap[target.y][target.x] = value;
}

void Map::dibujar() {

	for (int i = 0; i < dimensiones.y; i++) {
		for (int j = 0; j < dimensiones.x; j++) {
			std::cout << static_cast<char>(infoMap[i][j]);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

Map::~Map() {
	for (int i = 0; i < dimensiones.y; i++) {
		delete[] this->infoMap[i];
	}
	delete[] this->infoMap;
}

void Player::inicio(Map * pCurrentMap) {
	score = 0;
	CurrentMap = pCurrentMap;
	do {
		posicion = {
			rand() % (CurrentMap->dimensiones.x),
			rand() % (CurrentMap->dimensiones.y)
		};
	} while (CurrentMap->posicion(posicion) == symbols::COIN);

	CurrentMap->modificar(posicion, symbols::PLAYER);
}

bool Player::movimiento(const Input::Key & key) {
	CurrentMap->modificar(posicion, symbols::EMPTY);
	if (key != Input::Key::NONE) {
		switch (key) {
		case Input::Key::W:
			if (posicion.y != 0) {
				posicion.y--;
			}
			break;
		case Input::Key::A:
			if (posicion.x != 0) {
				posicion.x--;
			}
			break;
		case Input::Key::S:
			if (posicion.y + 1 < CurrentMap->dimensiones.y) {
				posicion.y++;
			}
			break;
		case Input::Key::D:
			if (posicion.x + 1 < CurrentMap->dimensiones.x) {
				posicion.x++;
			}
			break;
		default:
			break;
		}
	}
	bool temp{ false };
	if ((CurrentMap->posicion(posicion)) == symbols::COIN) {
		score++;
		temp = true;
	}
	CurrentMap->modificar(posicion, symbols::PLAYER);
	return temp;
}

coordenadas Player::conseguirPosicion() {
	return posicion;
}

bool operator==(const coordenadas & lhs, const coordenadas & rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

void CoinManager::AddCoin(Map * pCurrentMap) {
	CurrentMap = pCurrentMap;
	ActualCoin = CurrentMap->dimensiones.x * CurrentMap->dimensiones.y * 0.01 * (min + rand() % max);

	CoinData = new coordenadas[ActualCoin];
	for (int i = 0; i < ActualCoin; i++) {
		do {
			CoinData[i] = { rand() % CurrentMap->dimensiones.x,
				rand() % CurrentMap->dimensiones.y };
		} while (!comprobarPosicion(CoinData[i], i) || CurrentMap->posicion(CoinData[i]) == symbols::PLAYER);
		CurrentMap->modificar(CoinData[i], symbols::COIN);
	}
}

bool CoinManager::comprobarPosicion(const coordenadas & at, int last) {
	for (int i= 0; i < last; i++) {
		if (at == CoinData[i]) { 
			return false; 
		}
	}
	return true;
}