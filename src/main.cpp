/*
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */


#include <iostream>
#include "texteater.hpp"

using namespace std;

int main(int argc, char **argv)
{
	if(argc!=3) {
		cout << "usage idiotscript {script} {text file}" << endl;
		return 1;
	}

	TextEater processor(argv[1]);
	processor.generateTableFromFile(argv[2]);

	int i = 0;
	int j = 0;

	string nextElement;

	while(1) {
		nextElement = processor.getElement(i,j);
		if(nextElement=="") {
			if(j==0) {
				break;
			}
			i++;
			j=0;
			cout << "\n";
		}
		else {
			j++;
			cout << "\"" << nextElement << "\",";
		}
		
	}
	
	return 0;
}
