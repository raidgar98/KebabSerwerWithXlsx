# Simple TCP Serwer with raport generation

FIRST:

In this project i use this library:

	https://github.com/dbzhang800/QtXlsxWriter

for generating report and tcpserwer i made, using toutrial of VoidRealms

	https://www.youtube.com/watch?v=zMgbVN3uQ-E

So i want to thank you. I don't know how to contact them to ask about license header or to say thank you so if u see this plesae contact me (bottom) :)

This is first part of whole project which consist of this serwer and mobile app, also written in Qt (QML).

Serwer works really easly, it's waititng for connection from mobile app and when it's established
serwer waits for CSV like file with data of recent orders from mobile app. Connection is closed when file is ready. After that file is converted into SQL querries (by engine i created in another project SQLSerialGenerator) and sent to local SQLite database. This is the first function of this program. Second is generating reports, which allows to create reports in Excel format '.xlsx'. Only think user have to do is selecting directory, where raport should be created and select date. In the report generation dialog you can change actual default prices that is load from same database. 

Thinks To Do with Highest Priority:

	- Add missing comments

	- Change name of varriables and methodes

	- Export some strings into varriables

	- Solve problem of name translation (very long switches, that only translate dish names from short ones to human friendly ones)

	- Solve problem of GUI translation (now it's only in Polish)



Things To Do with Normal Priority:

	- Add encryption to transfer now it's plain text

	- Change communication between app and serwer, now is some tomporary strings, that are too long with no reason

	- Add logs of deleted orders



Things To Do with Lowest Priority

	- Test Serwer during long work time

	- Improve Layout (make suprises during resize)


I know there is a lot of work to do, but now i am studying and i don't have a lot of time to improve quality of this project.

Instruction for setup:

	- Import all files to new project in Qt
	
	- Add QXlscWriter library as author says. I done this by second option, and i recommend this, but if u want first option remember to change #include directives from "" to <> 

	- I use QStandardPaths, so in your Download Folder create SQLite database that name is: 'allOrders'

	- Next in this database execute following commands

		
		CREATE TABLE orders
			(
			orderID INTEGER PRIMARY KEY AUTOINCREMENT,
			dishName varchar,
			dishSouce int(3),
			extraMeat tinyint(1),
  			extraSalad tinyint(1),
			extraFries tinyint(1),
			extraCheese tinyint(1),
			otherExtras tinyint(1),
			takeAway tinyint(1),
			isComplete tinyint(1),                                                                                	orderDateTime datetime
			);



		CREATE TABLE prices(name varchar, val decimal);

	- Now you have to add execute addAllPrices.sql . 

	- When you set this up make sure this database have proper permissions for read and write

	- If u are Windows user and have some errors when program tries to save or write into sqlite database try to change slashes into backslashes in paths.

	- Now everythink should work, so you can try to run this.

	- If u want to test it u have to insert some values on your own, 
		and keep names that are build in program, or download mobile app (it can be run on 
		desktop as well) and generate some data by simply clicking on avaiable dishes.



This is how it works:

![Presentation](https://raw.githubusercontent.com/raidgar98/KebabSerwerWithXlsx/master/HowSerwWork.mp4)


All bugs or advices you can send here:

	raidgar98@onet.pl

with title

	[GitHub] KebabSerwerWithXlsx

So my mail can filter it from SPAM and move it to right folder :)
