#include "include/high_scores.h"
#include <iostream>
#include <fstream>
#include <string>

const std::string high_scores_filename = "high_scores.txt";

namespace high_scores {
	int print() {
		// Read the high score file and print all results
		std::string username;
		int high_score = 0;
		std::ifstream in_file{high_scores_filename};

		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			std::cout << "Check that file exists" << std::endl;
			std::cout << "May be not results yet?" << std::endl;
			std::cout << "Try play game first" << std::endl;
			return -1;
		}

		std::cout << std::endl << "   High scores table:   " << std::endl;

		while (true) {
			in_file >> username;
			in_file >> high_score;
			in_file.ignore();

			if (in_file.fail()) {
				break;
			}

			std::cout << "   " << username << '\t' << high_score << std::endl;
		}
		std::cout << std::endl;

		in_file.close();
		return 0;
	}

	int save(std::string user_name, int attempts_count) {
		std::string name_from_file;


		//save attempts count as scores
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			std::cout << "Try create file " << high_scores_filename << " in folder with game and replay." << std::endl;
			return -1;
		}

		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;

		out_file.close();
		return 0;
	}
}
