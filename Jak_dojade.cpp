#include <iostream>
#include <stdio.h>
#include "Graph.h"
#define SPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'
#define CITY_SYMBOL '*'
#define NOTHING '.'
#define ROAD '#'
#define BUFFER_SIZE 50
#define END_OF_TEXT '\0'
#define TRUE 1
#define FALSE 0
using namespace std;

enum direction {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE
};

void getMap(int height, int width, char** map);
int readCityName(char* cityName, int x, char* mapLine);
char* addCityName(int x, int y, char** map, int width, int height, Graph* mapGraph);
void readMap(int height, int width, char** map, Graph* mapGraph);

void getMap(int height, int width, char** map) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width;) {
			char input = getchar();
			if (input != SPACE && input != NEW_LINE && input != TAB) {
				map[y][x] = input;
				x++;
			}
		}
	}
}

int readCityName(char* cityName, int x, char* mapLine) {
	while (mapLine[x - 1] != NOTHING && mapLine[x -1] != ROAD) { //checks if previous character is '.'
		x -= 1;
	}
	int i = 0;
	int size = 0;
	while (mapLine[x] != NOTHING && mapLine[x] != ROAD) {
		cityName[i] = mapLine[x];
		size += 1;
		x += 1;
		i++;
	}
	return size;
}

char* addCityName(int x, int y, char** map, int width, int height, Graph* mapGraph) {
	char* input = new char[BUFFER_SIZE];
	int size = 0;
	if (y - 1 >= 0 && map[y - 1][x] != NOTHING && map[y - 1][x] != ROAD) {
		size = readCityName(input, x, map[y - 1]);
	}
	else if (y + 1 < height && map[y + 1][x] != NOTHING && map[y + 1][x] != ROAD) {
		size = readCityName(input, x, map[y + 1]);
	}
	else if (x + 1 < width && map[y][x + 1] != NOTHING && map[y][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y]);
	}
	else if (x - 1 >= 0 && map[y][x - 1] != NOTHING && map[y][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y]);
	}
	else if (x + 1 < width && y + 1 < height && map[y + 1][x + 1] != NOTHING && map[y + 1][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y + 1]);
	}
	else if (y + 1 < height && x - 1 >= 0 && map[y + 1][x - 1] != NOTHING && map[y + 1][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y + 1]);
	}
	else if (x - 1 >= 0 && y - 1 >= 0 && map[y - 1][x - 1] != NOTHING && map[y - 1][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y - 1]);
	}
	else if (x + 1 < width && y - 1 >= 0 && map[y - 1][x + 1] != NOTHING && map[y - 1][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y - 1]);
	}
	char* cityName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		cityName[i] = input[i];
	}
	cityName[size] = END_OF_TEXT;
	delete[] input;
	mapGraph->addNewCityName(cityName, x, y);
	return cityName;
}

int findCityNameLength(char* cityName) {
	int counter = 0;
	while (cityName[counter] != END_OF_TEXT) {
		counter += 1;
	}
	return counter;
}

void addRoad(Graph* mapGraph, char* cityName, int cityX, int cityY, int distance) {
	cityNameNode* destination = mapGraph->findCityByCoordinates(cityX, cityY);
	mapGraph->findCityByName(cityName)->addNewAdjacentCity(distance, destination->getCityName());
}

void checkRoads(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height);

bool checkCity(int x, int y, char** map, Graph* mapGraph, char* cityName, int width, int height, direction moveDirection) {
	int addedCities = 0;
	if (map[y][x] == CITY_SYMBOL) {
		addRoad(mapGraph, cityName, x, y, 0);
		addedCities += 1;
	}
	if (y - 1 >= 0 && map[y - 1][x] == CITY_SYMBOL && moveDirection != DOWN) {
		addRoad(mapGraph, cityName, x, y - 1, 0);
		addedCities += 1;
	}
	if (y + 1 < height && map[y + 1][x] == CITY_SYMBOL && moveDirection != UP) {
		addRoad(mapGraph, cityName, x, y + 1, 0);
		addedCities += 1;
	}
	if (x + 1 < width && map[y][x + 1] == CITY_SYMBOL && moveDirection != LEFT) {
		addRoad(mapGraph, cityName, x + 1, y, 0);
		addedCities += 1;
	}
	if (x - 1 >= 0 && map[y][x - 1] == CITY_SYMBOL && moveDirection != RIGHT) {
		addRoad(mapGraph, cityName, x - 1, y, 0);
		addedCities += 1;
	}
	if (addedCities > 0) {
		return true;
	}
	return false;
	
}

