#pragma once
#include <iostream>
#include "Input.h"

struct coordenadas {//struct en el que declaramos las coordenadas del mapa.
	int x, y;
};

enum class symbols :char {//enum en el que creamos los símbolos que se usarán en el juego.
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
	//con los "friend class" permitimos a otras clases acceder a los atributos y métodos del mapa.
	friend class Player;
	friend class CoinManager;
public:
	void inicio(const dificultad & difficulty);//método que crea el mapa.
	symbols posicion(const coordenadas & location);
	void modificar(const coordenadas & target, const symbols & value);//método que modifica una posición del mapa.
	void dibujar();//método que dibuja el mapa en la consola.
	~Map();//destructor del Map.
private:
	coordenadas dimensiones;
	symbols**infoMap;
};

class Player {
public:
	void inicio(Map * pCurrentMap);//método que le da una posición inicial al jugador.
	void movimiento(const Input::Key & key);//método que permite al jugador moverse.
	coordenadas conseguirPosicion();
	int score;
private:
	coordenadas posicion;
	Map * CurrentMap;
};

class CoinManager {
public:
	void inicio(Map * pCurrentMap);//método que inicia la cantidad de monedas del mapa.
	int ActualCoin;
private:
	const int	min = 3, max = 13;
	coordenadas*CoinData;
	bool comprobarPosicion(const coordenadas & at, int last);//método que comprueba si en una posición ya hay una moneda.
	Map * CurrentMap;
};