/*
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */
 
#include <iostream>
#include "listcontainer.hpp"

#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#define LENGTH_OF_SEARCH_FOR_ 11
#define LENGTH_OF_COPY_TILL_ 10
#define LENGTH_OF_IF_YOU_FIND_ 12
#define LENGTH_OF_OTHERWISE_IF_YOU_FIND_ 22

bool beginsWith(std::string&,std::string);
std::string cleanedSearchString(std::string rawString);
class InstructionListElementPointerList;
class InstructionListElement;
class InstructionList;

enum InstructionType {
	SEARCH,
	CONDITIONAL_SEARCH,
	COPY,
	REPEAT,
	UNDEFINED
};

class InstructionListElementPointerList {
	public:
		InstructionListElementPointerList();
		~InstructionListElementPointerList();
		
		void pushListDown();
		void popListUp();
		void append(InstructionListElement *);
		
		InstructionListElement * content;
		InstructionListElementPointerList * next;
};

class InstructionListElement {
	public:
		InstructionListElement();
		~InstructionListElement();
		
		InstructionType type;
		ListContainer<std::string> searchStrings;
		InstructionListElement * next;
		InstructionListElementPointerList * destinations;
	
};

class InstructionList
{
	public:
		InstructionList();
		~InstructionList();
		void addInstruction(std::string);
		InstructionListElement * getNextInstruction();
		InstructionListElement * getNextInstruction(int);
		void goToBeginning();
			
	private:
		
		InstructionListElement * firstInList; //this is just a list of statements that are in a computer structure form, they're not linked together in any kind of graph.
		InstructionListElement * lastInList;
		int instructionListLength;
		InstructionListElement * appendToInstructionList();
		
		
		InstructionListElementPointerList locationOfMostRecentIfStatement;
		
		InstructionListElement * lastInstructionReturned;
		
		/* add your private declarations */
};

#endif /* INSTRUCTIONLIST_HPP */ 
