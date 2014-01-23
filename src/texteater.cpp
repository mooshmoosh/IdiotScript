/*
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */

#include <fstream>
#include "texteater.hpp"

using namespace std;

void TextEater::init() {
	textPointer = 0;
	conditionalReturnValue = 0;
	extract = "";
	lastErrorCode = OK;
}

TextEater::TextEater()
{
	init();
}

TextEater::TextEater(std::string scriptFileName) {
	init();
	loadScript(scriptFileName);
}

TextEater::~TextEater() {
	
}

void TextEater::generateTableFromFile(std::string filename) {
	this->data = loadFileToString(filename);
	generateTableFromString(data);
}

void TextEater::generateTableFromString(std::string &data) {
	InstructionListElement * nextInstruction;
	int instCount = 0;
	while(lastErrorCode==OK) {
		instCount++;
		nextInstruction = instructionList.getNextInstruction(conditionalReturnValue);
		executeInstruction(nextInstruction);
		if(extract!="")
		{
			rows.lastElement().append(extract);
		}
	}
}

std::string TextEater::getElement(int row, int column) {
	return rows[row][column];
}

void TextEater::loadScript(std::string filename) {
	ifstream scriptFile(filename.c_str());
	if(!scriptFile.is_open()) {
		cout << "could not open script file: \"" << filename << "\"" << endl;
		return;
	}
	
	string line;
	
	while(getline(scriptFile,line)) {
		instructionList.addInstruction(line);
	}
	
	scriptFile.close();
}

string loadFileToString(string filename) {
	ifstream dataFile(filename.c_str());
	if(!dataFile.is_open()) {
		cout << "could not open file: \"" << filename << "\"" << endl;
		return "";
	}
	
	string result;
	dataFile.seekg(0,ios::end);
	result.resize(dataFile.tellg());
	dataFile.seekg(0,ios::beg);
	dataFile.read(&result[0],result.size());
	dataFile.close();
	
	return result;
}

void TextEater::executeInstruction(InstructionListElement* instruction) {
	
	conditionalReturnValue = 0;
	extract = "";
	lastErrorCode = 0;
	
	if(instruction==NULL) {
		setErrorFlag(END_OF_INSTRUCTIONS);
		return;
	}
	
	if(textPointer>=data.length()) {
		setErrorFlag(END_OF_TEXT);
		return;
	}
	
	int endpoint;
	
	int searchResultCount;
	int * searchResults;
	
	switch(instruction->type) {
	case SEARCH:
		endpoint = data.find(instruction->searchStrings[0],textPointer);
		if(endpoint==-1)
		{
			setErrorFlag(BAD_INSTRUCTION);
			return;
		}
		textPointer= endpoint + instruction->searchStrings[0].length();
		break;
	case COPY:
		endpoint = data.find(instruction->searchStrings[0],textPointer);
		if(endpoint==-1)
		{
			setErrorFlag(BAD_INSTRUCTION);
			return;
		}
		extract = data.substr(textPointer,endpoint-textPointer);
		textPointer = endpoint + instruction->searchStrings[0].length();
		break;
	case CONDITIONAL_SEARCH:
		searchResultCount = instruction->searchStrings.length();
		searchResults = new int[searchResultCount];
		for(int i=0;i<searchResultCount;i++) {
			searchResults[i] = 0;
		}
		endpoint = data.length() + 1;
		for(int i=0;i<searchResultCount;i++) {
			searchResults[i] = data.find(instruction->searchStrings[i],textPointer);			
			if(searchResults[i] != -1 && searchResults[i] < endpoint) {
				endpoint = searchResults[i];
				conditionalReturnValue = i;
			}
		}
		
		textPointer = endpoint + instruction->searchStrings[conditionalReturnValue].length();
		delete [] searchResults;
		break;
	case REPEAT:
		rows.append();
		instructionList.goToBeginning();
		break;
	default:
		break;

	}
}

void TextEater::setErrorFlag(TextEaterErrorCodeType code) {
	lastErrorCode=code;
}
