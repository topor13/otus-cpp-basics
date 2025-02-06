#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "include/help.h"
#include "include/high_scores.h"

const std::string high_scores_filename = "high_scores.txt";
int max_value = 100;
int result = 0;

int main(int argc, char* argv[]) {
	// To check - does use print some other argument we should check if the argc >= 2
	if (argc >= 2) {
		for(int i=1; i<argc; i++) {
			std::string arg_value{ argv[i] };
			if (arg_value == "-help") {
				help::print();
				return 0;
			} else if (arg_value == "-max") {
				if (argc < (i + 2)) {
					std::cout << "Wrong usage! -max arg must have digit!" << std::endl;
					help::print();
					return -1;
				}
				max_value = std::stoi(argv[i + 1]);
				i++;
			} else if (arg_value == "-table") {
				result = high_scores::print();	
				return result;
			} else {
				std::cout << "Wrong usage! Unknown argument " << arg_value << "!" << std::endl;
				help::print();
				return -1;
			}
		}
	}

	std::string user_name;
	int guess;
	int attempts_count = 0;
	std::srand(std::time(nullptr));
	const int random_value = std::rand() % max_value;
	std::cout << "   Hi! Enter your name, please:" << std::endl;
	std::cin >> user_name;
	std::cout << "   Enter your guess" << std::endl;
	
	while (true) {
		std::cin >> guess;
		attempts_count += 1;
		if (guess == random_value) {
			std::cout << "   You win! " << "Attempts = " << attempts_count << std::endl;
			break;
		} else if (guess < random_value) {
			std::cout << "   Greater than " << guess << std::endl;
		} else {
			std::cout << "   Less than " << guess << std::endl;
		};
	};

	result = high_scores::save(user_name, attempts_count);
		if (result != 0) {
			return result;
		}
	result = high_scores::print();
}