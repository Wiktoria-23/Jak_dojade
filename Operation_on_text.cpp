#include "Operation_on_text.h"

bool compareText(char* textOne, char* textTwo) {
	int i = 0;
	while (textOne[i] != END_OF_TEXT) {
		if (textOne[i] != textTwo[i]) {
			return false;
		}
		i++;
	}
	if (textOne[i] == END_OF_TEXT && textTwo[i] == END_OF_TEXT) {
		return true;
	}
}