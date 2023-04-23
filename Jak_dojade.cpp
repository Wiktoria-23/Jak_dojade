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
using namespace std;

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

void addCityName(int x, int y, char** map, int width, int height, Graph* mapGraph) {
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
	mapGraph->addNewCityName(cityName, size);
}

void readRoad(Graph* mapGraph, char** map, int x, int y) {
	if (map[y - 1][x] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y + 1][x] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y][x - 1] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y][x + 1] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}//rekurencyjne dodawanie drogi (rozwidlenia)(?)
}

void checkRoads(int x, int y, char** map, int width, int height, Graph* mapGraph) {
	if (map[y - 1][x] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y + 1][x] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y][x - 1] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
	else if (map[y][x + 1] == ROAD) {
		readRoad(mapGraph, map, x, y);
	}
}

void readMap(int height, int width, char** map, Graph* mapGraph) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				addCityName(x, y, map, width, height, mapGraph);
				checkRoads(x, y, map, width, height, mapGraph);
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