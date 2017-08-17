/*
//!	Docs-Ex -- A simple documentation extractor for C/C++ source files
//!	Copyright (C) 2017 Anand Menon

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

//!	You should have received a copy of the GNU General Public License
//!	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//!
*/

//!Header files:
//!	<iostream> , for standard I/O streams
#include <iostream>
//!	<fstream> for file streams
#include <fstream>

/***

[FUNCTION]	int extract(char filename[])
	This function extracts the documentation from inside the file of the given
	`char filename[]` in the present working directory. It does so by reading
	each line in the source file and cheecking if each line begins with a
	designated 'token' for documentation comments. It then writes to the
	standard output file (if the line was a doc-line).

***/
int extract(char filename[])
{
	std::ifstream infile;
	infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		infile.open(filename);
		std::string line;
	 	bool is_comment = false;
		while(getline(infile, line))
		{
			if(is_comment == true)
			{
				if(line.substr(0,4) == "***/")
				{
					line.erase(0,4);
					is_comment = false;
				}
				else
				{
					std::cout << line << std::endl;
				}
			}
			else
			{
				if(line.substr(0,3) == "//!")
				{
					line.erase(0,3);
					std::cout << line << std::endl;
				}
				else
					if(line.substr(0,4) ==  "/***")
					{
						line.erase(0,4);
						std::cout << line << std::endl;
						is_comment = true;
					}
			}
		}
	}
	catch(std::system_error &e)
	{
		if(!infile.eof())
			std::cerr << "There was an error processing the file \""
			    << filename << "\"" << std::endl << "[Error] "
			    << e.what() << std::endl;
	}
	catch(const char msg[])
	{
		std::cerr << msg << std::endl;
	}
	catch( ... )
	{
		infile.close();
		return 1;
	}
	return 0;
}

/***

[PROGRAM]	USAGE: docs-ex <file-1> <file-2> ... where <file-*> is a C/C++
 		source file.

	This program is to be used to extract documentation lines ("doc-lines")
	from C/C++ source files and output the exxtracted lines to standard output.
	The end-user is expected to redirect the output ("piping") to another
	program, or to a specified output file.

	EXAMPLES:
		(1)	> docs-ex "source.c" | grep "file"
		(2)	> docs-ex "main.cpp" > "docs.txt"

***/
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Usage: \"docs-ex <input-1> <input-2> ... etc.\""<<std::endl;
		return 1;
	}
	for(int i = 1; i < argc; i++)
	{
		try
		{
			if(extract(argv[i]))
				std::cerr << "Error processing file \""
				    << argv[i] << "\"" << std::endl;
		}
		catch(const char msg[])
		{
			std::cerr << msg << std::endl;
		}
	}
}
