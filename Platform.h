#include "Movie.h"
#include "Series.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#ifndef __PLATFORM
#define __PLATFORM
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
Base of the project, it can search, rate and create Movies, Series and Episodes.
Displays a menu for the user with all the possible options
It has an extended menu with all the extras I added to the project
*/
class Platform
{
    public:
        Platform();//Constructor
        ~Platform();
        void createVideos(string file_name);//From a csv file, creates videos and movies
        void showSeriesEpisodes(int index);//Shows the episodes for a series with index 
        void showAllSeriesEpisodes();//Displays the episodes of all series
        void showMovies();//Shows all movies
        void showAll();//Shows every video in the platform
        void showAlphabet();//Shows the series and movies title and rating in alphabetical order
        void selectSeries();//Shows all series with an index, you can choose one and it will show all it's episodes
        void selectSomething();//Shows all series and movies with an index, you can choose one and it will display all the video information
        void showGenre(string searched_genre);//Shows all the VIDEOS from a specific genre
        void showRating(int searched_rating);//returns the info of all videos with a specific rating
        void showVideoByFilter();//Ask the users if they want to know of the video sof a specific genre or rating, then ask waht that specific condition is and then calls the specific function
        void showSeriesRatingEpisodes();//Display all series, asks the user to select one, to select a rating and displays all episodes with said rating
        void showMoviesInRating();//Asks the user for a rating, and then show all movies with said rating
        void rateAVideo();//Ask the user of she/he wants to rate a movie or a series, it displays mvies/series and ask for the new rating if it's amovie, if it's a series asks if she/he wants to rate the whole series or just and episode, if it's an episode, it calls the series function, if it's the whole series, it changes the series general_rating
        void loadFile();//Ask the user for a file name or reads the included file
        void createMedia();//Asks the user for info to create a movie or series and cretae its, then it'll add it to a cdv file
        void menu();//Opens a menu
    protected:
        vector <Movie*> all_movies;//Where i store all movies
        vector <Series*> all_series;//Where i store all series
        int num_series;//Total number of series
        int num_movies;//total number of movies
        bool file_read;//Remembers if i have read a file, becuase the user has the option to load the file
        vector <string> already_read_files;//Vector that stores all the files that have been read, so I can give prevent content duplication, at the end, the user will be notified and given the option to read the file again, so it's the users decision, not a bug
};
#endif