/*
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */

#ifndef TEXTEATER_HPP
#define TEXTEATER_HPP

#include <iostream>
#include "instructionlist.hpp"

std::string loadFileToString(std::string);

enum TextEaterErrorCodeType {
	OK,
	END_OF_TEXT,
	END_OF_INSTRUCTIONS,
	BAD_INSTRUCTION
};

class TextEater
{
	public:
		TextEater();
		TextEater(std::string scriptFileName);
		~TextEater();
		void generateTableFromFile(std::string filename);
		void generateTableFromString(std::string &data);
		std::string getElement(int, int);
		void loadScript(std::string filename);
		
		
		void executeInstruction(InstructionListElement*);
		std::string data;
		int textPointer;
		int conditionalReturnValue;
		std::string extract;
		
		int lastErrorCode;
		void setErrorFlag(TextEaterErrorCodeType);
			
	private:
		void init();
		InstructionList instructionList;
		StringListList * rows;
		StringListList * lastRowAdded;
		
		
		/* add your private declarations */
};

#endif /* TEXTEATER_HPP */ 
