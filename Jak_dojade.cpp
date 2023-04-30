#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#include "adjacentCityNode.h"
#include "PriorityQueue.h"
#include "Operation_on_text.h"
#define BUFFER_SIZE 50
#define TRUE 1
#define FALSE 0
#define SHOW_ROAD 1
using namespace std;

//struct nextCity {
//	nextCity* adjacentCity;
//	char* name;
//};

struct shortestRoadToCity {
	char* cityName;
	int distance;
	shortestRoadToCity* next;
};

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

void checkRoads(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height, int lengthCounter);

bool checkCity(int x, int y, char** map, Graph* mapGraph, char* cityName, int width, int height, direction moveDirection, int lengthCounter) {
	int addedCities = 0;
	if (map[y][x] == CITY_SYMBOL) {
		lengthCounter += 1;
		addRoad(mapGraph, cityName, x, y, lengthCounter);
		addedCities += 1;
	}
	if (y - 1 >= 0 && map[y - 1][x] == CITY_SYMBOL && moveDirection != DOWN) {
		lengthCounter += 1;
		addRoad(mapGraph, cityName, x, y - 1, lengthCounter);
		addedCities += 1;
	}
	if (y + 1 < height && map[y + 1][x] == CITY_SYMBOL && moveDirection != UP) {
		lengthCounter += 1;
		addRoad(mapGraph, cityName, x, y + 1, lengthCounter);
		addedCities += 1;
	}
	if (x + 1 < width && map[y][x + 1] == CITY_SYMBOL && moveDirection != LEFT) {
		lengthCounter += 1;
		addRoad(mapGraph, cityName, x + 1, y, lengthCounter);
		addedCities += 1;
	}
	if (x - 1 >= 0 && map[y][x - 1] == CITY_SYMBOL && moveDirection != RIGHT) {
		lengthCounter += 1;
		addRoad(mapGraph, cityName, x - 1, y, lengthCounter);
		addedCities += 1;
	}
	if (addedCities > 0) {
		return true;
	}
	return false;
	
}

void readRoad(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height, int lengthCounter) {
	lengthCounter += 1;
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
			checkRoads(x, y, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
			break;
		}
		if (moveDirection == UP && y - 1 >= 0 && (map[y - 1][x] == ROAD || map[y - 1][x] == CITY_SYMBOL)) {
			y -= 1;
			lengthCounter += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection, lengthCounter)) {
				break;
			}
		}
		else if (moveDirection == DOWN && y + 1 < height && (map[y + 1][x] == ROAD || map[y + 1][x] == CITY_SYMBOL)) {
			y += 1;
			lengthCounter += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection, lengthCounter)) {
				break;
			}
		}
		else if (moveDirection == RIGHT && x + 1 < width && (map[y][x + 1] == ROAD || map[y][x + 1] == CITY_SYMBOL)) {
			x += 1;
			lengthCounter += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection, lengthCounter)) {
				break;
			}
		}
		else if (moveDirection == LEFT && x - 1 >= 0 && (map[y][x - 1] == ROAD) || map[y][x - 1] == CITY_SYMBOL) {
			x -= 1;
			lengthCounter += 1;
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection, lengthCounter)) {
				break;
			}
		}
		else {
			if (checkCity(x, y, map, mapGraph, cityName, width, height, moveDirection, lengthCounter)) {
				break;
			}
			else {
				checkRoads(x, y, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
				break;
			}
		}
	}
}

