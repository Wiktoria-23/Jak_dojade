#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#include "adjacentCityNode.h"
#include "PriorityQueue.h"
#include "Operation_on_text.h"
#include "SearchingNode.h"

#define BUFFER_SIZE 50
#define TRUE 1
#define FALSE 0
#define SHOW_ROAD 1
using namespace std;

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

int readCityName(char* cityName, int x, char* mapLine, int width) {
	while (x - 1 >= 0 && mapLine[x - 1] != NOTHING && mapLine[x - 1] != ROAD && mapLine[x - 1] != CITY_SYMBOL) { //checks if previous character is '.'
		x -= 1;
	}
	int i = 0;
	int size = 0;
	while (x < width && mapLine[x] != NOTHING && mapLine[x] != ROAD && mapLine[x] != CITY_SYMBOL) {
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
	if (y - 1 >= 0 && map[y - 1][x] != NOTHING && map[y - 1][x] != ROAD && map[y - 1][x] != CITY_SYMBOL) {
		size = readCityName(input, x, map[y - 1], width);
	}
	else if (y + 1 < height && map[y + 1][x] != NOTHING && map[y + 1][x] != ROAD && map[y + 1][x] != CITY_SYMBOL) {
		size = readCityName(input, x, map[y + 1], width);
	}
	else if (x + 1 < width && map[y][x + 1] != NOTHING && map[y][x + 1] != ROAD && map[y][x + 1] != CITY_SYMBOL) {
		size = readCityName(input, x + 1, map[y], width);
	}
	else if (x - 1 >= 0 && map[y][x - 1] != NOTHING && map[y][x - 1] != ROAD && map[y][x - 1] != CITY_SYMBOL) {
		size = readCityName(input, x - 1, map[y], width);
	}
	else if (x + 1 < width && y + 1 < height && map[y + 1][x + 1] != NOTHING && map[y + 1][x + 1] != ROAD && map[y + 1][x + 1] != CITY_SYMBOL) {
		size = readCityName(input, x + 1, map[y + 1], width);
	}
	else if (y + 1 < height && x - 1 >= 0 && map[y + 1][x - 1] != NOTHING && map[y + 1][x - 1] != ROAD && map[y + 1][x - 1] != CITY_SYMBOL) {
		size = readCityName(input, x - 1, map[y + 1], width);
	}
	else if (x - 1 >= 0 && y - 1 >= 0 && map[y - 1][x - 1] != NOTHING && map[y - 1][x - 1] != ROAD && map[y - 1][x - 1] != CITY_SYMBOL) {
		size = readCityName(input, x - 1, map[y - 1], width);
	}
	else if (x + 1 < width && y - 1 >= 0 && map[y - 1][x + 1] != NOTHING && map[y - 1][x + 1] != ROAD && map[y - 1][x + 1] != CITY_SYMBOL) {
		size = readCityName(input, x + 1, map[y - 1], width);
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

void addRoad(Graph* mapGraph, char* cityName, int cityX, int cityY, int distance) {
	cityNameNode* destination = mapGraph->findCityByCoordinates(cityX, cityY);
	mapGraph->findCityByName(cityName)->addNewAdjacentCity(distance, destination->getCityName());
	mapGraph->findCityByName(destination->getCityName())->addNewAdjacentCity(distance, cityName);
}

void checkRoads(List<SearchingNode>* toSearch, char** map, bool** checkedRoads, Graph* mapGraph, char* cityName, int width, int height) {
	SearchingNode* tmp = toSearch->getHead();
	while (tmp != nullptr) {
		int x = tmp->getX();
		int y = tmp->getY();
		if (y - 1 >= 0 && checkedRoads[y - 1][x] == false) {
			if (map[y - 1][x] == ROAD) {
				checkedRoads[y - 1][x] = true;
				SearchingNode* newRoad = new SearchingNode(x, y - 1, tmp->getDistance() + 1);
				toSearch->addNewLastNode(newRoad);
			}
			else if (map[y - 1][x] == CITY_SYMBOL) {
				checkedRoads[y - 1][x] = true;
				addRoad(mapGraph, cityName, x, y - 1, tmp->getDistance() + 1);
			}
		}
		if (y + 1 < height && checkedRoads[y + 1][x] == false) {
			if (map[y + 1][x] == ROAD) {
				checkedRoads[y + 1][x] = true;
				SearchingNode* newRoad = new SearchingNode(x, y + 1, tmp->getDistance() + 1);
				toSearch->addNewLastNode(newRoad);
			}
			else if (map[y + 1][x] == CITY_SYMBOL) {
				checkedRoads[y + 1][x] = true;
				addRoad(mapGraph, cityName, x, y + 1, tmp->getDistance() + 1);
			}
		}
		if (x - 1 >= 0 && checkedRoads[y][x - 1] == false) {
			if (map[y][x - 1] == ROAD) {
				checkedRoads[y][x - 1] = true;
				SearchingNode* newRoad = new SearchingNode(x - 1, y, tmp->getDistance() + 1);
				toSearch->addNewLastNode(newRoad);
			}
			else if (map[y][x - 1] == CITY_SYMBOL) {
				checkedRoads[y][x - 1] = true;
				addRoad(mapGraph, cityName, x - 1, y, tmp->getDistance() + 1);
			}
		}
		if (x + 1 < width && checkedRoads[y][x + 1] == false) {
			if (map[y][x + 1] == ROAD) {
				checkedRoads[y][x + 1] = true;
				SearchingNode* newRoad = new SearchingNode(x + 1, y, tmp->getDistance() + 1);
				toSearch->addNewLastNode(newRoad);
			}
			else if (map[y][x + 1] == CITY_SYMBOL) {
				checkedRoads[y][x + 1] = true;
				addRoad(mapGraph, cityName, x + 1, y, tmp->getDistance() + 1);
			}
		}
		toSearch->deleteElement(tmp);
		tmp = toSearch->getHead();
	}
}

void readMap(int height, int width, char** map, Graph* mapGraph, bool** checkedRoads) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				addCityName(x, y, map, width, height, mapGraph);
			}
		}
	}
	cityNameNode* currentCity = mapGraph->getCityNames()->getHead();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				int counter = 0;
				if ((y - 1 >= 0 && (map[y - 1][x] == ROAD || map[y - 1][x] == CITY_SYMBOL)) || (y + 1 < height && (map[y + 1][x] == ROAD || map[y + 1][x] == CITY_SYMBOL)) || (x - 1 >= 0 && (map[y][x - 1] == ROAD || map[y][x - 1] == CITY_SYMBOL)) || (x + 1 < width && (map[y][x + 1] == ROAD || map[y][x + 1] == CITY_SYMBOL))) {
					List<SearchingNode>* toSearch = new List<SearchingNode>();
					SearchingNode* newRoad = new SearchingNode(x, y, 0);
					checkedRoads[y][x] = true;
					toSearch->addNewLastNode(newRoad);
					checkRoads(toSearch, map, checkedRoads, mapGraph, currentCity->getCityName(), width, height);
					currentCity = currentCity->getNextNode();
					for (int y1 = 0; y1 < height; y1++) {
						for (int x1 = 0; x1 < width; x1++) {
							checkedRoads[y1][x1] = false;
						}
					}
				}
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
	getchar();
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

