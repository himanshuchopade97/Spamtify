//music playlist manager
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include "MMSystem.h"

using namespace std;

class song
{
    protected:
        string title;
        string artist;
        
    public:
        song()
        {
            title="";
            artist="";
        }
        song(string title1,string artist1)
            {
                title=title1;
                artist=artist1;
            
            }
    
        void play_song()  
        {
            cout << "Playing: " << title << " by " << artist << endl;
            PlaySound (TEXT("maahive.wav"), NULL, SND_FILENAME | SND_ASYNC);

        }

        void pause() 
        {
            PlaySound(NULL, NULL, SND_ASYNC);
            cout << "Song paused." << endl;
        }
      
        string  &get_title()
        {
            return title;
        }
        string &get_artist()
        {
            return artist;
        }
};
class playlist : public song
{
    private:       
        song s1;
        vector<song> songs;
        string playlist_title;
    public:

        playlist(string& title) 
        {
            // this->title = title;
            // this->artist = "";
            playlist_title = title;
        }

        void add_song(string title,string artist)
        {
            songs.push_back(song(title,artist));
        }
        
        void play()  
        {
            cout << "Playing you favourtie playlist: " << playlist_title << endl;
            for (int i = 0; i < songs.size(); i++) {
                songs[i].play_song();
                while (true) 
                {
                    cout << "Options: 1. Pause  2. Next  3. Quit\n";
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;
                    if (choice == 1)
                    {
                        songs[i].pause();
                        cout << "Press Enter to resume...";
                        cin.ignore();
                        cin.get();
                        songs[i].play_song();
                    } 
                    else if (choice == 2) 
                    {
                        break;    //to next song
                    } 
                    else if (choice == 3) 
                    {
                        return; // playlist ko stop kar deta hai isse
                    } 
                    else 
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
        }
    
        void stop()
        {
            cout<<"Song Stopped and playlist was emptied. Thank you :)";

            //stop wala and clear wala if possible

        }

        void listSongs()  
        {

            //playlist puri dikhe aise functions dalne hai 


        }
};

int main()
{
    string playlistTitle;
    cout << "Enter the title of your playlist: ";
    getline(cin, playlistTitle);

    playlist myPlaylist(playlistTitle);

    cout << "Welcome to our Music Playlist Manager  SPAMTIFY" << endl;

    while (true) 
    {
        cout << "\nMenu:\n";
        cout << "1. Add Song to Playlist\n";
        cout << "2. Play Playlist\n";
        cout << "3. List Songs in Playlist\n";
        cout << "4. Stop Playlist\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    string title, artist;
                    cout << "Enter song title: ";
                    cin>>title;
                    cout << "Enter artist name: ";
                    cin>>artist;
                    myPlaylist.add_song(title, artist);
                    cout << "Song added to the playlist." << endl;
                }
                break;
            case 2:
                myPlaylist.play();
                break;
            case 3:
                myPlaylist.listSongs();
                break;
            case 4:
                myPlaylist.stop();
                return 0;
            case 5:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
    
