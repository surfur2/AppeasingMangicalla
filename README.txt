Title: Appeasing Mangicalla
Author:  Nathaniel Blair (I was the only group of one)

Description:  
You appear to have been summoned to the domain of Mangicalla, a powerful Wizard, against your own free will. 
He has need of someone to do his chores, clean up the trash in the rest of his house. 
Kill all small nuisances in his house and be rewarded for your efforts with the generous gift of your life... and maybe a little trreasure.

Players:
P- Player: This is you! Try to avoid taking damage from the enemies that plague Mangicallas mansion and complete your task as fast as possible.
M- Mangicalla: This is the lord of the manor. Talk to him when you feel your task is complete. Do not yo upset him... too much.
D- DustBunny: These little critters are everywhere. The dustbunnies in your house sure don't fight back when you try to clean them...

System Requirements:
1) This game was built for Windows systems specifically. It counts on DOS, Windows 3.x, Phar Lap, DOSX, OS/2, or Win32 C compilers being present to run.
   There are no guarantees that the game will work correctly on Mac OS or Linux based systems.
2) Built for a 32 bit operating system, but should work on 64 bit as well.

Instructions for Play:
1) Unpack .zip folder to desired destination.
2) Enter the 'Release' folder.
2) Make sure that parameters.txt and Inntroduction.txt are in the same folder as the executable.
3) Double click on AppeasingMangicalla.exe to run.
4) Optional: If the project fails to open, it may because not all of your dependancies in visual studio are up to date.
Right click the project in visual studio solution explorer and click "update visual studio with necessary tools".


Notes on Grading:
One of the requirments for this project was to use the Big Three somewhere in the class structure. 
However, the big three include both the copy constructor and the copy assignment operator.
It was an intentional design desision of the game to have very tight managment of the objects being used, no dublicates of objects was desired.
You will notice that most of the classes either use:
a) A singleton architecture, enforcing that only one instance is ever allowed to be instantiated.
b) Are a member of BoardManager, whcih wants to manage exactly which objects are instantiated and keep the only reference to them.

For this reason, creating a copy construcot and an copy assignment operator on any of my classes was agains the architecture I was trying to enforce.
Furthermore, I would argue this was not necessarily a negative approach to take. It should lead to faster code that has a lower chance of a memory leak.

However, I have created both in BoardManager, to show I am not trying to skirt a requirment. They are both private members so that there would be no confusion to actually use them.
If it was my choice, I would have intentionally not created any copy constrctors or copy assignment operators.

If this takes away from my overall grade I accept that, however one of my personal goals of this course is to learn better practices on software development. 
Any comments on where or how I could or should have used them would be much appreciated, as well as and overall comments on the structure of my code.

Bonus Points:
1)As mentioned above, singletons were intentionally used in many of the classes to make sure a user of the code could only every have one 'source of truth' for the state of the game.
This is an object-oriented design pattern.
2) Factory architecutre was used for creating the singletons. Only the intended parts of the instance were exposed as public methods in the header file.
Another object-oriented design pattern.
3) While the save functionality was not included in the scope, all of the necessary architecture is there. The objects are serialized from a map in a file,
and the process could easily be reversed to write the current state of a file.
I dont know if this is enough for bonus points... but I am really proud of how well the system turned out.