void printRoad(shortestRoadToCity* city, char* endingPoint) {
	if (city->next != nullptr) {
		printRoad(city->next, endingPoint);
	}
	if (!compareText(endingPoint, city->cityName)) {
		cout << SPACE << city->cityName;
	}
}

void checkDistances(cityNameNode* currentCity, Graph* mapGraph, shortestRoadToCity* citiesArr, shortestRoadToCity* previousCity) {
	adjacentCityNode* tmp = currentCity->getAdjacentCitiesList()->getHead();
	while (tmp != nullptr) {
		for (int i = 0; i < mapGraph->getAmount(); i++) {
			if (compareText(citiesArr[i].cityName, tmp->getCityName()) && tmp->getDistance() + previousCity->distance < citiesArr[i].distance) {
				citiesArr[i].distance = tmp->getDistance() + previousCity->distance;
				if (previousCity->distance != 0) {
					citiesArr[i].next = previousCity;
				}
				else {
					citiesArr[i].next = nullptr;
				}
			}
		}
		tmp = tmp->getNextNode();
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
	PriorityQueue* citiesToCheck = new PriorityQueue(currentCity);
	mapGraph->setAllCitiesUnvisited();
	while (citiesToCheck->getFront() != nullptr) {
		if (currentCity->getState() == false) {
			for (int i = 0; i < citiesAmount; i++) {
				if (compareText(cities[i].cityName, currentCity->getCityName())) {
					startingCity = &cities[i];
				}
			}
			currentCity = citiesToCheck->getFront()->getCity();
			checkDistances(currentCity, mapGraph, cities, startingCity);
		}
		if (citiesToCheck->getFront() != nullptr) {
			currentCity = citiesToCheck->getFront()->getCity();
		}
		citiesToCheck->removeFirstFromQueue();
		if (currentCity->getState() == false) {
			citiesToCheck->addAllAdjacentCities(mapGraph, currentCity, startingCity->distance);
			currentCity->setVisitedState(true);
		}
		if (citiesToCheck->getFront() != nullptr) {
			currentCity = citiesToCheck->getFront()->getCity();
		}
	}
	for (int i = 0; i < citiesAmount; i++) {
		if (compareText(cities[i].cityName, endingPoint)) {
			cout << cities[i].distance;
			if (commandType == SHOW_ROAD) {
				shortestRoadToCity* endingCity = nullptr;
				for (int j = 0; j < citiesAmount; j++) {
					if (compareText(cities[j].cityName, endingPoint)) {
						endingCity = &cities[j];
					}
				}
				printRoad(endingCity, endingPoint);
			}
			cout << endl;
			return;
		}
	}
	delete[] cities;
}

void getCommands(Graph* mapGraph) {
	int commandsNumber, commandType;
	cin >> commandsNumber;
	for (int i = 0; i < commandsNumber; i++) {
		char* cityName1;
		char* cityName2;
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
	char** map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	bool** checkedRoads = new bool* [height];
	for (int y = 0; y < height; y++) {
		checkedRoads[y] = new bool[width];
		for (int x = 0; x < width; x++) {
			checkedRoads[y][x] = false;
		}
	}
	getMap(height, width, map);
	readMap(height, width, map, mapGraph, checkedRoads);
	getFlights(mapGraph);
	getCommands(mapGraph);
	for (int i = 0; i < height; i++) {
		delete[] checkedRoads[i];
	}
	delete[] checkedRoads;
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;
	delete mapGraph;
	return 0;
}