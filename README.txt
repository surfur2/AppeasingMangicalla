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
X- Pathing for spiders: If you want to know where the spiders are going next, follow the X.

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
A* Algorithm

A* is a heuristic search technique used to find the find the best way with the least cost.
The basic equation is f(n) = g(n) + h(n).
f(n) is the heuristic value to reach the destination from n.
g(n) is the cost to reach from start to n.
h(n) is the cost to reach the destination from n.

We used a 2D array of struct tiles that stores f, g and h value for each tile. This struct also has a variable that stores the preceeding tile in path.

In our implementation, we used 3 stacks:
1) open stack - that stores all the tiles in consideration and is sorted in decreasing order of f value.
2) closed stack - that stores all the tiles that have been considered
3) path stack - that stores the final path

Implementation:
- Starting from the current position, we push the current position in open at initialize.
- We start by popping the tile with the least f value (i.e. the top of the stack)
- Then we check if this tile is in closed stack. It it is in closed stack then check if the f value of the tile in closed stack is more than the f value currently. If it is more, then delete the copy in closed stack and push this tile, otherwise, disregard this tile.
- Next, we check the 4 directions (Up, down, left and right) of movement from the current tile.
	- Check if movement is possible and then add the tile in open if it does not exist in open already. If it does exist in open already then compare the f value. If f value in open is greater then delete the copy in open and add this tile otherwise discard the current tile.
- We loop to step 2 and pop the top tile in open and continue this process till the end tile is found in closed stack.
- Now using the end tile structure to get its preceeding tile and looping this process of getting the preceeding tile till we reach start, we get the whole path which is stored in the path stack.


##########################################

Working stack - Have used structs for stacks and all the implementation is in the PathFinder

Also, the solution has code for a TEMPLATE STACK that was causing runtime memory access issues.