void checkRoads(int x, int y, char** map, direction moveDirection, Graph* mapGraph, char* cityName, int width, int height, int lengthCounter) {
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
			readRoad(x, y - 1, map, newMoveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		if (y + 1 < height && map[y + 1][x] == ROAD && moveDirection != UP) {
			newMoveDirection = DOWN;
			readRoad(x, y + 1, map, newMoveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		if (x - 1 >= 0 && map[y][x - 1] == ROAD && moveDirection != RIGHT) {
			newMoveDirection = LEFT;
			readRoad(x - 1, y, map, newMoveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		if (x + 1 < width && map[y][x + 1] == ROAD && moveDirection != LEFT) {
			newMoveDirection = RIGHT;
			readRoad(x + 1, y, map, newMoveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
	}
	else {//change of direction of the road 
		if (y - 1 >= 0 && map[y - 1][x] == ROAD && moveDirection != DOWN) {
			moveDirection = UP;
			readRoad(x, y - 1, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		else if (y + 1 < height && map[y + 1][x] == ROAD && moveDirection != UP) {
			moveDirection = DOWN;
			readRoad(x, y + 1, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		else if (x - 1 >= 0 && map[y][x - 1] == ROAD && moveDirection != RIGHT) {
			moveDirection = LEFT;
			readRoad(x - 1, y, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
		}
		else if (x + 1 < width && map[y][x + 1] == ROAD && moveDirection != LEFT) {
			moveDirection = RIGHT;
			readRoad(x + 1, y, map, moveDirection, mapGraph, cityName, width, height, lengthCounter);
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
				checkRoads(x, y, map, NONE, mapGraph, cityName, width, height, 0);
			}
		}
	}
}

char* getCityName() {
	char buffer[BUFFER_SIZE];
	char input = getchar();
	int length = 0;
	while (input != SPACE) {
		if (input != NEW_LINE) {
			buffer[length] = input;
			length += 1;
		}
		input = getchar();
	}
	buffer[length] = END_OF_TEXT;
	length += 1;
	char* cityName = new char[length];
	for (int i = 0; i < length; i++) {
		cityName[i] = buffer[i];
	}
	return cityName;
}

void addFlight(Graph* mapGraph) {
	char* cityName1;
	char* cityName2;
	char input = getchar();
	cityName1 = getCityName();
	cityName2 = getCityName();
	int distance;
	cin >> distance;
	mapGraph->findCityByName(cityName1)->addNewAdjacentCity(distance, cityName2);
}

void getFlights(Graph* mapGraph) {
	int flightsAmount;
	cin >> flightsAmount;
	if (flightsAmount == 0) {
		return;
	}
	else {
		for (int i = 0; i < flightsAmount; i++) {
			addFlight(mapGraph);
		}
	}
}

void countShortestDistance(char* startingPoint, char* endingPoint, Graph* mapGraph, int commandType) {
	int citiesAmount = mapGraph->getAmount();
	shortestRoadToCity* startingCity = nullptr;
	shortestRoadToCity* cities = new shortestRoadToCity[citiesAmount];
	for (int i = 0; i < citiesAmount; i++) {
		cities[i].cityName = mapGraph->findCityByNumber(i)->getCityName();
		if (compareText(cities[i].cityName, startingPoint)) {
			cities[i].distance = 0;
		}
		else {
			cities[i].distance = INT_MAX;
		}
		cities[i].next = nullptr;
	}
	cityNameNode* currentCity = mapGraph->findCityByName(startingPoint);
	PriorityQueue* citiesToCheck = new PriorityQueue(currentCity, mapGraph);
	mapGraph->setAllCitiesUnvisited();
	int currentDistance = 0;
	do {
		if (currentCity->getState() == false) {
			adjacentCityNode* currentAdjacentCity = currentCity->getAdjacentCitiesList()->getHead();
			for (int i = 0; i < citiesAmount; i++) {
				if (compareText(cities[i].cityName, currentCity->getCityName())) {
					startingCity = &cities[i];
				}
			}
			while (currentAdjacentCity != nullptr) {
				for (int i = 0; i < citiesAmount; i++) {
					if (compareText(cities[i].cityName, currentAdjacentCity->getCityName()) && cities[i].distance > currentAdjacentCity->getDistance() + startingCity->distance) {
						cities[i].distance = currentAdjacentCity->getDistance() + startingCity->distance;
						if (startingCity->distance != 0) {
							cities[i].next = startingCity;
						}
						else {
							cities[i].next = nullptr;
						}
						break;
					}//iteracja po wszystkich sąsiednich miastach
				}
				currentAdjacentCity = currentAdjacentCity->getNextNode();
			}
			citiesToCheck->addAllAdjacentCities(mapGraph, currentCity);
			currentCity->setVisitedState(true);
		}
		citiesToCheck->removeFirstFromQueue();
		if (citiesToCheck->getFront() != nullptr) {
			currentCity = citiesToCheck->getFront()->getCity();
		}
	} while (citiesToCheck->getFront() != nullptr);
	for (int i = 0; i < citiesAmount; i++) {
		if (compareText(cities[i].cityName, endingPoint)) {
			cout << cities[i].distance;
			if (commandType == SHOW_ROAD) {
				for (int i = 0; i < citiesAmount; i++) {
					if (compareText(endingPoint, cities[i].cityName)) {
						shortestRoadToCity* tmp = &cities[i];
						while (tmp->next != nullptr) {
							cout << SPACE << tmp->next->cityName;
							tmp = tmp->next;
						}
						break;
					}
				}
			}
			cout << endl;
			return;
		}
	}
	return;
}

void getCommands(Graph* mapGraph) {
	int commandsNumber, commandType;
	char* cityName1;
	char* cityName2;
	cin >> commandsNumber;
	for (int i = 0; i < commandsNumber; i++) {
		cityName1 = getCityName();
		cityName2 = getCityName();
		cin >> commandType;
		countShortestDistance(cityName1, cityName2, mapGraph, commandType);
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
	getFlights(mapGraph);
	getCommands(mapGraph);
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;
	return 0;
}