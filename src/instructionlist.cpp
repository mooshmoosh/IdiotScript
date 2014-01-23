/*
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 * 
 */

#include <iostream>
#include "instructionlist.hpp"

using namespace std;

InstructionListElement::InstructionListElement() {
	type = UNDEFINED;
	next = NULL;
	destinations = NULL;
}

InstructionListElement::~InstructionListElement() {
	if(next!=NULL) delete next;
	if(destinations!=NULL) delete destinations;
}

InstructionListElementPointerList::InstructionListElementPointerList() {
	content = NULL;
	next = NULL;
}

InstructionListElementPointerList::~InstructionListElementPointerList() {
	if(next!=NULL) delete next;
}

InstructionList::InstructionList()
{
	firstInList = NULL;
	lastInList = NULL;
	instructionListLength = 0;
	lastInstructionReturned = NULL;
}

InstructionList::~InstructionList() {
	if(firstInList!=NULL) {
		delete firstInList;
	}
}

void InstructionList::addInstruction(std::string newInstruction) {
	InstructionListElement * parsedInstruction = appendToInstructionList();
	
	if(beginsWith(newInstruction,"search for ")) {
		parsedInstruction->type = SEARCH;
		parsedInstruction->searchStrings.append(cleanedSearchString(newInstruction.substr(LENGTH_OF_SEARCH_FOR_)));
	}
	else if(beginsWith(newInstruction,"copy till ")) {
		parsedInstruction->type = COPY;
		parsedInstruction->searchStrings.append(cleanedSearchString(newInstruction.substr(LENGTH_OF_COPY_TILL_)));
	}
	else if(beginsWith(newInstruction,"if you find ")) {
		parsedInstruction->type = CONDITIONAL_SEARCH;
		parsedInstruction->searchStrings.append(cleanedSearchString(newInstruction.substr(LENGTH_OF_IF_YOU_FIND_)));
		locationOfMostRecentIfStatement.pushListDown();
		locationOfMostRecentIfStatement.content = parsedInstruction;
		parsedInstruction->destinations = new InstructionListElementPointerList;
		parsedInstruction->destinations->content = parsedInstruction;
	}
	else if(beginsWith(newInstruction,"otherwise if you find ")) {
		locationOfMostRecentIfStatement.content->searchStrings.append(cleanedSearchString(newInstruction.substr(LENGTH_OF_OTHERWISE_IF_YOU_FIND_)));
		if(locationOfMostRecentIfStatement.content->destinations==NULL) {
			
		}
		locationOfMostRecentIfStatement.content->destinations->append(parsedInstruction);
	}
	else if(beginsWith(newInstruction,"then")) {
		InstructionListElementPointerList * p;
		for(p=locationOfMostRecentIfStatement.content->destinations;p!=NULL;p=p->next) {
			if(p->content->destinations==NULL) {
				p->content->destinations = new InstructionListElementPointerList;
				p->content->destinations->content = parsedInstruction;
			}
		}
		locationOfMostRecentIfStatement.popListUp();
	}
	else if(beginsWith(newInstruction,"repeat")) {
		parsedInstruction->type = REPEAT;
	}
	else return;
	
}

bool beginsWith(std::string& data, std::string test) {
	if (data.length() < test.length()) return false;
	
	for(int i=0;i<test.length();i++) {
		if(test[i]!=data[i]) return false;
	}
	
	return true;
}

void InstructionListElementPointerList::pushListDown() {
	InstructionListElementPointerList * tempOldNext = this->next;
	InstructionListElement * tempOldContent = this->content;

	this->next = new InstructionListElementPointerList;
	this->next->next = tempOldNext;
	this->next->content = tempOldContent;
	
	this->content = NULL;
}

void InstructionListElementPointerList::popListUp() {
	if(this->next==NULL) {
		this->content = NULL;
	}return;
	
	InstructionListElementPointerList * tempListElement = this->next;
	this->content = this->next->content;
	this->next = this->next->next;
	
	this->next->next = NULL;
	delete this->next;
}

void InstructionListElementPointerList::append(InstructionListElement * newPointer) {
	InstructionListElementPointerList * p;
	for(p = this;p->next!=NULL;p=p->next) {
			//this loop takes us to the end of the linked list, no code here
	}
	p->next = new InstructionListElementPointerList;
	p->next->content = newPointer;
}

InstructionListElement * InstructionList::appendToInstructionList() {
	if(firstInList==NULL) {
		firstInList = new InstructionListElement;
		lastInList = firstInList;
		instructionListLength++;
		return lastInList;
	}
	else {
		lastInList->next = new InstructionListElement;
		lastInList = lastInList->next;
		instructionListLength++;
		return lastInList;
	}
}
InstructionListElement * InstructionList::getNextInstruction() {
	return getNextInstruction(0);
}

InstructionListElement * InstructionList::getNextInstruction(int branch) {
	if(lastInstructionReturned==NULL) {
		lastInstructionReturned = firstInList;
		return lastInstructionReturned;
	}
	else if(lastInstructionReturned->destinations==NULL) {
		lastInstructionReturned = lastInstructionReturned->next;
		return lastInstructionReturned;
	}
	else {
		InstructionListElementPointerList * p;
		for(p = lastInstructionReturned->destinations;p!=NULL;p=p->next) {
			if(branch==0) {
				lastInstructionReturned = p->content->next;
				return lastInstructionReturned;
			}
			branch--;
		}
		lastInstructionReturned = lastInstructionReturned->destinations->content->next;
		return lastInstructionReturned;
	}
	
}

void InstructionList::goToBeginning() {
	lastInstructionReturned = NULL;
}

string cleanedSearchString(string rawString) {
	string result = "";
	for(int i=0;i<rawString.size();i++) {
		if(rawString[i]=='\\') {
			i++;
			switch(rawString[i]) {
			case 's':
				result+=" ";
				break;
			case 'n':
				result+="\n";
				break;
			case '\\':
				result+="\\";
				break;
			}
		}
		else {
			result+=rawString[i];
		}
	}
	
	return result;
}
