IdiotScript
===========
Two sentence description
------------------------
Every time I need to use regular expressions to create tables of data from webpages I have to re-watch [this](http://www.youtube.com/watch?v=EkluES9Rvak) 50 minutes video tutorial because I can never remember them. Now idiots like me everywhere can use IdiotScript instead!

Possible applications
---------------------
You have webpages like [this](http://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_National_Pok%C3%A9dex_number). The data we're after is split into several tables, with information in between. We know what comes before and after each snippet of data we want, but copying and pasting the tables into excel also coppies a whole bunch of formatting, and the data is still split up.

Given a webpage containing many hyperlinks, you want to extract all the links that are on images, not just on text.

Examples
--------
Many people complain about reddit's layout being confusing. If you copy and paste a whole thread into a text file, the following script will put into a linear table, the first collumn is the user, the second is what they say. This makes AMAs much easier to read. _Note_ the second line has two spaces after the word "till".

	search for [–]
	copy till  
	search for ago\n
	copy till \npermalink
	repeat

Consider [this](http://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_National_Pok%C3%A9dex_number) webpage mentioned earlier. The following script will convert the page into a nice csv file.

	`search for <td style="font-family:Monospace;"> #`
	`copy till \n</td>`
	search for <td style="font-family:Monospace;"> #
	copy till \n</td>
	search for " src="
	copy till " width="32" height="32" />
	search for <a href="/wiki/
	search for " title="
	search for ">
	copy till </a>

	if you find <td colspan="1" style="background:#
	search for <a href="/wiki/
	search for " title="
	copy till  
	search for <td style="background:#
	search for <a href="/wiki/
	search for " title="
	search for "><span style="color:#
	search for >
	copy till </span>

	otherwise if you find <td colspan="2" style="background:#
	search for <a href="/wiki/
	search for " title="
	search for "><span style="color:#
	search for >
	copy till </span>

	then
	repeat
    
Store the script in *script.is* and the HTML source of the webpage in *source.txt* then run
	
	idiotscript script.is source.txt >> output.csv
    
The rows representing pokemon with more than one type will have two cells for their type, and be one column longer.
    

About the code
--------------
The interpreter starts at the beginning of the source file, and applies each instruction in the script in turn. The variable textPointer (member of the textEater class) represents how far along the source file the interpreter is.
- search for <something>
	- searches for the next instance of <something> and continues from the end of <something>
- copy till <something>
	- copies all the text from textPointer up till <something> then continues from the end of <something>
- ff you find <something>
	- Searches for the next instance of <something> just like 'search for'
	- The interpreter then continues executing until the next 'otherwise if you find' instruction
- otherwise if you find <something>
	- Just like 'if you find'
	- You can have a bunch of 'if you find', 'otherwise if you find' blocks, the <something> that comes first after textPointer is the one that will be executed. All others are ignored.
	- these if statements *can* be nested.
- then
	- Indicates the end of a set of 'if you find' blocks.
- repeat
	- Optional. The interpreter goes back the the start of the script and continues until it gets to the end of the source file. Without it, then only one row of data will be extracted.

You can run unit tests to see if you've broken anything with `make check` in the root directory.

You can check for memory leaks with valgrind with `make check_memory`.

Originally my purpose for writing this was for parsing tables of data I'd copied of websites. I was using it with a datamining application written in C++. If you want to add IdiotScripting to your C++ application you can do something like the following

	#include "texteater.hpp"
	...
	TextEater processor("script.is");
	processor.generateTableFromFile("input_data.txt");

The element in row *i*, column *j* of the generated table is a std::string which can be accessed with 

	processor.getElement(i,j);
	
Alternatively, you can run

	make idiotscript
	
to compile the main binary. Then you can run commands like the following from the command line

	idiotscript script.is source.txt >> output.csv

to generate a table that Microsoft Excel can read. We all know, that even if we use the most advanced database software in the world, 99% of real work gets done in Excel.
	
Slowly over time I plan on cleaning up the code when ever I feel like it. If you like the idea behind this project, or want to complain about my code at all please feel free to email me any time. If you have anything you want to add let me know, and I'll totally give you write access.

To do
-----
- I'm planning on writing a version of this in javascript. Since javascript is dynamic, the code will look much nicer. This would mean I could get rid of the ugly switch case in the TextEater.executeInstruction() function. I would like the instructions to be virtualised, and all subclasses of a genericInstruction class. I started writing it that way several times and each time wasn't convinced it was any easier to understand. I think it will work better in javascript.
- There is a class named InstructionList, I would like to replace it with a ListContainer<> object like I've done throughout the rest of the code.