void readRoad(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height) {
	while (TRUE) {
		int roadsCounter = 0;
		if (y - 1 >= 0 && map[y - 1][x] == ROAD) {
			roadsCounter += 1;
		}
		if (y + 1 < height && map[y + 1][x] == ROAD) {
			roadsCounter += 1;
		}
		if (x - 1 >= 0 && map[y][x - 1] == ROAD) {
			roadsCounter += 1;
		}
		if (x + 1 < width && map[y][x + 1] == ROAD) {
			roadsCounter += 1;
		}
		if (roadsCounter > 2) {
			checkRoads(x, y, map, moveDirection, mapGraph, cityName, width, height);
			break;
		}
		if (moveDirection == UP && y - 1 >= 0 && (map[y - 1][x] == ROAD || map[y - 1][x] == CITY_SYMBOL)) {
			y -= 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection)) {
				break;
			}
		}
		else if (moveDirection == DOWN && y + 1 < height && (map[y + 1][x] == ROAD || map[y + 1][x] == CITY_SYMBOL)) {
			y += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection)) {
				break;
			}
		}
		else if (moveDirection == RIGHT && x + 1 < width && (map[y][x + 1] == ROAD || map[y][x + 1] == CITY_SYMBOL)) {
			x += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection)) {
				break;
			}
		}
		else if (moveDirection == LEFT && x - 1 >= 0 && (map[y][x - 1] == ROAD) || map[y][x - 1] == CITY_SYMBOL) {
			x -= 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection)) {
				break;
			}
		}
		else {
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection)) {
				break;
			}
			else {
				checkRoads(x, y, map, moveDirection, mapGraph, cityName, width, height);
				break;
			}
		}
	}
}

void checkRoads(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height) {
	int roadsCounter = 0;
	if (y - 1 >= 0 && map[y - 1][x] == ROAD) {
		roadsCounter += 1;
	}
	if (y + 1 < height && map[y + 1][x] == ROAD) {
		roadsCounter += 1;
	}
	if (x - 1 >= 0 && map[y][x - 1] == ROAD) {
		roadsCounter += 1;
	}
	if (x + 1 < width && map[y][x + 1] == ROAD) {
		roadsCounter += 1;
	}
	if (roadsCounter > 2 || moveDirection == NONE) {
		direction newMoveDirection;
		if (y - 1 >= 0 && map[y - 1][x] == ROAD && moveDirection != DOWN) {
			newMoveDirection = UP;
			readRoad(x, y - 1, map, newMoveDirection, mapGraph, cityName, width, height);
		}
		if (y + 1 < height && map[y + 1][x] == ROAD && moveDirection != UP) {
			newMoveDirection = DOWN;
			readRoad(x, y + 1, map, newMoveDirection, mapGraph, cityName, width, height);
		}
		if (x - 1 >= 0 && map[y][x - 1] == ROAD && moveDirection != RIGHT) {
			newMoveDirection = LEFT;
			readRoad(x - 1, y, map, newMoveDirection, mapGraph, cityName, width, height);
		}
		if (x + 1 < width && map[y][x + 1] == ROAD && moveDirection != LEFT) {
			newMoveDirection = RIGHT;
			readRoad(x + 1, y, map, newMoveDirection, mapGraph, cityName, width, height);
		}
	}
	else {//change of direction of the road 
		if (y - 1 >= 0 && map[y - 1][x] == ROAD && moveDirection != DOWN) {
			moveDirection = UP;
			readRoad(x, y - 1, map, moveDirection, mapGraph, cityName, width, height);
		}
		else if (y + 1 < height && map[y + 1][x] == ROAD && moveDirection != UP) {
			moveDirection = DOWN;
			readRoad(x, y + 1, map, moveDirection, mapGraph, cityName, width, height);
		}
		else if (x - 1 >= 0 && map[y][x - 1] == ROAD && moveDirection != RIGHT) {
			moveDirection = LEFT;
			readRoad(x - 1, y, map, moveDirection, mapGraph, cityName, width, height);
		}
		else if (x + 1 < width && map[y][x + 1] == ROAD && moveDirection != LEFT) {
			moveDirection = RIGHT;
			readRoad(x + 1, y, map, moveDirection, mapGraph, cityName, width, height);
		}
	}
}

void readMap(int height, int width, char** map, Graph* mapGraph) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				char* cityName = addCityName(x, y, map, width, height, mapGraph);
			}
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				char* cityName = mapGraph->findCityByCoordinates(x, y)->getCityName();
				checkRoads(x, y, map, NONE, mapGraph, cityName, width, height);
			}
		}
	}
}

int main() {
	int width, height;
	cin >> width;
	cin >> height;
	Graph* mapGraph = new Graph();
	char** map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	getMap(height, width, map);
	readMap(height, width, map, mapGraph);
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;
	return 0;
}