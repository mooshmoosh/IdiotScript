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

	for(int i=0;i<processor.rows.length();i++) {
		for(int j=0;j<processor.rows[i].length();j++) {
			cout << "\"" << processor.getElement(i,j) << "\",";
		}
		cout << endl;
	}
	return 0;
}
