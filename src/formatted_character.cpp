#include "formatted_character.hpp"

char cuttle::formatted_character(char part1, char part2) {
	if (part1 == '\\') {
		switch (part2) {
		case 'n':
			return '\n';
		case '\\':
			return '\\';
		case 't':
			return '\t';
		case 'r':
			return '\r';
		default:
			return part2;
		}
	} else {
		return part2;
	}
}