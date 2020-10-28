#include "Platform.h"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
*/
int checkInt(string value)//I receive a string and eveluate if it contains a number, if I raturn 0 is because it was 0, if i return -1, it was not a number, if i return -2 it was negative, if i return anything else, thats the value fo the string in int form
{
    if (value=="0")//If they gave ma a zero
    {
        return 0;
    }
    else//IF its not zero
    {
        if (atoi(value.c_str())==0)//When you use atoi in a string that does not contain a number, it returs 0
        {
            
            return -1;
        }
        else//If it's a number
        {
            int number=stoi(value);//Assign the value to an int
            if (number<0)//If it's negtive
            {
                return -2;
            }
            else //If not
            {
                return number;
            }
        }
    }
}
string checkString(string value)
{
    if (value=="")//If it's blank
    {
        return "_empty_";
    }
    else
    {
        bool only_spaces=true;//Bool if ture means there's only " " inside the string
        for (int i=0;i<value.size();i++)//For each element of the string
        {
            if (value[i]!=' ')//If the elements different to ' ', because the elements of a string are char
            {
                only_spaces=false;//Theres somethig that's not a space 
            }
        }
        if(only_spaces)//If there was only spaces
        {
            return "_blank_";
        }
        else//If there was something else
        {
            return value;
        }
    }
}
string createID(string name)
{
    stringstream stream_line(name);//Create a stringsetrame of the name
    string word, ID;//A word, and where to store my ID
    int counter=0,number_words=0;//Counter and number of words in name
    while (getline(stream_line,word,' '))//While getting words
    {
        number_words++;//Add to the number of words
    }
    if (number_words==1)//IF it only has one word
    {
        ID=name+"_1";//add _1 to the name to make and ID, example Shrek -> Shrek_1
    }
    else//If it has more
    {
        ID="";//Start the ID variable
        stringstream stream_line_2(name);//Create a second stringstream because the other one has been read
        while (getline(stream_line_2,word,' '))//While i can get words
        {
            ID+=word;//Add the word
            counter++;//Updtae counter
            if (counter!=number_words)//If the caounter is differente to the total number of words
            {
                ID+="_";//add _ to the ID,theres an if because my ID don't end in _, example Love Live->Love_live, not Love_live_
            }
            
        }
    }
    return ID;
}
Platform::Platform()//Constructor
{
    file_read=false;
    num_movies=0;
    num_series=0;
}
Platform::~Platform()
{

}
void Platform::createVideos(string file_name)//From a csv file, creates videos and movies
{
    vector <string>::const_iterator file_iterator;//Iterator
    bool repeated_file=false;//Indicates if the file has been read before
    bool read_file=true;//Indicates if the file shall be read
    for (file_iterator=already_read_files.begin();file_iterator!=already_read_files.end();++file_iterator)//For each file name
    {
        if ((*file_iterator)==file_name)//If the file name is the same
        {
            repeated_file=true;//Indicate it has been read already
        }
    }
    if (repeated_file)//If the file is a repeated one
    {
        bool valid_input=true;//Bool for while
        string input;//Variable for user input
        while (valid_input)
        {
            //Notify the user this file has been read
            cout<<"This file has been read already, if you read this file again, all of its contents will be duplicated"<<endl<<"If you want to add new content, I recomend using the create series or movies option in the menu"<<endl<<"If you want to read the file anyways, press 1\nIf you don't want to read the file press 2"<<endl;
            cin>>input;//receive input
            if (input=="1")//If they want to read it anyways
            {
                valid_input=false;//Stop while
            }
            else if (input=="2")//If they don't want to read it
            {
                valid_input=false;//Stop while
                read_file=false;//Indicate the file will not be read
                cout<<"File reading canceled"<<endl;//Notify the user
            }
            else
            {
                cout<<"Invalid input, try again"<<endl;//Notify the user
            }
        }
    }
    else//If it's a new file
    {
        already_read_files.push_back(file_name);//Add it to the list
    }
    if (read_file)//if I shall read the file
    {
        char delimiter=',';//Comma for the csv
        ifstream info_file;//M/S, ID, name, genre, length, episode title, season episode
        info_file.open(file_name);//Open file
        string line, word;//Create variables to store file input
        vector <string> movie_lines;// a vector to store the lines of the file containing movie info
        vector <string> series_lines;//A vector to stre lines in the file containing series info
        vector <string>::const_iterator movie_iterator;
        vector <string> :: const_iterator series_iterator;
        if (info_file.is_open())//if the file opened
        {
            while (getline(info_file,line))//read the number of lines
            {
                if (line[0]=='M')//If the first character is a M, it's a movie
                {
                    num_movies++;//Add one movie to the count
                    movie_lines.push_back(line);//add the line to the vector for movie lines
                }
                else if (line[0]=='S')//If not, it could be a series, I do not use else because theres a chance there-s a line not meant to be a video, for example the fisrt line which shows the order of inFormation
                {
                    
                    series_lines.push_back(line);//add the line to the vector for series lines
                }   
            }
            info_file.close();
            //Create all my movies
            string data[5];
            for (movie_iterator=movie_lines.begin();movie_iterator!=movie_lines.end();++movie_iterator)
            {
                stringstream stream_line((*movie_iterator));//Create a string stream so tou can go more easily thorugh the string
                getline(stream_line,word,delimiter);//Get the first velue (M)
                getline(stream_line,word,delimiter);//Get the ID
                data[0]=word;//Add it to the data array
                getline(stream_line,word,delimiter);//Get name
                data[1]=word;//Add it to the data array
                string first_letter(1,word[0]);//Get the fisrt letter of the title
                getline(stream_line,word,delimiter);//Get genre
                data[2]=word;//Add it to the data array
                data[3]=first_letter;//Add the fisrt letter to the array
                getline(stream_line,word,delimiter);//Get length
                data[4]=word;//Add it to the data array
                getline(stream_line,word,delimiter);//Get rating
                int rating=atoi(word.c_str());//I save the rating
                getline(stream_line,word,delimiter);//Get Episode name
                getline(stream_line,word,delimiter);//Get Season
                getline(stream_line,word,delimiter);//Get Episode number
                getline(stream_line,word,delimiter);//Get Year
                int year=atoi(word.c_str());//Save the year
                getline(stream_line,word,delimiter);//Get Budget
                all_movies.push_back(new Movie(data,rating,year,atoi(word.c_str())));//Give the movie the data I've recolected and the rating which is in word momentarely
            }
            //Create series
            vector <string> one_series_lines;
            vector <string> :: const_iterator one_series_iterator;
            one_series_lines.push_back(series_lines[0]);//Add the first one
            string last_id, current_id, series_name, series_genre;
            int total_seasons=0, episodes_per_season=0, year=0, budget=0;
            int lines_read=0;//Count the numver of lines read
            for (series_iterator=series_lines.begin();series_iterator!=series_lines.end();++series_iterator)
            {
                if (one_series_lines.size()==1)//A new series is starting
                {
                    stringstream stream_line(one_series_lines[0]);
                    getline(stream_line,word,delimiter);//Get S
                    getline(stream_line,word,delimiter);//Get ID
                    last_id=word;//Get the last word of this series
                }
                stringstream stream_line((*series_iterator));
                getline(stream_line,word,delimiter);//Get S
                getline(stream_line,word,delimiter);//Get ID
                current_id=word;//Get the ID of this episode
                if (current_id==last_id && lines_read!=0)//If the Id matches and it isn't the first series line, because it was added before the for
                {
                    one_series_lines.push_back((*series_iterator));//Add this line to the series
                }
                if (lines_read+1==series_lines.size() || current_id!=last_id)//If it doesn't ot it's the last line, then the series has ended
                {
                    //Create series
                    num_series++;//Add one series to the count
                    //Get the last season and episode number
                    stringstream last_line(one_series_lines.back());
                    getline(last_line,word,delimiter);//Get S
                    getline(last_line,word,delimiter);//Get ID
                    getline(last_line,word,delimiter);//Get name
                    series_name=word;//Save the name of the series
                    getline(last_line,word,delimiter);//Get genre
                    series_genre=word;//Save the genre of the series
                    getline(last_line,word,delimiter);//Get length
                    getline(last_line,word,delimiter);//Get rating
                    getline(last_line,word,delimiter);//Get episode title
                    getline(last_line,word,delimiter);//Get season
                    total_seasons=stoi(word);//Save the number of seasons
                    getline(last_line,word,delimiter);//Get last episode
                    episodes_per_season=stoi(word);//Save the number of episodes per season
                    getline(last_line,word,delimiter);//Get Year
                    year=atoi(word.c_str());//Save the year
                    getline(last_line,word,delimiter);//Get Budget
                    budget=atoi(word.c_str());//I save the budget
                    //Recolect episode names, lengths and rating
                    string episodes_names[total_seasons*episodes_per_season];//Where to store the episode names for the series constructor
                    double episodes_lengths[total_seasons*episodes_per_season];//Where to store the episode lengths for the series constructor
                    int episodes_rating[total_seasons*episodes_per_season];//Where to store the episode ratings for the series constructor
                    int episode_counter=0;
                    for (one_series_iterator=one_series_lines.begin();one_series_iterator!=one_series_lines.end();++one_series_iterator)
                    {
                        //M/S, ID, name, genre, length, rating, episode title, season, episode
                        
                        stringstream stream_line((*one_series_iterator));//Create a string stream so tou can go more easily thorugh the string
                        getline(stream_line,word,delimiter);//Get S
                        getline(stream_line,word,delimiter);//Get ID
                        getline(stream_line,word,delimiter);//Get series_name
                        getline(stream_line,word,delimiter);//Get genre
                        getline(stream_line,word,delimiter);//Get length
                        episodes_lengths[episode_counter]=stod(word);//Add length to the array
                        getline(stream_line,word,delimiter);//Get rating
                        episodes_rating[episode_counter]=stoi(word);//Add rating to the array
                        getline(stream_line,word,delimiter);//Get episode title
                        episodes_names[episode_counter]=word;//Add title to the array
                        //The other two dont matter anymore
                        episode_counter++;//Go to the next episode
                        
                    }
                    //Create series
                    all_series.push_back(new Series(total_seasons,episodes_per_season,series_name,episodes_names, series_genre,episodes_lengths,episodes_rating,last_id,year,budget));
                    one_series_lines.clear();//Empty one_series_lines vector
                    one_series_lines.push_back((*series_iterator));//push back this line   
                }
                last_id=current_id;//Change the ID
                lines_read++;//Updtae read_lines
            }
            file_read=true;
            cout<<"File read succesfully"<<endl;//Notify i read the file
        }
        else
        {
            cout<<"Information file not found"<<endl;
        }
    }
}
void Platform::showSeriesEpisodes(int index)//Shows the episodes for a series with index 
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
    }
    cout<<all_series[index]->displayGeneralInfo()<<endl<<all_series[index]->display()<<endl;//Display the name and rating, an then all episodes
}
void Platform::showAllSeriesEpisodes()//Displays the episodes of all series
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    cout<<"Series:"<<endl;//Indicate we're seeing series
    vector <Series*>::const_iterator series_iterator;//Iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        cout<<(*series_iterator)->displayGeneralInfo()<<endl<<(*series_iterator)->display()<<endl;//Display the name and rating, an then all episodes
    }
}
void Platform::showMovies()//Shows all movies
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    cout<<"Movies"<<endl;//Indicate we're seeing movies
    vector <Movie*>::const_iterator movie_iterator;//Iterator
    for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
    {
        cout<<(*movie_iterator)->display()<<endl;//Display name and rating
    }
    cout<<endl;
}
void Platform::showAll()//Shows every video in the platform
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    vector <Video*> all_videos;//Vector to use polymorphism
    vector <Movie*>::const_iterator movie_iterator;//Iterator
    for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
    {
        all_videos.push_back((*movie_iterator));//Add all movies to the vector for polymorphism
    }
    vector <Series*>::const_iterator series_iterator;//Iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        for (int s=0;s<(*series_iterator)->getSeason();s++)//For each season in this series
        {
            for (int e=0;e<(*series_iterator)->getEpisodes();e++)//For each episode in each seson fo this series
            {
                all_videos.push_back((*series_iterator)->getEpisode(s,e));//Add the episodes to the vector for polymorphism
            }
        }
    }
    vector <Video*>::const_iterator video_iterator;//Iterator
    for (video_iterator=all_videos.begin();video_iterator!=all_videos.end();++video_iterator)//For each video in the vector for polymorphism
    {
        cout<<(*video_iterator)->display()<<endl;//Use display method
    }
    cout<<endl;
}
void Platform::showAlphabet()//Shows the series and movies title and rating in alphabetical order
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    string alphabet[27]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};//All letters
    string alphabet_min[27]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};//All letters in miniscules
    bool letters_printed[28];//To remember the letters i have printed
    bool series_printed[num_series];//To remember which series i have printed
    bool movies_printed[num_series];//To remember which movies i have printed
    for (int a=0;a<28;a++)
    {
        letters_printed[a]=true;
    }
    for (int s=0;s<num_series;s++)//Fill with true series_printed
    {
        series_printed[s]=true;
    }
    for (int m=0;m<num_movies;m++)//Fill with true movies_printed
    {
        movies_printed[m]=true;
    }
    for (int a=0;a<27;a++)//For all letters
    {
        for (int s=0;s<num_series;s++)//Check all series
        {
            if (alphabet[a]==all_series[s]->getInitialLetter() || alphabet_min[a]==all_series[s]->getInitialLetter())//If the lleter is the same or the same in miniscule
            {
                if (letters_printed[a])//If the lleter has not been printed
                {
                    letters_printed[a]=false;//Remember it
                    cout<<alphabet[a]<<endl;//Print it
                }
                cout<<all_series[s]->displayGeneralInfo()<<endl<<endl;//Display it
                series_printed[s]=false;//Remeber it's already printed
            }
            
        }
        
        for (int m=0;m<num_movies;m++)//Check all movies
        {
            if (alphabet[a]==all_movies[m]->getInitialLetter() || alphabet_min[a]==all_movies[m]->getInitialLetter())//If the lleter is the same or the same in miniscule
            {
                if (letters_printed[a])//If the lleter has not been printed
                {
                    letters_printed[a]=false;//Remember it
                    cout<<alphabet[a]<<endl;//Print it
                }
                cout<<all_movies[m]->display()<<endl<<endl;//Display it
                movies_printed[m]=false;//Remember it has been displayed
            }
        }
    }   
    for (int s=0;s<num_series;s++)//For all series
    {
        if (series_printed[s])//If it wasn't printed
        {
                if (letters_printed[27])//If the ? symbol has not been printed before
                {
                    letters_printed[27]=false;//remember it
                    cout<<"?"<<endl;//Print it
                }
                cout<<all_series[s]->displayGeneralInfo()<<endl<<endl;//Print it
                series_printed[s]=false;//Change value
        }
    }
    for (int m=0;m<num_movies;m++)//For all movies
    {
        if (movies_printed[m])//If it wasn't printed
        {
                if (letters_printed[27])//If the ? symbol has not been printed before
                {
                    letters_printed[27]=false;//remember it
                    cout<<"?"<<endl;//Print it
                }
            cout<<all_movies[m]->display()<<endl<<endl;//Print it
            movies_printed[m]=false;//Change value
        }
    }
}
void Platform::selectSeries()//Shows all series with an index, you can choose one and it will show all it's episodes
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    int counter=1;//Index to select seasons
    vector <Series*>::const_iterator series_iterator;//Iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        cout<<"["<<counter<<"] "<<(*series_iterator)->displayGeneralInfo()<<endl<<endl;//Display counter and name with rating
        counter++;
    }
    cout<<endl<<"Type the number in brackets for the series you want to see all the episodes:"<<endl;//Ask the user to input the counter for the movie they want to see
    bool invalid_input=true, is_valid_number=false;//Bool for while and to indicate it's a number
    string input;//Variable for input
    int index;//Variable for the index inside the vector
    while (invalid_input)
    {
        cin>>input;//Ask for input
        for (int n=1;n<+num_series+1;n++)//For each possible answer +1 because the counter started in 1 and the index start at 0
        {
            if (input==to_string(n))//If input is the same as a possible answer
            {
                is_valid_number=true;//Enable the display part of the code
                invalid_input=false;//Stop while
                index=stoi(input);//Transform input to int
                index--;//Minus one because index are one less than the counter
                n=+num_movies+1;//Stop for
            }
        }
        if (is_valid_number)//If it was a valid number
        {
            showSeriesEpisodes(index);//I call the function made for this
        }
        else//If it's was not a valid number, notify the user
        {
            cout<<"Invalid input, try again"<<endl;
        }
    }

}
void Platform::selectSomething()//Shows all series and movies with an index, you can choose one and it will display all the video information
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    int counter=1;//Index to select seasons
    vector <Movie*>::const_iterator movie_iterator;//Iterator
    for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
    {
        cout<<"["<<counter<<"] "<<(*movie_iterator)->display()<<endl<<endl;//Display counter and name with rating
        counter++;
    }
    vector <Series*>::const_iterator series_iterator;//Iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        cout<<"["<<counter<<"] "<<(*series_iterator)->displayGeneralInfo()<<endl<<endl;//Display counter and name with rating
        counter++;
    }
    cout<<endl<<"Type the number in brackets for the series/movie you want to see more details:"<<endl;//Ask the user to input the counter for the movie they want to see
    bool invalid_input=true, is_valid_number=false;//Bool for while and to indicate it's a number
    string input;//Variable for input
    int index;//Variable for the index inside the vector
    while (invalid_input)
    {
        cin>>input;//Ask for input
        for (int n=1;n<num_movies+num_series+1;n++)//For each possible answer +1 because the counter started in 1 and the index start at 0
        {
            if (input==to_string(n))//If input is the same as a possible answer
            {
                is_valid_number=true;//Enable the display part of the code
                invalid_input=false;//Stop while
                index=stoi(input);//Transform input to int
                index--;//Minus one because index are one less than the counter
                n=num_series+num_movies+1;//Stop for
            }
        }
        if (is_valid_number)//If it was a valid number
        {
            if(index<num_movies)//Because movies were shown first, if it's samller tha the number of movies, it must be a movie
            {
                cout<<all_movies[index]->toString()<<endl;//Display video info
            }
            else//If it's larger, it's a series
            {
                cout<<all_series[index-num_movies]->toString()<<endl;//Display series info and each video information
            }           
        }
        else//If it's was not a valid number, notify the user
        {
            cout<<"Invalid input, try again"<<endl;
        }
    }
}
void Platform::showGenre(string searched_genre)//Shows all the VIDEOS from a specific genre
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    bool something_shown=false;
    vector <Movie*>::const_iterator movie_iterator;
    for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//Check each film
    {
        if ((*movie_iterator)->getGenre()==searched_genre)//If the films genre is the same as the one I'm looking
        {
            cout<<(*movie_iterator)->toString()<<endl<<endl;//Print information
            something_shown=true;//Rememebr I printed something
        }
    }
    vector <Series*>::const_iterator series_iterator;
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)
    {
        if ((*series_iterator)->getGenre()==searched_genre)
        {
            cout<<(*series_iterator)->videosToString()<<endl<<endl;
            something_shown=true;//Rememebr I printed something
        }
    }
    if (!something_shown)
    {
        cout<<"There are no movies of this genre"<<endl;//Print there was no suitable media
    }
}
void Platform::showRating(int searched_rating)//returns the info of all videos with a specific rating
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }   
    bool show_something=false;
    vector <Video*> all_videos;//Vector to use polymorphism
    vector <Movie*>::const_iterator movie_iterator;//Iterator
    for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
    {
        all_videos.push_back((*movie_iterator));//Add all movies to the vector for polymorphism
    }
    vector <Series*>::const_iterator series_iterator;//Iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        for (int s=0;s<(*series_iterator)->getSeason();s++)//For each season in this series
        {
            for (int e=0;e<(*series_iterator)->getEpisodes();e++)//For each episode in each seson fo this series
            {
                all_videos.push_back((*series_iterator)->getEpisode(s,e));//Add the episodes to the vector for polymorphism
            }
        }
    }
    vector <Video*>::const_iterator video_iterator;//Iterator
    for (video_iterator=all_videos.begin();video_iterator!=all_videos.end();++video_iterator)//For each video in the vector for polymorphism
    {
        if ((*video_iterator)->getRating()==searched_rating)//If they have the same rating
        {
            cout<<(*video_iterator)->toString()<<endl;//Use polymorphism
            show_something=true;//Indicate I used something
        }
    }
    if (!show_something)//If nothing was shown
    {
        cout<<"There were no videos with this rating"<<endl;//Say there's was no video in that rating
    }
}
void Platform::showVideoByFilter()//Ask the users if they want to know of the video sof a specific genre or rating, then ask waht that specific condition is and then calls the specific function
{

    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess
        
    }
    string input;//To store the user input
    bool while_continues=true, valid_option=false;//While_continues is for the wile loop, valid_option determines if the input was valid
    while (while_continues)
    {
        //Hive instructions
        cout<<"To show the videos from a specific rating select 1\nTo show videos from a specifc genre select 2"<<endl;
        cin>>input;//Receive input
        
        if (input=="1")//If they select by Rating
        {
            while_continues=false;//End the outside while
            bool valid_input=true;
            while (valid_input)
            {
                cout<<"Write the rating you want to search:"<<endl;//Asak them to give me the rating
                cin>>input;//receive his input
                for (int i=1;i<6;i++)//For each valid rating
                {
                    if (input==to_string(i))//If the string input is the same as the int converted to string
                    {
                        valid_option=true;//Enable search
                        i=7;//End for
                    }
                }
                if (valid_option)//If a valid option was given
                {
                    cout<<"Showing videos with rating "<<input<<":"<<endl;//Notify the seacrhed rating
                    showRating(stoi(input));//Call my function that prints by rating
                    valid_input=false;//Stop inner while
                }
                else//If it was not a valid input
                {
                    cout<<"Invalid input, try again"<<endl;//Ask them to try again
                }
            }
            
        }
        else if(input=="2")
        {
            while_continues=false;//Stop outer while
            vector <string> available_genre;//Where I'll store the genre available in the platform
            vector <string>::const_iterator genre_iterator;//Iterator for genre
            vector <Movie*>::const_iterator movie_iterator;//Iterator for movie
            vector <Series*>::const_iterator series_iterator;//Iterator for series
            for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
            {
                string local_genre=(*movie_iterator)->getGenre();//Find this movies genre
                bool not_registered=true;//Registers if the genre is not already in the available_genre vector
                for (genre_iterator=available_genre.begin();genre_iterator!=available_genre.end();++genre_iterator)//For each genre already stored
                {
                    if (local_genre==(*genre_iterator))//If the genre is already there
                    {
                        not_registered=false;//Set as alredy registered
                    }
                }
                if (not_registered)//If it's not registered
                {
                    available_genre.push_back(local_genre);//Add it to the list
                    
                }
            }
            for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For all series
            {
                string local_genre=(*series_iterator)->getGenre();//Find this movies genre
                bool not_registered=true;//Registers if the genre is not already in the available_genre vector
                for (genre_iterator=available_genre.begin();genre_iterator!=available_genre.end();++genre_iterator)//For each genre in the vector
                {
                    if (local_genre==(*genre_iterator))//If the genre is in the list
                    {
                        not_registered=false;//Set as already registered
                    }
                }
                if (not_registered)//If it's not registred
                {
                    available_genre.push_back(local_genre);//Add it to the vector
                }
            }
            int number_genre=available_genre.size();//Store the total numbre of genres
            //Show the genre to the user
            int counter=0;//Index of the genre
            cout<<"Available genres:"<<endl;//Notify I'll show the genre
            for (genre_iterator=available_genre.begin();genre_iterator!=available_genre.end();++genre_iterator)
            {
                counter++;//Change index
                cout<<"["<<counter<<"]\t"<<(*genre_iterator)<<endl;//Print the index and the genre
            }
            bool valid_input=true;//Inner while condition
            while (valid_input)
            {
                cout<<"Select the numbre of the genre you want to search:"<<endl;//Ask the user to give the genre index
                cin>>input;//receive the input
                bool valid_index=false;
                for (int i=1;i<number_genre+1;i++)//For each posible index
                {
                    if (input==to_string(i))//If the number are the same
                    {
                        valid_index=true;//Save that's it's a valid answer
                        i=number_genre+2;//End for
                    }
                }
                if (valid_index)//If it was a valid index
                {
                    cout<<"Showing videos of the genre "<< available_genre[stoi(input)-1]<<":"<<endl;//Show the genre selected
                    showGenre(available_genre[stoi(input)-1]);//Call my mehtod
                    valid_input=false;//Stop inner while
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;
                }
                
            }
        }  
        else
        {
            cout<<"Invalid input, try again"<<endl;
        }
        
    }
}
void Platform::showSeriesRatingEpisodes()//Display all series, asks the user to select one, to select a rating and displays all episodes with said rating
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess    
    }
    int counter=1;//Index of the series
    string input;
    bool valid_series=true, valid_rating=true;
    vector <Series*>::const_iterator series_iterator;//Series iterator
    for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
    {
        cout<<"["<<counter<<"] "<<(*series_iterator)->displayGeneralInfo()<<endl;//Display thema
        counter++;//update index
    }
    cout<<"Select the number of the series you want to select:"<<endl;//Ask for input
    while (valid_series)//While there's no valid input
    {
        bool i_can_continue=false;
        cin>>input;//Receivve input
        for (int i=1;i<num_series+1;i++)//For each possible index
        {
            if (input==to_string(i))//If the stirng input  is the same as the int converted to string
            {
                valid_series=false;//End while
                i_can_continue=true;//Enable the next part
                i=num_series+2;//End for
            }
        }
        if (i_can_continue)//If a valid index has been given
        {
            int series_index=stoi(input)-1;//Store the index of the series
            while (valid_rating)//Not a valid rating
            {
                bool i_can_search=false;
                cout<<"Write the rating you want to search:"<<endl;//Asak them to give me the rating
                cin>>input;//receive his input
                for (int i=1;i<6;i++)//For each valid rating
                {
                    if (input==to_string(i))//If the string input is the same as the int converted to string
                    {
                        valid_rating=false;//Enable search
                        i_can_search=true;
                        i=7;//End for
                    }
                }
                if (i_can_search)
                {
                    string msg=all_series[series_index]->videosInRating(stoi(input));
                    if (msg=="")
                    {
                        msg="There are no videos with that rating";
                    }
                    cout<<msg<<endl;//Call the function for the series
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;
                }
            }
        }
        else
        {
            cout<<"Invalid input, try again"<<endl;
        }
        
    }
}
void Platform::showMoviesInRating()//Asks the user for a rating, and then show all movies with said rating
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess    
    }
    bool show_something=false;
    string input;//Store input
    bool while_continues=true;//While conditional
    while (while_continues)//While i can continue
    {
        cout<<"Select the rating you want to search for:"<<endl;//Ask for rating
        cin>>input;//Receive input
        bool valid_rating=false;//Store if the input is a rating
        for (int i=1;i<6;i++)//For each posible rating
        {
            if (input==to_string(i))//If it's the same
            {
                i=7;//End for
                valid_rating=true;//Enable next part
            }
        }
        if (valid_rating)//If it's a valid rating
        {
            vector <Movie*>::const_iterator movie_iterator;//Iterator
            cout<<"Showing movies with rating of "<<input<<":"<<endl;//Notify waht rating i'm displaying
            int int_input=stoi(input);//Tranforms it to an int
            for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//Fpr each movie
            {
                if ((*movie_iterator)->getRating()==int_input)//If the rating is the same as the one i was searching for
                {
                    cout<<(*movie_iterator)->display()<<endl;//I display it
                    show_something=true;
                }
            }
            while_continues=false;//Stop while
        }
        else
        {
            cout<<"Invalid input, try again"<<endl;
        }
        
    }
    if (!show_something)
    {
        cout<<"There are no movies of this rating"<<endl;
    }
}
void Platform::rateAVideo()//Ask the user of she/he wants to rate a movie or a series, it displays mvies/series and ask for the new rating if it's amovie, if it's a series asks if she/he wants to rate the whole series or just and episode, if it's an episode, it calls the series function, if it's the whole series, it changes the series general_rating
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess    
    }
    bool valid_input=true, rate_movie=false,rate_series=false;
    string input;
    while (valid_input)
    {
        cout<<"If you want to rate a movie select 1\nIf you want to rate a series, select 2"<<endl;
        cin>>input;//receive input
        if (input=="1")
        {
            int counter=1;//Movie index
            valid_input=false;
            vector <Movie*>::const_iterator movie_iterator;//Iterator
            for (movie_iterator=all_movies.begin();movie_iterator!=all_movies.end();++movie_iterator)//For each movie
            {
                cout<<"["<<counter<<"] "<<(*movie_iterator)->display()<<endl;//Display index and movie
                counter++;//Updtae counter
            }
            bool valid_rating=true;
            while (valid_rating)
            {
                bool is_movie=false;
                cout<<"Select the movie you want to rate:"<<endl;
                cin>>input;//Receive input
                for (int n=1;n<num_movies+1;n++)
                {
                    if (input==to_string(n))
                    {
                        is_movie=true;
                        n=num_movies+2;//end for
                        valid_rating=false;//end while
                    }
                }
                if (is_movie)
                {
                    int movie_index=stoi(input)-1;
                    bool valid_rating=true;
                    while (valid_rating)
                    {
                        bool is_rating=false;
                        cout<<"Write the ranking you want to give this movie"<<endl;
                        cin>>input;
                        for (int r=1;r<6;r++)
                        {
                            if (input==to_string(r))
                            {
                                r=7;//end for
                                is_rating=true;
                            }
                        }
                        if (is_rating)
                        {
                            all_movies[movie_index]->setRating(stoi(input));
                            cout<<"The rating has been changed"<<endl;
                            valid_rating=false;//end while
                        }
                        else
                        {
                            cout<<"Invalid input, try again"<<endl;
                        }
                        
                    }
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;//Notify the user
                }
                
            }
        }
        else if(input=="2")
        {
            valid_input=false;//end while
            bool valid_selection=true;
            int counter=1;//Series index
            vector <Series*> :: const_iterator series_iterator;//Iterator
            for (series_iterator=all_series.begin();series_iterator!=all_series.end();++series_iterator)//For each series
            {
                cout<<"["<<counter<<"] "<<(*series_iterator)->displayGeneralInfo()<<endl;//Display index and series
                counter++; //Update counter
            }
            int series_index=0;
            bool valid_index=false;
            while (valid_selection)
            {
                cout<<"Select the index of the series you want to rate"<<endl;//Ask for index
                cin>>input;//Receiv input
                for (int s=1;s<num_series+1;s++)
                {
                    if (input==to_string(s))
                    {
                        valid_index=true;
                        series_index=s-1;
                    }
                }
                if (valid_index)
                {
                    valid_selection=false;
                    bool valid_decision=true;
                    while (valid_decision)
                    {
                        //ask if they want to rate the series or one episode
                        cout<<"If you wish to rate the whole series select 1\nIf you wish to rate an episode select 2"<<endl;
                        cin>>input;//Receive input
                        if (input=="1")
                        {
                            valid_decision=false;//Stop while
                            bool valid_rating=true;
                            while (valid_rating)
                            {
                                bool is_rating=false;//If true, it mark sthe user gave a valid rating
                                cout<<"Write the rating you want to give to this series"<<endl;//Ask for rating
                                cin>>input;//receive rating
                                for (int r=1;r<6;r++)//For each possible rating
                                {
                                    if (input==to_string(r))//If it's the same
                                    {
                                        is_rating=true;//Enable rating part
                                        r=7;//End for
                                    }
                                }
                                if (is_rating)
                                {
                                    valid_rating=false;
                                    all_series[series_index]->setRating(stoi(input));
                                    cout<<"The rating has been changed"<<endl;
                                }
                                else
                                {
                                    cout<<"Invalid input, try again"<<endl;//Notify the user
                                }
                                
                            }
                        }
                        else if (input=="2")
                        {
                            valid_decision=false;//Stop while
                            all_series[series_index]->rateEpisode();//Call the series method
                        }
                        else
                        {
                            cout<<"Invalid input, try again"<<endl;//Notify the user
                        }
                        
                    }
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;//Notify the user
                }
                
            }
        }
        else
        {
            cout<<"Invalid input, try again"<<endl;//Notify the user
        }
        
    }

}
void Platform::loadFile()//Ask the user for a file name or reads the included file
{
    bool valid_name=true, the_first=true;//Remember if i'm in the fisrt one
    string file_name;//Where to store the input
    getline(cin,file_name);//Getline, I need to get it here because the first time i use it it returns ""
    while (valid_name)
    {
        cout<<"Write the name of the file you want to read, if you wish to read the included file, write 1"<<endl;
        getline(cin,file_name);//Receive input, use getline bacause the file name has a space in it
        if (file_name=="1")//If they want my standard file
        {
            createVideos("video_info.csv");//I use my file
            valid_name=false;//Stop while
        }
        else
        {
            ifstream file_read;//Create an ifstream
            file_read.open(file_name);//open the file they gave me
            if (file_read.is_open())//if it opens
            {
                createVideos(file_name);//send it to the method
                valid_name=false;//Stop while
            }
            else//If it didn't open
            {

                cout<<"File was not found, try again"<<endl;//Notify the user

            }
        }
        
    }
}
void Platform::createMedia()//Asks the user for info to create a movie or series and cretae its, then it'll add it to a cdv file
{
    if (!file_read)//If there are not any movies nor series loaded
    {
        cout<<"WARNING\n\nNo data file has been loaded, loading file...\n"<<endl;
        createVideos("video_info.csv");//I really don't undesratnd why shall i laeve the user decide when to run the files, I leave my program unprotected unless i add extra lines, it would be better if I could just create my videos in the constructor, but the instructions say it must be part of the menu so... it's ok I guess    
    }
    string input, line_4_writer="";//Where to receive input and a line to add to the csv file
    bool valid_input=true;//Bool for while
    while (valid_input)
    {
        //Ask if it's series or movie
        cout<<"If you want to create a movie write M\nIf you want to create a series press S"<<endl;
        cin>>input;//Receive input
        //I know some stuff here that could have been made into functions, I'll change it if I have time, i'm tired, I've been working on this for more than a week ^w^
        //Well turns out i made it, so... yey to me, i think i could simplify it alittle bit more, but well, I've dedicated all my time to this project and i just remembered I have another classes, yeah... not the best decision...
        //Who I'm kidding, I really enjoy programming in c++, but you now, I'm kind of running to a burn out, maybe it's time I watch the series included in this project ^w^
        //Why I wrote this here? I could have done it at the beggining of the function, well it is waht it is :)
        if (input=="M")//If it's a movie
        {
            bool valid_string=true;
            string name,ID,genre;
            int length,rating,year,budget;//Create important variable
            getline(cin,input);//First one returns ""
            while (valid_string)
            {
                cout<<"Write the name of the film:"<<endl;//Ask for name
                getline(cin,name);//Get name
                string evaluate=checkString(name);
                if (evaluate=="_blank_")//If it's blank 
                {
                    cout<<"It cannot be only spaces..."<<endl;
                }
                else if (evaluate=="_empty_")//If it's empty
                {
                    cout<<"It cannot be empty..."<<endl;
                }
                else
                {
                    valid_string=false;//End while
                }
            }
            ID=createID(name);//Create an ID based in the name
            string initial_letter(1,name[0]);//I create the initial letter, will be a string of length 1 made of the char of the first character in name
            valid_string=true;//Reinitialize the bool
            while (valid_string)
            {
                cout<<"Write the genre of the film:"<<endl;//Ask for genre
                getline(cin,genre);//Get genre
                string evaluate=checkString(genre);
                if (evaluate=="_blank_")//If it's blank 
                {
                    cout<<"It cannot be only spaces..."<<endl;
                }
                else if (evaluate=="_empty_")//If it's empty
                {
                    cout<<"It cannot be empty..."<<endl;
                }
                else
                {
                    valid_string=false;//End while
                }
            }

            bool valid_number=true;//Create a while to evaluate the number
            while (valid_number)
            {
                cout<<"Write the length of the film in minutes:"<<endl;//Ask for film duration
                cin>>input;//receive duration
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The length cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    length=evluation;//assign value
                }  
            }
            valid_number=true;//Reinitialize the bool
            while (valid_number)
            {
                cout<<"Write the rating of the film:"<<endl;//Ask for rating
                cin>>input;//receive rating
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The rating cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    if (evluation<=5 && evluation>=1)
                    {
                        valid_number=false;//stop while
                        rating=evluation;//assign value
                    }
                    else 
                    {
                        cout<<"It has to be a number between 1 and 5..."<<endl;
                    }
                }  
            }
            valid_number=true;//Reinitialize the bool
            while (valid_number)
            {
                cout<<"Write the year of release of the film:"<<endl;//Ask for year
                cin>>input;//receive year
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The year cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    year=evluation;//assign value
                }  
            }
            valid_number=true;//Reinitialize the bool
            while (valid_number)
            {
                cout<<"Write the budget of the film:"<<endl;//Ask for film's budget
                cin>>input;//receive Budget
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The budget cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    budget=evluation;//assign value
                }  
            }
            //create data string array
            string data[5]={ID,name,genre,initial_letter,to_string(length)};
            //Create object
            all_movies.push_back(new Movie(data,rating,year,budget));
            //Update nume_movies variable
            num_movies++;
            valid_input=false;//end while
            //Ask for csv file name
            valid_string=true;//reinitiliza the bool
            string file_name;//String for the file_name
            while (valid_string)
            {
                cout<<"Write name of the file you want to save your film:"<<endl;
                cin>>input;
                file_name=input;
                bool valid_answer=true;
                while (valid_answer)
                {
                    cout<<"If the file doesn't exists a new one with this name will be creates, are you sure?"<<endl<<"1. Yes\n2. No"<<endl;
                    cin>>input;
                    if (input=="1")
                    {
                        //end both whiles
                        valid_answer=false;//End the inner one
                        valid_string=false;
                    }
                    else if (input=="2")
                    {
                        //End this one
                        valid_answer=false;//end this one, it'll return to the outer one
                    }
                    else
                    {
                        cout<<"Invalid input, try again"<<endl;
                    }
                }
            }
            ofstream writer;
            writer.open(file_name,ios::app);//Open the file with the append lines option
            string line_4_writer="M,"+ID+","+name+","+genre+","+to_string(length)+","+to_string(rating)+","+name+",0,0"+","+to_string(year)+","+to_string(budget);//Create a string M,ID,Name,genre,length,rating,name,0,0,year,budget
            writer<<endl<<line_4_writer<<endl;//Add line
            writer.close();//Close the file
        }
        else if (input=="S")
        {
            bool valid_string=true, valid_number=true;//Bool for whiles
            string name, ID, genre;//Variables for names
            int year, budget, seasons, episodes;//Variables for int
            getline(cin,name);//First will be ""
            //Ask name
            while (valid_string)
            {
                cout<<"Write the name of the series:"<<endl;//Ask name
                getline(cin,name);//Get name
                string evaluate=checkString(name);
                if (evaluate=="_blank_")//If it's blank 
                {
                    cout<<"It cannot be only spaces..."<<endl;
                }
                else if (evaluate=="_empty_")//If it's empty
                {
                    cout<<"It cannot be empty..."<<endl;
                }
                else
                {
                    valid_string=false;//End while
                }
            }
            //Create ID
            ID=createID(name);//Create an ID based in the name
            string initial_letter(1,name[0]);//I create the initial letter, will be a string of length 1 made of the char of the first character in name
            valid_string=true;//Reinitiliaze variable
            //Ask genre
            while (valid_string)
            {
                cout<<"Write the genre of the series:"<<endl;//Ask genre
                getline(cin,genre);//Get genre
                string evaluate=checkString(genre);
                if (evaluate=="_blank_")//If it's blank 
                {
                    cout<<"It cannot be only spaces..."<<endl;
                }
                else if (evaluate=="_empty_")//If it's empty
                {
                    cout<<"It cannot be empty..."<<endl;
                }
                else
                {
                    valid_string=false;//End while
                }
            }
            //Ask year
            while (valid_number)
            {
                cout<<"Write the year of realease of the series:"<<endl;//Ask for series year of release
                cin>>input;//receive year
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The year cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    year=evluation;//assign value
                }  
            }
            //Ask budget
            valid_number=true;//reinitialize variable
            while (valid_number)
            {
                cout<<"Write the budget of the series:"<<endl;//Ask for series's budget
                cin>>input;//receive Budget
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The budget cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    budget=evluation;//assign value
                }  
            }
            //Ask seasons
            valid_number=true;//reinitialize variable
            while (valid_number)
            {
                cout<<"Write the number of seasons of the series:"<<endl;//Ask for season number
                cin>>input;//receive season
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The number of seasons cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    seasons=evluation;//assign value
                }  
            }
            //Ask episodes per season
            valid_number=true;//reinitialize variable
            while (valid_number)
            {
                cout<<"Write the number of episodes per seasons of the series:"<<endl;//Ask for episodes per seasons number
                cin>>input;//receive season
                int evluation=checkInt(input);
                if (evluation==0)//If it's zero
                {
                    cout<<"The number of seasons cannot be zero..."<<endl;
                }
                else if (evluation==-1)//If it was not a number
                {
                    cout<<"It must be a number..."<<endl;
                }
                else if (evluation==-2)//If it was negetive
                {
                    cout<<"It must be a positive number..."<<endl;
                }
                else//then it's valid
                {
                    valid_number=false;//stop while
                    episodes=evluation;//assign value
                }  
            }
            //Create array, episodes names, episodes length, episode rating
            string all_episodes_name[seasons*episodes];
            double all_episode_length[seasons*episodes];
            int all_episodes_rating[seasons*episodes];
            //Create array for lines
            string lines_4_file[seasons*episodes];
            string episode_name;
            int episode_rating;
            double episode_length;
            int episode_counter=0;
            bool valid_episode=true;
            for (int s=0;s<seasons;s++)//For each season
            {
                for (int e=0;e<episodes;e++)//For each episode
                {
                    //Add to line array S,ID,name,genre,
                    string line_4_array="S,"+ID+","+name+","+genre+",";
                    //Display seasons and episode
                    cout<<"Season "<<s+1<<" Episode "<<e+1<<endl;
                    //Ask name
                    getline(cin,episode_name);
                    valid_episode=true;//Reinitialize variable
                    while (valid_episode)
                    {
                        cout<<"Write the name of the episode:"<<endl;
                        getline(cin,episode_name);
                        string evaluate=checkString(episode_name);
                        if (evaluate=="_blank_")//If it's blank 
                        {
                            cout<<"It cannot be only spaces..."<<endl;
                        }
                        else if (evaluate=="_empty_")//If it's empty
                        {
                            cout<<"It cannot be empty..."<<endl;
                        }
                        else
                        {
                            valid_episode=false;//End while
                        }
                    }
                    //Ask lentgh
                    valid_episode=true;
                    while (valid_episode)
                    {
                        cout<<"Write the length of the episode:"<<endl;//Ask for the length
                        cin>>input;//receive length
                        int evluation=checkInt(input);
                        if (evluation==0)//If it's zero
                        {
                            cout<<"The length cannot be zero..."<<endl;
                        }
                        else if (evluation==-1)//If it was not a number
                        {
                            cout<<"It must be a number..."<<endl;
                        }
                        else if (evluation==-2)//If it was negetive
                        {
                            cout<<"It must be a positive number..."<<endl;
                        }
                        else//then it's valid
                        {
                            valid_episode=false;//stop while
                            episode_length=evluation;//assign value
                        }  
                    }
                    //Ask rating
                    valid_episode=true;
                    while (valid_episode)
                    {
                        cout<<"Write the rating of the episode:"<<endl;//Ask for the rating
                        cin>>input;//receive rating
                        int evluation=checkInt(input);
                        if (evluation==0)//If it's zero
                        {
                            cout<<"The rating cannot be zero..."<<endl;
                        }
                        else if (evluation==-1)//If it was not a number
                        {
                            cout<<"It must be a number..."<<endl;
                        }
                        else if (evluation==-2)//If it was negetive
                        {
                            cout<<"It must be a positive number..."<<endl;
                        }
                        else//then it's valid
                        {
                            if (evluation<=5 && evluation>=1)
                            {
                                valid_episode=false;//stop while
                                episode_rating=evluation;//assign value
                            }
                            else 
                            {
                                cout<<"It has to be a number between 1 and 5..."<<endl;
                            }
                        }  
                    }
                    //Finalize line_4_array add: episodelength,episode rating,episode name, season, episode,year, budget
                    line_4_array+=to_string(episode_length)+","+to_string(episode_rating)+","+episode_name+","+to_string(s+1)+","+to_string(e+1)+","+to_string(year)+","+to_string(budget);
                    //Add to info array
                    lines_4_file[episode_counter]=line_4_array;//Add line
                    all_episodes_name[episode_counter]=episode_name;//Add name
                    all_episode_length[episode_counter]=episode_length;//Add length
                    all_episodes_rating[episode_counter]=episode_rating;//Add rating
                    episode_counter++;//Updta episode counter
                }
            }
            all_series.push_back(new Series(seasons,episodes,name,all_episodes_name,genre,all_episode_length, all_episodes_rating, ID, year, budget));//Create object
            num_series++;//Update the number of seasons
                        valid_string=true;//reinitiliza the bool
            string file_name;//String for the file_name
            while (valid_string)
            {
                cout<<"Write name of the file you want to save your film:"<<endl;
                cin>>input;
                file_name=input;
                bool valid_answer=true;
                while (valid_answer)
                {
                    cout<<"If the file doesn't exists a new one with this name will be creates, are you sure?"<<endl<<"1. Yes\n2. No"<<endl;
                    cin>>input;
                    if (input=="1")
                    {
                        //end both whiles
                        valid_answer=false;//End the inner one
                        valid_string=false;
                    }
                    else if (input=="2")
                    {
                        //End this one
                        valid_answer=false;//end this one, it'll return to the outer one
                    }
                    else
                    {
                        cout<<"Invalid input, try again"<<endl;
                    }
                }
            }
            valid_input=false;//end while
            ofstream writer;
            writer.open(file_name,ios::app);//Open the file with the append lines option
            for (int l=0;l<seasons*episodes;l++)//For each line
            {
                writer<<endl<<lines_4_file[l];//Add the line to the file
            }
            writer<<endl;//Go to next line
            writer.close();//Close the file
        }
        else
        {
            cout<<"Invalid output, try again"<<endl;
        }
        
    }   
}
void Platform::menu()//Opens a menu
{
    cout<<"Welcome"<<endl;//Welcome the user
    bool menu_runs=true;//While cool
    bool extended_menu=false;
    int options_number=7;
    string input;//Variable to receive input
    while (menu_runs)
    {
        //Display menu
        cout<<"\n1.Load data file"<<endl<<"2.Show the videos with a specific rating or from a specific genre."<<endl<<"3.Show the episodes of a specific series with a specific rating."<<endl<<"4.Show the movies with a specific rating."<<endl<<"5.Rate a video."<<endl<<"6.Exit"<<endl;
        if (!extended_menu)
        {
            cout<<"7.Show extended menu"<<endl;
        }
        else
        {
            cout<<"7.Show everything in alphabetical order"<<endl<<"8.Show collections of all video title and rating"<<endl<<"9.Show only series"<<endl<<"10.Show only movies"<<endl<<"11.Show the episodes for one series"<<endl<<"12.Show more info of a movie or series"<<endl<<"13.Create a series or movie"<<endl<<"14.Hide extended menu"<<endl;
        }
        cin>>input;//Receive input
        bool valid_input=false;
        for (int in=1;in<options_number+1;in++)
        {
            if (input==to_string(in))
            {
                valid_input=true;
            }
        }
        if (valid_input)
        {
            if (input=="1")
            {
                //Load file
                loadFile();
            }
            else if(input=="2")
            {
                //Show videos of genre or rating
                showVideoByFilter();
            }
            else if (input=="3")
            {
                //Show  episodes in rating
                showSeriesRatingEpisodes();
            }
            else if (input=="4")
            {
                //Show movies with rating
                showMoviesInRating();
            }
            else if (input=="5")
            {
                //Rate video
                rateAVideo();
            }
            else if (input=="6")
            {
                //Close
                menu_runs=false;
            }
            else if (input=="7")
            {
                //show extende menu ture
                //or show alphabeticall order
                //update number of options
                if (extended_menu)
                {
                    showAlphabet();
                }
                else
                {
                    extended_menu=true;
                    options_number=14;
                }
                
            }
            else if (input=="8")
            {
                //Show all videos
                showAll();
            }
            else if(input=="9")
            {
                //show series
                showAllSeriesEpisodes();
            }
            else if (input=="10")
            {
                //show movies
                showMovies();
            }
            else if (input=="11")
            {
                //show episode of one series
                selectSeries();
            }
            else if (input=="12")
            {
                //Show all info
                selectSomething();
            }
            else if (input=="13")
            {
                //create something
                createMedia();
            }
            else if (input=="14")
            {
                //Extended menu false
                //change number of options
                extended_menu=false;
                options_number=7;
            }
        }
        else
        {
            cout<<"Invalid option, try again"<<endl;
        }
        
        
    }
    cout<<"Bye bye o/"<<endl;//After while has ended, I say goodbye
}