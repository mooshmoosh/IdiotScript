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

To do
-----

