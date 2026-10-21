#include "AudioSystemManager.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

AudioSystemManager::AudioSystemManager() {}

AudioSystemManager::~AudioSystemManager() {}

void AudioSystemManager::run() {
    int choice = -1;
    do {
        showMenu();
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a valid menu number.\n";
            continue;
        }

        handleChoice(choice);

    } while (choice != 0);
}

void AudioSystemManager::showMenu() const {
    std::cout << "\n========================================\n";
    std::cout << "      AUDIO SYSTEM MANAGEMENT MENU      \n";
    std::cout << "========================================\n";
    std::cout << "1. Add a new audio track (Song/Podcast/Memo)\n";
    std::cout << "2. Show all tracks in the system\n";
    std::cout << "3. Playlist management\n";
    std::cout << "4. Save data to file\n";
    std::cout << "5. Load data from file\n";
    std::cout << "6. Delete data from file\n";
    std::cout << "0. Exit\n";
    std::cout << "----------------------------------------\n";
}

void AudioSystemManager::handleChoice(int choice) {
    switch (choice) {
    case 1:
        handleAddTrack();
        break;
    case 2:
        handleShowAllTracks();
        break;
    case 3:
        handlePlaylistManagement();
        break;
    case 4:
        saveToFile("audio_database.txt");
        break;
    case 5:
        loadFromFile("audio_database.txt");
        break;
    case 6:
        handleDeleteMenu();
        break;
    case 0:
        std::cout << "Exiting the program. Goodbye!\n";
        break;
    default:
        std::cout << "Non-existent option! Please choose from the menu.\n";
    }
}

void AudioSystemManager::handleAddTrack() {
    int typeChoice = 0;
    std::cout << "\n--- Select Track Type ---\n";
    std::cout << "1. Song Track\n";
    std::cout << "2. Podcast Track\n";
    std::cout << "3. Voice Memo Track\n";
    std::cout << "Enter type: ";
    std::cin >> typeChoice;

    std::string id, title, format;
    double duration = 0.0;
    double size = 0.0;

    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter Format (e.g., mp3, wav): ";
    std::cin >> format;
    std::cout << "Enter Duration (seconds): ";
    std::cin >> duration;
    std::cout << "Enter Size (MB): ";
    std::cin >> size;

    if (typeChoice == 1) {
        std::string performer, genre;
        std::cout << "Enter Performer: ";
        std::cin.ignore();
        std::getline(std::cin, performer);
        std::cout << "Enter Genre: ";
        std::getline(std::cin, genre);

        SongTrack song(id, title, format, duration, size, performer, genre);
        allSongs.push_back(song);
        std::cout << "Song added successfully!\n";

    }
    else if (typeChoice == 2) {
        std::string host, language;
        std::cout << "Enter Podcast Host: ";
        std::cin.ignore();
        std::getline(std::cin, host);
        std::cout << "Enter Language: ";
        std::getline(std::cin, language);

        PodcastTrack podcast(id, title, format, duration, size, host, language);
        allPodcasts.push_back(podcast);
        std::cout << "Podcast added successfully!\n";

    }
    else if (typeChoice == 3) {
        int year, month, day, priority;
        std::cout << "Enter Date (Year Month Day separated by spaces): ";
        std::cin >> year >> month >> day;
        std::cout << "Enter Priority (1-5): ";
        std::cin >> priority;

        Date date(year, month, day);
        VoiceMemoTrack memo(id, title, format, duration, size, date, priority);
        allVoiceMemos.push_back(memo);
        std::cout << "Voice Memo added successfully!\n";
    }
    else {
        std::cout << "Invalid track type selected!\n";
    }
}

