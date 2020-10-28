#include "Video.h"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
*/
Video::Video(string data[5])//Data will have id,name,genre,initial_letter,length
{
    ID=data[0];
    name=data[1];
    genre=data[2];
    initial_letter=data[3];
    length=stod(data[4]);
}
Video::~Video()
{

}
string Video::getID()//Returns the ID
{
    return ID;
}
string Video::getName()//Returns the name
{
    return name;
}
string Video::getGenre()//Returns the genre
{
    return genre;
}
double Video::getLength()//Returns length
{
    return length;
}
string Video::getInitialLetter()//Returns initial_letter
{
    return initial_letter;
}
string Video::display()//Returns a string with the name of the video
{
    string msg="Title: "+name;
    return msg;
}
int Video::getRating()//returns 0
{
    return 0;
}