/*
 *  * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */


#include <iostream>
#include <cassert>
#include <fstream>

#include "texteater.hpp"

using namespace std;

void testMainTextEaterFunction();
void testInstructionList();
void testLoadFileFunction();
void testExecuteSearch();
void testExecuteCopy();
void testExecuteConditionalSearch();
void testMainTextEaterFunctionSmallData();
void testCleanSearchString();

int main(int argc, char **argv)
{
	testLoadFileFunction();
	testInstructionList();
	testExecuteSearch();
	testExecuteCopy();
	testExecuteConditionalSearch();
	testCleanSearchString();
	
	testMainTextEaterFunctionSmallData();
	testMainTextEaterFunction();
	cout << "all tests fine" << endl;
	return 0;
}

void testLoadFileFunction() {
	string fileText = loadFileToString("res/TextToLoad.txt");
	assert(fileText=="Why hello there!\n");
}

void testInstructionList() {
	InstructionList instructions;
	instructions.addInstruction("search for hello, my name is ");
	instructions.addInstruction("copy till .");
	instructions.addInstruction("if you find I like ");
	instructions.addInstruction("copy till .");
	instructions.addInstruction("otherwise if you find somethings I like are ");
	instructions.addInstruction("copy till ,");
	instructions.addInstruction("then");
	instructions.addInstruction("search for goodbye!");
	
	
	InstructionListElement * nextInst = instructions.getNextInstruction();
	assert(nextInst->type == SEARCH);
	assert(nextInst->searchStrings[0] == "hello, my name is ");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == COPY);
	assert(nextInst->searchStrings[0] == ".");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == CONDITIONAL_SEARCH);
	assert(nextInst->searchStrings[0] == "I like ");
	assert(nextInst->searchStrings[1] == "somethings I like are ");
	
	nextInst = instructions.getNextInstruction(0);
	assert(nextInst->type == COPY);
	assert(nextInst->searchStrings[0] == ".");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == UNDEFINED);
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == SEARCH);
	assert(nextInst->searchStrings[0]=="goodbye!");
	
	instructions.goToBeginning();
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == SEARCH);
	assert(nextInst->searchStrings[0] == "hello, my name is ");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == COPY);
	assert(nextInst->searchStrings[0] == ".");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == CONDITIONAL_SEARCH);
	assert(nextInst->searchStrings[0] == "I like ");
	assert(nextInst->searchStrings[1] == "somethings I like are ");
	
	nextInst = instructions.getNextInstruction(1);
	assert(nextInst->type == COPY);
	assert(nextInst->searchStrings[0] == ",");
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == UNDEFINED);
	
	nextInst = instructions.getNextInstruction();
	assert(nextInst->type == SEARCH);
	assert(nextInst->searchStrings[0]=="goodbye!");
	
	cout << "testInstructionList was fine " << endl;
}

void testExecuteSearch() {
	TextEater processor;
	processor.data = "Welcome everyone, hello, my name is Will. names are silly";
	InstructionList instructions;
	instructions.addInstruction("search for hello, my name is ");
	instructions.addInstruction("search for name");
	
	InstructionListElement * nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	
	assert(processor.textPointer== 36);
	
	nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	
	assert(processor.textPointer==46);
	
	cout << "testExecuteSearch was fine" << endl;
}

void testExecuteCopy() {
	TextEater processor;
	processor.data = "Welcome everyone, hello, my name is Will.";
	InstructionList instructions;
	instructions.addInstruction("copy till , ");
	instructions.addInstruction("copy till  ");
	
	InstructionListElement * nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	
	assert(processor.textPointer==18);
	assert(processor.extract=="Welcome everyone");
	
	nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	
	assert(processor.textPointer==25);
	assert(processor.extract=="hello,");
	
	cout << "testExecuteCopy was fine" << endl;
}

