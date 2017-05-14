#include "coinRace.h"
#include "Input.h"
#include <time.h>

//declaración de variables.
bool shouldGameContinue;
int cointarget;
dificultad difficulty;
Map map;
CoinManager coinManager;
Player player;

int main() {
	//inicializamos una variable para el correcto funcionamiento del juego.

	srand(time(nullptr));
	//bucle en el que funciona el juego.
	system("cls");
	std::cout << "/////////////////////////////////////////" << std::endl;
	std::cout << "                COIN RACE                " << std::endl;
	std::cout << "/////////////////////////////////////////" << std::endl << std::endl;
	std::cout << "Controls: Use WASD to move the player" << std::endl;
	std::cout << "if you want to exit, press ESC" << std::endl << std::endl;
	std::cout << "Choose a difficulty:" << std::endl
		<< "1 - EASY" << std::endl
		<< "2 - MEDIUM" << std::endl
		<< "3 - HARD" << std::endl;
	int input = 0;
	while (input != 1 && input != 2 && input != 3) {
		std::cin.clear();
		std::cin >> input;
	}
	//Un cast para cambiar la dificultad de enum a integer.
	difficulty = static_cast<dificultad>(input);
	//cálculo del número objetivo de monedas a recolectar.
	cointarget = 30 * static_cast<int>(difficulty) + rand() % (30 * static_cast<int>(difficulty));

	map.inicio(difficulty);
	player.inicio(&map);
	coinManager.AddCoin(&map);

	Input::Key key{ Input::Key::ENTER };

	shouldGameContinue = true;

	clock_t start_time = clock();

	//El juego seguirá en curso mientras el booleano sea true y el jugador no haya conseguido todas las monedas.
	while (shouldGameContinue == true && player.score != cointarget) {
		if (Input::Key::NONE != key && Input::Key::ESC != key) {
			//Comprobamos si el movimiento del player devuelve true, lo cual significa que ha cogido una moneda y por lo tanto
			//su score ha aumentado. Si es true, disminuimos la cantidad de monedas actuales en el mapa, y si llega a 0, volvemos 
			//a añadir monedas en el mapa.
			if (player.movimiento(key) == true) {
				coinManager.ActualCoin--;
				if (coinManager.ActualCoin <= 0) {
					coinManager.AddCoin(&map);
				}
			}
			system("cls");
			map.dibujar();//esto dibuja el mapa después de cada movimiento del jugador.
			std::cout << "Score: " << player.score << "/" << cointarget << std::endl;
		}
		else if (key == Input::Key::ESC) {
			shouldGameContinue = false;
		}
		key = Input::getKey();
	}
		system("cls");
		//Finalmente, cuando el jugador haya recolectado todas las monedas, se le mostrará el
		//tiempo que ha tardado en conseguirlo.
		if (player.score == cointarget) {
			clock_t end_time = clock();
			std::cout << std::endl << "You've picked up ";
			std::cout << cointarget;
			std::cout << " coins in ";
			std::cout << (end_time - start_time) / 1000;
			std::cout << " seconds" << std::endl;
			_getch();
		}
		//Con esto, le permite al jugador observar detenidamente el tiempo que ha tardado 
		//en recolectar las monedas antes de que se cierre el juego.
		std::cout << "Press ESC to exit";
		Input::Key finalkey = Input::Key::NONE;
		while (finalkey == Input::Key::NONE) {
			switch (Input::getKey()) {
			case Input::Key::ESC:
				return 0;
			}
		}
	return 0;
}