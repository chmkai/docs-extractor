/*
	Docs-Ex -- A simple documentation extractor for C/C++ source files
	Copyright (C) 2017 Anand Menon

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>

int extract(char output[], char filename[])
{
	std::ifstream infile;
	std::ofstream outfile;
	infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		infile.open(filename);
	}
	catch(std::system_error &e)
	{
		std::cerr << "There was an error opening the file \""
		    << filename << "\"" << std::endl << e.what() << std::endl;
	}
	catch(const char msg[])
	{
		std::cerr << msg << std::endl;
	}
	catch( ... )
	{
		infile.close();
		outfile.close();
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout<<"Usage: \"docs-ex <output-file>"
		    << "<input-1> <input-2> ... etc.\""<<std::endl;
		return 1;
	}
	for(int i = 2; i < argc; i++)
	{
		try
		{
			extract(argv[1],argv[i]);
		}
		catch(const char msg[])
		{
			std::cerr << msg << std::endl;
		}
	}
}
