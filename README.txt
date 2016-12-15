Title: Appeasing Mangicalla
Author:  Nathaniel Blair and Akshay Rachapudi

Description:  
You appear to have been summoned to the domain of Mangicalla, a powerful Wizard, against your own free will. 
He has need of someone to do his chores, clean up the trash in the rest of his house. 
Kill all small nuisances in his house and be rewarded for your efforts with the generous gift of your life... and maybe a little trreasure.

Players:
P- Player: This is you! Try to avoid taking damage from the enemies that plague Mangicallas mansion and complete your task as fast as possible.
M- Mangicalla: This is the lord of the manor. Talk to him when you feel your task is complete. Do not yo upset him... too much.
D- DustBunny: These little critters are everywhere. The dustbunnies in your house sure don't fight back when you try to clean them...
S- Spider: Creppy crawlers that will follow you around in the game. Try not to get cornered!

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

Use of Threads in a Meaningful way:
- Lines 47-68 main.cpp create a second thread that calculate an in game timer.
- This value is passed to game manager for update on the graphic update cycle.
- When the timer hits zero the game ends.

Use a Lambda Function in a Meaningful Way:
- The thread created for our timer has a lambda function passed in defining how the timer should be updated.
- Lines 47-68 main.cpp defines the lambda function.
- The sory function for A* also uses a lambda function.
- Pathfinder.cpp line 78.

Use a Smart Pointer in a Meaningful way:
- Our BoardManager instance in main.cpp now uses unique_ptr.
- Line 36 in main.cpp.

Three Design Patterns Used in Meaningful Ways:
1) Singleton Design Pattern: A class which only a single instance can exist
	a) See BoardManager.cpp, Player.cpp, and WindowController.cpp.

2) Model-View-Controller(MVC): Create separate units for the logic of the app, view into the app,
and how the user interacts with the app.
	a) The view for out app is defined explicitly in 2-3 print methods in boardmanager.cpp.
	b) The controller for the app is defined in main.cpp, it has a little logic about the 4-7 types of input
	   That are valid for the user.
	c) The logic is the rest of the app, but mostly controlled by BoardManager.cpp.

3) Facade: Define a higher-level interface that makes the subsystems easier to use.
	a) BoardManager: The class that exposes a high level interface for main.cpp to interact with.
	   Takes in a simple input into AttemptPlayerAction and the rest of the system is updated.

4) Private Class Data: Control write access to some class members to avoid corrupted class state.
	a) All classes use this paradigm, only expose the data members that need to be and usually
	   define an interface for checking/modifying values rather than directly allowing other
	   classes to mutate values.
