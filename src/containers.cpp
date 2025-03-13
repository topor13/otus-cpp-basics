#include <iostream>
#include "include/serial_container.hpp"
#include "include/list_container.hpp"

int main() 
{
	int down_cntr = 0;

	std::cout << "SERIAL:" << std::endl;

	std::cout << "   | create empty serial container" << std::endl;
	SerialContainer<int> serial_values;

	std::cout << "   | pushback 10 elements to list container" << std::endl;
	for (int i = 0; i < 10; i++) {
		serial_values.push_back(i);
	}
	std::cout << "   | ";
	serial_values.print();

	std::cout << "   | size of container is: " << serial_values.size() << std::endl;

	std::cout << "   | drop 3rd, 5th and 7th elements" << std::endl;
	
	for (int i : {3,5,7}){
		down_cntr += 1; //After delete 3rd element 5th element will 4th, after delete 3rd and 5th element 7th element will 5th
		serial_values.erase(i - down_cntr);	
	}
	
	std::cout << "   | ";
	serial_values.print();

	std::cout << "   | push 10 to begin" << std::endl;
	serial_values.insert(10, 0);
	std::cout << "   | ";
	serial_values.print();

	std::cout << "   | push 20 to medium" << std::endl;
	serial_values.insert(20, serial_values.size() / 2);
	std::cout << "   | ";
	serial_values.print();

	std::cout << "   | push 30 to end" << std::endl;
	serial_values.push_back(30);
	std::cout << "   | ";
	serial_values.print();

	std::cout << "   | operator [] test, list_values[3]==";
	std::cout << serial_values[3] << std::endl;
	

	std::cout << "LIST:" << std::endl;
	std::cout << "   | create empty list container" << std::endl;
	ListContainer<int> list_values;
	std::cout << "   | pushback 10 elements to list container" << std::endl;
	for (int i = 0; i < 10; i++) {
		list_values.push_back(i);
	}
	std::cout << "   | size of container is: " << list_values.size() << std::endl;

	std::cout << "   | ";
	list_values.print();

	std::cout << "   | drop 3rd, 5th and 7th elements" << std::endl;
	down_cntr = 0;
	for (int i : {3,5,7}){
		down_cntr += 1;
		list_values.erase(i - down_cntr);
	}

	std::cout << "   | ";
	list_values.print();

	std::cout << "   | push 10 to begin" << std::endl;
	list_values.insert(10, 0);
	std::cout << "   | ";
	list_values.print();

	std::cout << "   | push 20 to medium" << std::endl;
	list_values.insert(20, list_values.size() / 2);
	std::cout << "   | ";
	list_values.print();

	std::cout << "   | push 30 to end" << std::endl;
	list_values.push_back(30);
	std::cout << "   | ";
	list_values.print();

	std::cout << "   | operator [] test, list_values[3]==";
	std::cout << list_values[3] << std::endl;

	return 0;
}