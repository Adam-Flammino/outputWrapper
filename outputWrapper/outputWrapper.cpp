// Adam Flammino 11/6
// Wraps each line with content in an input file in out.println(""); for ease of moving html to java servlets

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>


int main()
{
	std::string docToRead; // Must be in same directory as cpp file
	std::string docToWrite;
	std::string output = "out.println(\"";
	std::ifstream inputFile;
	std::ofstream outputFile;
	char in;
	char ans;
	char last = '\n';
	bool run = true;
	while (run)
	{
		// Note: if file to read has a BOM it will be included. Just check first line of output if you're unsure
		std::cout << "\nEnter input document name:\t"; 
		std::cin >> docToRead;
		inputFile.open(docToRead);
		if (!inputFile.is_open())
		{
			std::cout << "Unable to open file. Is " << docToRead << " in the same directory as outputWrapper.cpp?\n";
		}
		else
		{
			while (inputFile.get(in))
			{
				if ((in == '\n' || in == '\r') && last != '\n' && last != '\r') // adds line ending if it isn't just a blank line
				{
					output += "\");";
				}
				last = in;
				output += in;
				if ((in == '\n' || in == '\r') && inputFile.peek() != '\n'  && inputFile.peek() != '\r') // adds line beginning if it isn't just a blank line
				{
					output += "out.println(\"";
				}	
			}
			inputFile.close();
			output += ")\";\n";
			std::cout << "Preview file? (Y or N):\t";
			std::cin >> ans;
			ans = tolower(ans);
			if(ans == 'y')
			{
				std::cout << output << std::endl;
			}
			std::cout << "Save file? (Y or N):\t";
			std::cin >> ans;
			ans = tolower(ans);
			if(ans == 'y')
			{
				std::cout << "Enter desired output file name:\t";
				std::cin >> docToWrite;
				std::cout << "Writing results to " << docToWrite << '\n';
				outputFile.open(docToWrite);
				outputFile << output;
				outputFile.close();
			}
		}
		std::cout << "Run Again? (Y or N):\t";
		std::cin >> ans;
		ans = tolower(ans);
		if(ans == 'n')
		{
			run = false;
		}
	}
	return 0;
}
