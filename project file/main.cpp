#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include "MMSystem.h"

using namespace std;

class song {
protected:
    string title;
    string artist;
    string file_name;

public:
    song() {
        title = "";
        artist = "";
        file_name = "";
    }

    song(string title1, string artist1, string file_name1) {
        title = title1;
        artist = artist1;
        file_name = file_name1;
    }

    void play_song() {
        cout << "Playing: " << title << " by " << artist << endl;
        PlaySound(TEXT(file_name.c_str()), NULL, SND_FILENAME | SND_ASYNC);
    }

    void pause() {
        PlaySound(NULL, NULL, SND_ASYNC);
        cout << "Song paused." << endl;
    }

    string& get_title() {
        return title;
    }

    string& get_artist() {
        return artist;
    }

    string& get_file_name() {
        return file_name;
    }
};

class playlist : public song {
private:
    vector<song> songs;
    string playlist_title;

public:
    playlist(string& title) {
        playlist_title = title;
    }

    void add_song(string file_name, string artist) {
        songs.push_back(song("", artist, file_name)); // title is empty for now
    }

    void play() {
        cout << "Playing your favorite playlist: " << playlist_title << endl;
        for (int i = 0; i < songs.size(); i++) {
            songs[i].play_song();
            while (true) {
                cout << "Options: 1. Pause  2. Next  3. Quit\n";
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    songs[i].pause();
                    cout << "Press Enter to resume...";
                    cin.ignore();
                    cin.get();
                    songs[i].play_song();
                } else if (choice == 2) {
                    break; // to next song
                } else if (choice == 3) {
                    songs[i].pause();
                    stop();
                    return;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
    }

    void stop() {
        cout << "Song Stopped and playlist was emptied. Thank you :)";
    }

    void listSongs() {
        if (songs.empty()) {
            cout << "No songs in the playlist." << endl;
        } else {
            for (int i = 0; i < songs.size(); i++) {
                cout << i + 1 << ". " << songs[i].get_title() << " by " << songs[i].get_artist() << endl;
            }
        }
    }

    void displayAvailableSongs() {
        cout << "Available songs:\n";
        for (int i = 0; i < songs.size(); i++) {
            string songName = songs[i].get_file_name();
            songName = songName.substr(0, songName.find_last_of('.'));
            cout << i + 1 << ". " << songName << " by " << songs[i].get_artist() << endl;
        }
    }

    void addSongToPlaylist(int index) {
        if (index >= 1 && index <= songs.size()) {
            add_song(songs[index - 1].get_file_name(), songs[index - 1].get_artist());
            cout << "Added " << songs[index - 1].get_file_name() << " by " << songs[index - 1].get_artist() << " to your playlist." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    void search_and_play_by_partial_name(string partial_name) {
        bool found = false;

        for (int i = 0; i < songs.size(); i++) {
            string fileName = songs[i].get_file_name();
            size_t dotPos = fileName.find_last_of('.');
            string fileNameWithoutExt = fileName.substr(0, dotPos);

            if (songs[i].get_title().find(partial_name) != string::npos || fileNameWithoutExt.find(partial_name) != string::npos) {
                cout << i + 1 << ". " << fileNameWithoutExt << " by " << songs[i].get_artist() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No matching songs found." << endl;
            return;
        }

        int choice;
        cout << "Enter the number of the song you want to play: ";
        cin >> choice;

        if (choice >= 1 && choice <= songs.size()) {
            songs[choice - 1].play_song();
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
};

int main() {
    string playlistTitle;
    cout << "Enter the title of your playlist: ";
    getline(cin, playlistTitle);

    playlist myPlaylist(playlistTitle);

    myPlaylist.add_song("alag_aasman.wav", "Anuv Jain");
    myPlaylist.add_song("chand_baliyan.wav", "Aditya A");
    myPlaylist.add_song("dil_vich_tere_liye.wav", "Milind gaba");
    myPlaylist.add_song("elvish_bhai.wav", "Elvish Yadav");
    myPlaylist.add_song("likhe_jo_khat.wav", "Mohammed Rafi");
    myPlaylist.add_song("pal_behta_jaaye.wav", "Lata Mangeshkar");
    myPlaylist.add_song("rinkiya_ke_papa.wav", "Daler Mehndi");
    myPlaylist.add_song("shree_ram_janki.wav", "Lakhbir Singh Lakkha");
    myPlaylist.add_song("tumhi_ho_bandhu.wav", "Neeraj Shridhar");

    cout << "Welcome to our Music Playlist Manager SPAMTIFY" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Available Songs\n";
        cout << "2. Add Song to Playlist\n";
        cout << "3. Search and Play Song by Name\n";
        cout << "4. Play Playlist\n";
        cout << "5. List Songs in Playlist\n";
        cout << "6. Stop Playlist\n";
        cout << "7. Quit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            myPlaylist.displayAvailableSongs();
            break;
        case 2: {
            int index;
            myPlaylist.displayAvailableSongs();
            cout << "Enter the number of the song you want to add to your playlist: ";
            cin >> index;
            myPlaylist.addSongToPlaylist(index);
            break;
        }
        case 3: {
            string partial_name;
            cout << "Enter a partial name of the song you want to search: ";
            cin.ignore();
            getline(cin, partial_name);
            myPlaylist.search_and_play_by_partial_name(partial_name);
            break;
        }
        case 4:
            myPlaylist.play();
            break;
        case 5:
            myPlaylist.listSongs();
            break;
        case 6:
            myPlaylist.stop();
            return 0;
        case 7:
            myPlaylist.stop();
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
