Color-Game
==========

Color Game Using C++/CLI, MFC


SDI Document/View App help from:
http://www.scribd.com/doc/29336159/06-Introduction-to-Mfc
http://www.scribd.com/doc/7124911/Visual-Cpp-and-MFC-Programming
http://aclacl.brinkster.net/MFC/ch09c.htm
http://msdn.microsoft.com/en-us/library/ms821625.aspx
http://msdn.microsoft.com/en-us/library/6w6cd538(v=vs.80).aspx
http://www.functionx.com/visualc/howto/calldlgfromsdi.htm
Changes made to the 1999 "Programming Windows with MFC" SDI Square Color application:
Part 1: Added a random number generator to pick a number 1-6 and call the respective color function to get that color back to the OnLButtonDown function which changes the color of the specified box by getting it's x and y positions. Also the original tutorial never calls the different functions for colors, that is why I was getting only one color at first. (part 1 is commented out, as I changed the way the program works)
Part 2: When a box is clicked, the user is asked to choose a color of the box, which changes the color of the box to the specified color.
Game Rules inspired by:
http://www.colormatchgame.com/default.asp
http://powayusd.sdcoe.k12.ca.us/teachers/smiddleton/Geo/Proofs/Colored%20Square%20Game.htm
Note: Rules of the game can be found by clicking Help ~> How To Play 