void AudioSystemManager::handleShowAllTracks() const {
    std::cout << "\n========================================\n";
    std::cout << "          ALL SYSTEM TRACKS             \n";
    std::cout << "========================================\n";

    std::cout << "\n--- Songs (" << allSongs.getSize() << ") ---\n";
    for (size_t i = 0; i < allSongs.getSize(); ++i) {
        std::cout << i + 1 << ". ";
        allSongs[i].printInfo();
    }

    std::cout << "\n--- Podcasts (" << allPodcasts.getSize() << ") ---\n";
    for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
        std::cout << i + 1 << ". ";
        allPodcasts[i].printInfo();
    }

    std::cout << "\n--- Voice Memos (" << allVoiceMemos.getSize() << ") ---\n";
    for (size_t i = 0; i < allVoiceMemos.getSize(); ++i) {
        std::cout << i + 1 << ". ";
        allVoiceMemos[i].printInfo();
    }
    std::cout << "========================================\n";
}

void AudioSystemManager::handlePlaylistManagement() {
    int plChoice = 0;
    std::cout << "\n--- Playlist Management ---\n";
    std::cout << "1. Create new playlist\n";
    std::cout << "2. Show all playlists\n";
    std::cout << "3. Add song to a playlist\n";
    std::cout << "Enter choice: ";
    std::cin >> plChoice;

    if (plChoice == 1) {
        std::string plName;
        std::cout << "Enter playlist name: ";
        std::cin.ignore();
        std::getline(std::cin, plName);

        Playlist newPlaylist(plName);
        playlists.push_back(newPlaylist);
        std::cout << "Playlist created successfully!\n";

    }
    else if (plChoice == 2) {
        if (playlists.isEmpty()) {
            std::cout << "No playlists available.\n";
            return;
        }
        for (size_t i = 0; i < playlists.getSize(); ++i) {
            std::cout << "\n[" << i + 1 << "] ";
            playlists[i].printPlaylist();
        }

    }
    else if (plChoice == 3) {
        if (playlists.isEmpty() || allSongs.isEmpty()) {
            std::cout << "Error: You need at least one playlist and one song to perform this action.\n";
            return;
        }

        std::cout << "Select Playlist Index:\n";
        for (size_t i = 0; i < playlists.getSize(); ++i) {
            std::cout << i + 1 << ". " << playlists[i].getPlaylistName() << "\n";
        }
        size_t plIndex;
        std::cin >> plIndex;

        if (plIndex < 1 || plIndex > playlists.getSize()) {
            std::cout << "Invalid playlist index!\n";
            return;
        }

        std::cout << "Select Song Index to add:\n";
        for (size_t i = 0; i < allSongs.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allSongs[i].printInfo();
        }
        size_t songIndex;
        std::cin >> songIndex;

        if (songIndex < 1 || songIndex > allSongs.getSize()) {
            std::cout << "Invalid song index!\n";
            return;
        }

        auto songCopy = std::make_unique<SongTrack>(allSongs[songIndex - 1]);
        playlists[plIndex - 1].addTrack(std::move(songCopy));
        std::cout << "Song added to playlist successfully!\n";
    }
}

void AudioSystemManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open file for writing: " << filename << "\n";
        return;
    }

    outFile << "SONGS_COUNT " << allSongs.getSize() << "\n";
    for (size_t i = 0; i < allSongs.getSize(); ++i) {
        outFile << allSongs[i].getId() << " "
            << allSongs[i].getTitle() << " "
            << allSongs[i].getFormat() << " "
            << allSongs[i].getDuration() << " "
            << allSongs[i].getSize() << " "
            << allSongs[i].getPerformer() << " "
            << allSongs[i].getGenre() << "\n";
    }

    outFile << "PODCASTS_COUNT " << allPodcasts.getSize() << "\n";
    for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
        outFile << allPodcasts[i].getId() << " "
            << allPodcasts[i].getTitle() << " "
            << allPodcasts[i].getFormat() << " "
            << allPodcasts[i].getDuration() << " "
            << allPodcasts[i].getSize() << " "
            << allPodcasts[i].getPodcastHost() << " "
            << allPodcasts[i].getPodcastLanguage() << "\n";
    }

    outFile << "VOICEMEMOS_COUNT " << allVoiceMemos.getSize() << "\n";
    for (size_t i = 0; i < allVoiceMemos.getSize(); ++i) {
        auto d = allVoiceMemos[i].getCreationDate();
        outFile << allVoiceMemos[i].getId() << " "
            << allVoiceMemos[i].getTitle() << " "
            << allVoiceMemos[i].getFormat() << " "
            << allVoiceMemos[i].getDuration() << " "
            << allVoiceMemos[i].getSize() << " "
            << d.getYear() << "-" << d.getMonth() << "-" << d.getDay() << " "
            << allVoiceMemos[i].getPriority() << "\n";
    }

    outFile << "PLAYLISTS_COUNT " << playlists.getSize() << "\n";
    for (size_t i = 0; i < playlists.getSize(); ++i) {
        size_t count = playlists[i].getTracksCount();
        outFile << playlists[i].getPlaylistName() << " " << count;

        for (size_t j = 0; j < count; ++j) {
            const AudioTrack* track = playlists[i].getTrack(j);
            if (track != nullptr) {
                if (j == 0) {
                    outFile << " " << track->getId();
                }
                else {
                    outFile << ", " << track->getId();
                }
            }
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "Data saved successfully! All records and playlists were saved to file: " << filename << "\n";
}

void AudioSystemManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw FileNotFoundException(filename);
    }

    allSongs.clear();
    allPodcasts.clear();
    allVoiceMemos.clear();

    std::string marker;
    size_t count = 0;

    while (inFile >> marker) {
        if (marker == "SONGS_COUNT") {
            inFile >> count;
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, performer, genre;
                double duration = 0.0;
                double size = 0.0;

                inFile >> id >> title >> format >> duration >> size >> performer >> genre;
                SongTrack song(id, title, format, duration, size, performer, genre);
                allSongs.push_back(song);
            }
            std::cout << "Loaded " << count << " songs from file.\n";
        }
        else if (marker == "PODCASTS_COUNT") {
            inFile >> count;
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, host, language;
                double duration = 0.0;
                double size = 0.0;

                inFile >> id >> title >> format >> duration >> size >> host >> language;
                PodcastTrack podcast(id, title, format, duration, size, host, language);
                allPodcasts.push_back(podcast);
            }
            std::cout << "Loaded " << count << " podcasts from file.\n";
        }
        else if (marker == "VOICEMEMOS_COUNT") {
            inFile >> count;
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, dateStr;
                double duration = 0.0;
                double size = 0.0;
                int priority = 1;

                inFile >> id >> title >> format >> duration >> size >> dateStr >> priority;

                int year = 2026, month = 1, day = 1;
                char dash1, dash2;
                std::stringstream ss(dateStr);
                ss >> year >> dash1 >> month >> dash2 >> day;

                Date date(year, month, day);
                VoiceMemoTrack memo(id, title, format, duration, size, date, priority);
                allVoiceMemos.push_back(memo);
            }
            std::cout << "Loaded " << count << " voice memos from file.\n";
        }
        else if (marker == "PLAYLISTS_COUNT") {
            inFile >> count;
            for (size_t i = 0; i < count; ++i) {
                std::string plName;
                size_t trackCount;
                inFile >> plName >> trackCount;

                Playlist pl(plName);
                for (size_t j = 0; j < trackCount; ++j) {
                    std::string trackId;
                    inFile >> trackId;

                    if (!trackId.empty() && trackId.back() == ',') {
                        trackId.pop_back();
                    }

                    for (size_t s = 0; s < allSongs.getSize(); ++s) {
                        if (allSongs[s].getId() == trackId) {
                            auto songCopy = std::make_unique<SongTrack>(allSongs[s]);
                            pl.addTrack(std::move(songCopy));
                            break;
                        }
                    }
                }
                playlists.push_back(pl);
            }
            std::cout << "Loaded " << count << " playlists from file.\n";
        }
    }

    inFile.close();
    std::cout << "Data loaded successfully from " << filename << "!\n";
}

