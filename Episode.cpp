#include "Episode.h"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
*/
Episode::Episode(string data[5], int new_rating, int new_season, int new_episode_num):Video(data)//Data has this info id,name,genre,initial_letter,length; rating for the episode, season number and episode number is given
{
    rating=new_rating;
    season=new_season;
    episode_num=new_episode_num;
}
Episode::Episode(string data[5],int new_rating):Video(data)//Constructor for operator
{
    rating=new_rating;
}
Episode::~Episode()
{

}
int Episode::getSeason()//Returns season
{
    return season;
}
int Episode::getEpisodeNumber()//Returns episode_num
{
    return episode_num;
}
void Episode::setEpisodeNumber(int new_episode_num)//Changes episode_num
{
    episode_num=new_episode_num;
}
void Episode::setSeason(int new_season)//Changes season
{
    season=new_season;
}
string Episode::toString()//Returns al info of the episode
{
    string msg;
    msg="Title:\t\t"+name+"\n";
    msg+="ID:\t\t"+ID+"\n";
    msg+="Genre\t\t"+genre+"\n";
    msg+="Lentgh:\t\t"+to_string(length)+" min\n";
    msg+="Season:\t\t"+to_string(season)+"\n";
    msg+="Episode:\t"+to_string(episode_num)+"\n";
    return msg;
}
int Episode::getRating()//Returns rating
{
    return rating;
}
void Episode::setRating(int new_rating)//Changes rating
{
    rating=new_rating;
}
string Episode::display()
{
    string msg="Title:\t"+name;
    msg+="\nRating:\t"+to_string(rating);
    return msg;
}