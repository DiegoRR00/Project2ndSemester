#include <iostream>
using namespace std;
#ifndef __VIDEO
#define __VIDEO
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
This is the base class for Movie and Episode, it has ID, name, length, initial letter and genre, it's an abstract class
*/
class Video
{
    public:
        Video(string data[5]);//Data will have id,name,genre,initial_letter,length
        ~Video();
        string getID();//Returns the ID
        string getName();//Returns the name
        string getGenre();//Returns the genre
        double getLength();//Returns length
        string getInitialLetter();//Returns initial_letter
        virtual string display();//Returns a string with the name of the video
        virtual string toString()=0;//Returns a string with the data of the video
        virtual int getRating();//returns 0
    protected:
        string ID;//ID for video
        string name;//Video Name
        string genre;//Genre of the video
        double length;//Length of the video
        string initial_letter;//First letter of the title
};

#endif