void AudioSystemManager::handleDeleteMenu() {
    int deleteChoice = 0;
    std::cout << "\n--- Delete Menu ---\n";
    std::cout << "1. Delete Audio Track (Song / Podcast / Voice Memo)\n";
    std::cout << "2. Delete Playlist\n";
    std::cout << "Enter your choice: ";
    std::cin >> deleteChoice;

    if (deleteChoice == 1) {
        handleDeleteTrack();
    }
    else if (deleteChoice == 2) {
        handleDeletePlaylist();
    }
    else {
        std::cout << "Invalid choice!\n";
    }
}

void AudioSystemManager::handleDeleteTrack() {
    int typeChoice = 0;
    std::cout << "\n--- Delete Track ---\n";
    std::cout << "1. Delete Song\n";
    std::cout << "2. Delete Podcast\n";
    std::cout << "3. Delete Voice Memo\n";
    std::cout << "Enter type to delete from: ";
    std::cin >> typeChoice;

    if (typeChoice == 1) {
        if (allSongs.isEmpty()) { std::cout << "No songs available.\n"; return; }
        std::cout << "Select song index to delete:\n";
        for (size_t i = 0; i < allSongs.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allSongs[i].printInfo();
        }
        size_t idx;
        std::cin >> idx;
        if (idx >= 1 && idx <= allSongs.getSize()) {
            allSongs.remove(idx - 1);
            std::cout << "Song deleted successfully!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else if (typeChoice == 2) {
        if (allPodcasts.isEmpty()) { std::cout << "No podcasts available.\n"; return; }
        std::cout << "Select podcast index to delete:\n";
        for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allPodcasts[i].printInfo();
        }
        size_t idx;
        std::cin >> idx;
        if (idx >= 1 && idx <= allPodcasts.getSize()) {
            allPodcasts.remove(idx - 1);
            std::cout << "Podcast deleted successfully!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else if (typeChoice == 3) {
        if (allVoiceMemos.isEmpty()) { std::cout << "No voice memos available.\n"; return; }
        std::cout << "Select voice memo index to delete:\n";
        for (size_t i = 0; i < allVoiceMemos.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allVoiceMemos[i].printInfo();
        }
        size_t idx;
        std::cin >> idx;
        if (idx >= 1 && idx <= allVoiceMemos.getSize()) {
            allVoiceMemos.remove(idx - 1);
            std::cout << "Voice memo deleted successfully!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else {
        std::cout << "Invalid choice!\n";
    }
}

void AudioSystemManager::handleDeletePlaylist() {
    if (playlists.isEmpty()) {
        std::cout << "No playlists available to delete.\n";
        return;
    }

    std::cout << "\n--- Delete Playlist ---\n";
    for (size_t i = 0; i < playlists.getSize(); ++i) {
        std::cout << i + 1 << ". " << playlists[i].getPlaylistName() << "\n";
    }
    std::cout << "Select playlist index to delete: ";
    size_t plIdx;
    std::cin >> plIdx;

    if (plIdx < 1 || plIdx > playlists.getSize()) {
        std::cout << "Invalid playlist index!\n";
        return;
    }

    std::cout << "What do you want to do with the tracks inside this playlist?\n";
    std::cout << "1. Keep them in the system (unassigned)\n";
    std::cout << "2. Delete them from the system entirely\n";
    std::cout << "Enter choice: ";
    int actionChoice;
    std::cin >> actionChoice;

    if (actionChoice == 2) {
        Playlist& plToDelete = playlists[plIdx - 1];
        for (size_t j = 0; j < plToDelete.getTracksCount(); ++j) {
            const AudioTrack* tr = plToDelete.getTrack(j);
            if (tr != nullptr) {
                std::string targetId = tr->getId();
                for (size_t s = 0; s < allSongs.getSize(); ++s) {
                    if (allSongs[s].getId() == targetId) {
                        allSongs.remove(s);
                        break;
                    }
                }
            }
        }
    }

    playlists.remove(plIdx - 1);
    std::cout << "Playlist deleted successfully!\n";
}