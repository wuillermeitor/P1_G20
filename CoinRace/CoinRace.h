#pragma once
#include <iostream>
#include "Input.h"

struct coordenadas {//struct en el que declaramos las coordenadas del mapa.
	int x, y;
};

enum class symbols :char {//enum en el que creamos los s�mbolos que se usar�n en el juego.
	EMPTY = '.',
	PLAYER = '@',
	COIN = '$'
};

enum class dificultad : int {//enum con el que crearemos la dificultad.
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
};

class Map {
	//con los "friend class" permitimos a otras clases acceder a los atributos y m�todos del mapa.
	friend class Player;
	friend class CoinManager;
public:
	void inicio(const dificultad & difficulty);//m�todo que crea el mapa.
	symbols posicion(const coordenadas & location);
	void modificar(const coordenadas & target, const symbols & value);//m�todo que modifica una posici�n del mapa.
	void dibujar();//m�todo que dibuja el mapa en la consola.
	~Map();//destructor del Map.
private:
	coordenadas dimensiones;
	symbols**infoMap;
};

class Player {
public:
	void inicio(Map * pCurrentMap);//m�todo que le da una posici�n inicial al jugador.
	bool movimiento(const Input::Key & key);//m�todo que permite al jugador moverse.
	coordenadas conseguirPosicion();
	int score;
private:
	coordenadas posicion;
	Map * CurrentMap;
};

class CoinManager {
	//Cantidad de monedas visibles en el mapa
public:
	void AddCoin(Map * pCurrentMap);//m�todo que a�ade la cantidad de monedas del mapa.
	int ActualCoin;
private:
	const int min = 3, max = 13;
	coordenadas*CoinData;
	bool comprobarPosicion(const coordenadas & at, int last);//m�todo que comprueba si en una posici�n ya hay una moneda.
	Map * CurrentMap;
};