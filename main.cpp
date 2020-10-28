#include "Platform.cpp"
#include "Episode.cpp"
#include "Movie.cpp"
#include "Series.cpp"
#include "Video.cpp"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
It creates a platform, runs the menu and destroys it
This is the cpp file to run 
It's meant to be run in g++, as repl.it has failed me, again (◡﹏◡✿)
Here's the link to the repl.it, but it crashes for some reason:
https://repl.it/@diegs117/Final-Project-OOP-The-real-Final-one
To be honest, I don't find why, when I run it here in the same conditions, it does not show an error message at the end, like it does in replit
Maybe it's an issue with the destructor idk (◡︿◡✿)

In another note, I implemented some basic string similarity checker in series.cpp
Nothing that impresive, but it's better than having to write the anme of the Episodes exactly as they are registred, now they don't have to be capitalized, and there's some space for typos, not excesive, one maybe two if the name is long enough
This is the last addition, I'm pretty sure.
Sorry for making such a long code, I tried to comment it as best as I could if you were to read every single line
*/
using namespace std;
int main()
{
    Platform* p=new Platform();//Create a platform
    p->menu();//Call the menu
    p->~Platform();//Destroy it
    return 0;
}