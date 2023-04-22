#include <iostream>
#include <stdio.h>
#define SPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'
#define CITY_SYMBOL '*'
#define NOTHING '.'
#define BUFFER_SIZE 50
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
	while (mapLine[x - 1] != NOTHING) { //checks if previous character is '.'
		x -= 1;
	}
	int i = 0;
	int size = 0;
	while (mapLine[x] != NOTHING) {
		cityName[i] = mapLine[x];
		size += 1;
		x += 1;
	}
	return size;
}

char* findCityName(int x, int y, char** map) {
	char* cityName = new char[BUFFER_SIZE];
	int size;
	if (map[y - 1][x] != NOTHING) {
		size = readCityName(cityName, x, map[y - 1]);
	}
	else if (map[y + 1][x] != NOTHING) {
		size = readCityName(cityName, x, map[y + 1]);
	}
	else if (map[y][x + 1] != NOTHING) {
		size = readCityName(cityName, x + 1, map[y]);
	}
	else if (map[y][x - 1] != NOTHING) {
		size = readCityName(cityName, x - 1, map[y]);
	}
	else if (map[y + 1][x + 1] != NOTHING) {
		size = readCityName(cityName, x + 1, map[y + 1]);
	}
	else if (map[y + 1][x - 1] != NOTHING) {
		size = readCityName(cityName, x - 1, map[y + 1]);
	}
	else if (map[y - 1][x - 1] != NOTHING) {
		size = readCityName(cityName, x - 1, map[y - 1]);
	}
	else if (map[y - 1][x + 1] != NOTHING) {
		size = readCityName(cityName, x + 1, map[y - 1]);
	}

}

void readMap(int height, int width, char** map) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				char* cityName = findCityName(x, y, map);
			}
		}
	}
}

int main() {//dodac wczytywanie calej tablicy do programu, nastepnie dodac zczytywanie nazw miast, pozniej polaczen
	int width, height;
	cin >> width;
	cin >> height;
	char** map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	getMap(height, width, map);
	readMap(height, width, map);
	return 0;
}