void testExecuteConditionalSearch() {
	InstructionList instructions;
	instructions.addInstruction("search for hello, my name is ");
	instructions.addInstruction("copy till .");
	instructions.addInstruction("if you find I like ");
	instructions.addInstruction("copy till .");
	instructions.addInstruction("otherwise if you find somethings I like are ");
	instructions.addInstruction("copy till ,");
	instructions.addInstruction("then");
	instructions.addInstruction("search for goodbye!");
	
	TextEater processor;
	processor.data = "Welcome everyone, hello, my name is Will. somethings I like are reading, hoop. blah, gooble, goodbye! folkes. Although somethings I like are bananas, and peaches. goodbye!";
	
	InstructionListElement * nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	assert(processor.textPointer==36);
	
	nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	assert(processor.textPointer==41);
	assert(processor.extract=="Will");
	
	nextInst = instructions.getNextInstruction();
	processor.executeInstruction(nextInst);
	assert(processor.textPointer==64);
	
	nextInst = instructions.getNextInstruction(processor.conditionalReturnValue);
	processor.executeInstruction(nextInst);
	assert(processor.textPointer==72);
	assert(processor.extract=="reading");
	
	cout << "testExecuteConditionalSearch was fine" << endl;
}

void testCleanSearchString() {
	assert(cleanedSearchString("Hello world. What follows the less than sign is a new line >\\n< there should be a slash >\\\\< here\\nand there should be a space >\\s< here\n")=="Hello world. What follows the less than sign is a new line >\n< there should be a slash >\\< here\nand there should be a space > < here\n");
	cout << "testCleanSearchString was fine"<<endl;
}

void testMainTextEaterFunctionSmallData() {
	TextEater processor("res/SmallScript.txt");
	processor.generateTableFromFile("res/SmallSourceText.txt");
	
	assert(processor.getElement(0,0)=="Will");
	assert(processor.getElement(0,1)=="reading");
	assert(processor.getElement(0,2)=="blue");
	assert(processor.getElement(1,0)=="Will");
	assert(processor.getElement(1,1)=="cats");
	assert(processor.getElement(1,2)=="blue");
}

void testMainTextEaterFunction() {
	TextEater processor("res/SearchScript.txt");
	processor.generateTableFromFile("res/ListOfPokemon.txt");
	
	assert(processor.getElement(0,0)=="001");
	assert(processor.getElement(0,1)=="001");
	assert(processor.getElement(0,2)=="http://cdn.bulbagarden.net/upload/e/ec/001MS.png");
	assert(processor.getElement(0,3)=="Bulbasaur");
	assert(processor.getElement(0,4)=="Grass");
	assert(processor.getElement(0,5)=="Poison");
	
	assert(processor.getElement(146,0)=="147");
	assert(processor.getElement(146,1)=="147");
	assert(processor.getElement(146,2)=="http://cdn.bulbagarden.net/upload/2/26/147MS.png");
	assert(processor.getElement(146,3)=="Dratini");
	assert(processor.getElement(146,4)=="Dragon");
	assert(processor.getElement(146,5)=="");
	
	assert(processor.getElement(155,0)=="005");
	assert(processor.getElement(155,1)=="156");
	assert(processor.getElement(155,2)=="http://cdn.bulbagarden.net/upload/3/36/156MS.png");
	assert(processor.getElement(155,3)=="Quilava");
	assert(processor.getElement(155,4)=="Fire");
	assert(processor.getElement(155,5)=="");
	
	//there are some doubles in the table, this loop searches for the index of the first (and only) occurance of national pokedex number 718 (Zygarde) the last element in the table.
	int index=155;
	while(processor.getElement(index,1)!="718")
	{
		index++;
		assert(index<1000000);
	}
	
	assert(processor.getElement(index,0)=="150");
	assert(processor.getElement(index,1)=="718");
	assert(processor.getElement(index,2)=="http://cdn.bulbagarden.net/upload/a/ab/000MS.png");
	assert(processor.getElement(index,3)=="Zygarde");
	assert(processor.getElement(index,4)=="Dragon");
	assert(processor.getElement(index,5)=="Ground");
	
	assert(processor.getElement(index+1,0)=="");
	
	cout << "testMainTextEaterFunction completed" << endl;
}
