#include "AudioSystemManager.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <limits>

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
            choice = -1;
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
    std::cout << "7. Concatenate two audio tracks\n";
    std::cout << "8. Filter tracks by duration or language\n";
    std::cout << "9.Add subtitle/segment to a track\n";
    std::cout << "10. Search text (in Song/Podcast/Memo)\n";
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
    case 7:
        handleConcatenation();
        break;
    case 8:
        handleFilterTracks();
        break;
    case 9:
        handleAddSegments();
        break;
    case 10:
        handleTextSearch();
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
    const_cast<AudioSystemManager*>(this)->reIndex();

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

        size_t segCount = allSongs[i].segments.getSize();
        outFile << segCount << "\n";
        for (size_t s = 0; s < segCount; ++s) {
            auto start = allSongs[i].segments[s].getStartTime();
            auto end = allSongs[i].segments[s].getEndTime();
            outFile << start.getHours() << " " << start.getMinutes() << " " << start.getSeconds() << " " << start.getMilliseconds() << " "
                << end.getHours() << " " << end.getMinutes() << " " << end.getSeconds() << " " << end.getMilliseconds() << "\n";
            outFile << allSongs[i].segments[s].getText() << "\n";
        }
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

        size_t segCount = allPodcasts[i].segments.getSize();
        outFile << segCount << "\n";
        for (size_t s = 0; s < segCount; ++s) {
            auto start = allPodcasts[i].segments[s].getStartTime();
            auto end = allPodcasts[i].segments[s].getEndTime();
            outFile << start.getHours() << " " << start.getMinutes() << " " << start.getSeconds() << " " << start.getMilliseconds() << " "
                << end.getHours() << " " << end.getMinutes() << " " << end.getSeconds() << " " << end.getMilliseconds() << "\n";
            outFile << allPodcasts[i].segments[s].getText() << "\n";
        }
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

        size_t segCount = allVoiceMemos[i].segments.getSize();
        outFile << segCount << "\n";
        for (size_t s = 0; s < segCount; ++s) {
            auto start = allVoiceMemos[i].segments[s].getStartTime();
            auto end = allVoiceMemos[i].segments[s].getEndTime();
            outFile << start.getHours() << " " << start.getMinutes() << " " << start.getSeconds() << " " << start.getMilliseconds() << " "
                << end.getHours() << " " << end.getMinutes() << " " << end.getSeconds() << " " << end.getMilliseconds() << "\n";
            outFile << allVoiceMemos[i].segments[s].getText() << "\n";
        }
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
    playlists.clear();

    std::string marker;
    size_t count = 0;

    while (inFile >> marker) {
        if (marker == "SONGS_COUNT") {
            if (!(inFile >> count))
            {
                throw InvalidFileFormatException(filename);
            }
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, performer, genre;
                double duration = 0.0;
                double size = 0.0;

                if (!(inFile >> id >> title >> format >> duration
                    >> size >> performer >> genre))
                {
                    throw InvalidFileFormatException(filename);
                }
                SongTrack song(id, title, format, duration, size, performer, genre);

                if (inFile >> std::ws && isdigit(inFile.peek())) {
                    size_t segCount = 0;
                    inFile >> segCount;
                    for (size_t s = 0; s < segCount; ++s) {
                        int sh, sm, ss, sms, eh, em, es, ems;
                        if (!(inFile >> sh >> sm >> ss >> sms
                            >> eh >> em >> es >> ems))
                        {
                            throw InvalidFileFormatException(filename);
                        }
                        std::string segText;
                        inFile.ignore(
                            std::numeric_limits<std::streamsize>::max(), '\n'
                        );

                        if (!std::getline(inFile, segText))
                        {
                            throw InvalidFileFormatException(filename);
                        }

                        Timestamp start(sh, sm, ss, sms);
                        Timestamp end(eh, em, es, ems);
                        AudioSegment segment(start, end, segText);
                        song.addSegment(segment);
                    }
                }

                allSongs.push_back(song);
            }
            std::cout << "Loaded " << count << " songs from file.\n";
        }
        else if (marker == "PODCASTS_COUNT") {
            if (!(inFile >> count))
            {
                throw InvalidFileFormatException(filename);
            }
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, host, language;
                double duration = 0.0;
                double size = 0.0;

                if (!(inFile >> id >> title >> format >> duration
                    >> size >> host >> language))
                {
                    throw InvalidFileFormatException(filename);
                }
                PodcastTrack podcast(id, title, format, duration, size, host, language);

                if (inFile >> std::ws && isdigit(inFile.peek())) {
                    size_t segCount = 0;
                    inFile >> segCount;
                    for (size_t s = 0; s < segCount; ++s) {
                        int sh, sm, ss, sms, eh, em, es, ems;
                        if (!(inFile >> sh >> sm >> ss >> sms
                            >> eh >> em >> es >> ems))
                        {
                            throw InvalidFileFormatException(filename);
                        }
                        std::string segText;
                        inFile.ignore(
                            std::numeric_limits<std::streamsize>::max(), '\n'
                        );

                        if (!std::getline(inFile, segText))
                        {
                            throw InvalidFileFormatException(filename);
                        }

                        Timestamp start(sh, sm, ss, sms);
                        Timestamp end(eh, em, es, ems);
                        AudioSegment segment(start, end, segText);
                        podcast.addSegment(segment);
                    }
                }

                allPodcasts.push_back(podcast);
            }
            std::cout << "Loaded " << count << " podcasts from file.\n";
        }
        else if (marker == "VOICEMEMOS_COUNT") {
            if (!(inFile >> count))
            {
                throw InvalidFileFormatException(filename);
            }
            for (size_t i = 0; i < count; ++i) {
                std::string id, title, format, dateStr;
                double duration = 0.0;
                double size = 0.0;
                int priority = 1;

                if (!(inFile >> id >> title >> format >> duration
                    >> size >> dateStr >> priority))
                {
                    throw InvalidFileFormatException(filename);
                }

                int year, month, day;
                char dash1, dash2;

                std::stringstream ss(dateStr);

                if (!(ss >> year >> dash1 >> month >> dash2 >> day)
                    || dash1 != '-' || dash2 != '-')
                {
                    throw InvalidFileFormatException(filename);
                }

                Date date(year, month, day);
                VoiceMemoTrack memo(id, title, format, duration, size, date, priority);

                if (inFile >> std::ws && isdigit(inFile.peek())) {
                    size_t segCount = 0;
                    inFile >> segCount;
                    for (size_t s = 0; s < segCount; ++s) {
                        int sh, sm, ss, sms, eh, em, es, ems;
                        if (!(inFile >> sh >> sm >> ss >> sms
                            >> eh >> em >> es >> ems))
                        {
                            throw InvalidFileFormatException(filename);
                        }
                        std::string segText;
                        inFile.ignore(
                            std::numeric_limits<std::streamsize>::max(), '\n'
                        );

                        if (!std::getline(inFile, segText))
                        {
                            throw InvalidFileFormatException(filename);
                        }

                        Timestamp start(sh, sm, ss, sms);
                        Timestamp end(eh, em, es, ems);
                        AudioSegment segment(start, end, segText);
                        memo.addSegment(segment);
                    }
                }

                allVoiceMemos.push_back(memo);
            }
            std::cout << "Loaded " << count << " voice memos from file.\n";
        }
        else if (marker == "PLAYLISTS_COUNT") {
            if (!(inFile >> count))
            {
                throw InvalidFileFormatException(filename);
            }
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

                    bool foundAndAdded = false;

                    for (size_t s = 0; s < allSongs.getSize(); ++s) {
                        if (allSongs[s].getId() == trackId) {
                            auto songCopy = std::make_unique<SongTrack>(allSongs[s]);
                            pl.addTrack(std::move(songCopy));
                            foundAndAdded = true;
                            break;
                        }
                    }

                    if (!foundAndAdded) {
                        for (size_t p = 0; p < allPodcasts.getSize(); ++p) {
                            if (allPodcasts[p].getId() == trackId) {
                                auto podcastCopy = std::make_unique<PodcastTrack>(allPodcasts[p]);
                                pl.addTrack(std::move(podcastCopy));
                                foundAndAdded = true;
                                break;
                            }
                        }
                    }

                    if (!foundAndAdded) {
                        for (size_t m = 0; m < allVoiceMemos.getSize(); ++m) {
                            if (allVoiceMemos[m].getId() == trackId) {
                                auto memoCopy = std::make_unique<VoiceMemoTrack>(allVoiceMemos[m]);
                                pl.addTrack(std::move(memoCopy));
                                foundAndAdded = true;
                                break;
                            }
                        }
                    }
                }
                playlists.push_back(pl);
            }
            std::cout << "Loaded " << count << " playlists from file.\n";
        }
        else
        {
            throw InvalidFileFormatException(filename);
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

void AudioSystemManager::handleConcatenation() {
    if (allSongs.getSize() < 2) {
        std::cout << "You need at least 2 songs in the system to concatenate them.\n";
        return;
    }

    std::cout << "\n--- Concatenate Two Songs ---\n";
    for (size_t i = 0; i < allSongs.getSize(); ++i)
    {
        std::cout << i + 1 << ". ";
        allSongs[i].printInfo();
    }

    size_t index1, index2;
    std::cout << "Enter the index of the first song: ";
    std::cin >> index1;
    std::cout << "Enter the index of the second song: ";
    std::cin >> index2;

    if (index1 >= 1 && index1 <= allSongs.getSize() && index2 >= 1 && index2 <= allSongs.getSize()) {
        std::unique_ptr<AudioTrack> combined =
            allSongs[index1 - 1] + allSongs[index2 - 1];

        if (combined != nullptr)
        {
            SongTrack* castedSong =
                dynamic_cast<SongTrack*>(combined.get());

            if (castedSong != nullptr)
            {
                allSongs.push_back(*castedSong);

                std::cout << "Tracks concatenated successfully! "
                    << "A new combined song was created.\n";

                castedSong->printInfo();
            }
        }
    }
}

void AudioSystemManager::handleFilterTracks() const {
    int filterChoice = 0;
    std::cout << "\n--- Filter Tracks ---\n";
    std::cout << "1. Filter by maximum duration (seconds)\n";
    std::cout << "2. Filter podcasts by language\n";
    std::cout << "\nEnter your choice: ";
    std::cin >> filterChoice;

    if (filterChoice == 1) {
        double maxDuration;
        std::cout << "Enter maximum duration (in seconds): ";
        std::cin >> maxDuration;

        std::cout << "\n--- Songs matching duration <= " << maxDuration << "s ---\n";
        bool songsFound = false;
        for (size_t i = 0; i < allSongs.getSize(); ++i) {
            if (allSongs[i].getDuration() <= maxDuration) {
                allSongs[i].printInfo();
                songsFound = true;
            }
        }
        if (!songsFound) {
            std::cout << "No songs found in this duration.\n";
        }
       

        std::cout << "\n--- Podcasts matching duration <= " << maxDuration << "s ---\n";
        bool podcastFound = false;
        for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
            if (allPodcasts[i].getDuration() <= maxDuration) {
                allPodcasts[i].printInfo();
                podcastFound = true;
            }
        }
        if(!podcastFound) {
            std::cout << "No podcasts found in this duration.\n";
        }
    }
    else if (filterChoice == 2) {
        std::string targetLang;
        std::cout << "Enter language (e.g. English, Bulgarian): ";
        std::cin >> targetLang;

        std::string lowerTargetLang = targetLang;
        for (char& c : lowerTargetLang) {
            c = std::tolower(static_cast<unsigned char>(c));
        }

        std::cout << "\n--- Podcasts in language: " << targetLang << " ---\n";
        bool found = false;
        for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
            std::string podcastLang = allPodcasts[i].getPodcastLanguage();

            std::string lowerPodcastLang = podcastLang;
            for (char& c : lowerPodcastLang) {
                c = std::tolower(static_cast<unsigned char>(c));
            }

            if (lowerPodcastLang == lowerTargetLang) {
                allPodcasts[i].printInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No podcasts found for this language.\n";
        }
    }
    else {
        std::cout << "Invalid choice!\n";
    }
}

void AudioSystemManager::handleAddSegments() {
    int typeChoice = 0;
    std::cout << "\n--- Add Subtitle/Segment ---\n";
    std::cout << "1. Add to a Song\n";
    std::cout << "2. Add to a Podcast\n";
    std::cout << "3. Add to a Voice Memo\n";
    std::cout << "Enter type: ";
    std::cin >> typeChoice;

    if (typeChoice == 1 && !allSongs.isEmpty()) {
        for (size_t i = 0; i < allSongs.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allSongs[i].printInfo();
        }
        size_t index;
        std::cout << "Select song index: ";
        std::cin >> index;
        if (index >= 1 && index <= allSongs.getSize()) {
            int startHours, startMinutes, startSeconds, startMilliseconds;
            int endHours, endMinutes, endSeconds, endMilliseconds;
            std::string subtitleText;

            std::cout << "Enter Start Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> startHours >> startMinutes >> startSeconds >> startMilliseconds;

            std::cout << "Enter End Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> endHours >> endMinutes >> endSeconds >> endMilliseconds;

            std::cout << "Enter Subtitle Text: ";
            std::cin.ignore();
            std::getline(std::cin, subtitleText);

            Timestamp startTime(startHours, startMinutes, startSeconds, startMilliseconds);
            Timestamp endTime(endHours, endMinutes, endSeconds, endMilliseconds);
            AudioSegment segment(startTime, endTime, subtitleText);

            allSongs[index - 1].addSegment(segment);
            std::cout << "Segment added successfully to song!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else if (typeChoice == 2 && !allPodcasts.isEmpty()) {
        for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allPodcasts[i].printInfo();
        }
        size_t index;
        std::cout << "Select podcast index: ";
        std::cin >> index;
        if (index >= 1 && index <= allPodcasts.getSize()) {
            int startHours, startMinutes, startSeconds, startMilliseconds;
            int endHours, endMinutes, endSeconds, endMilliseconds;
            std::string subtitleText;

            std::cout << "Enter Start Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> startHours >> startMinutes >> startSeconds >> startMilliseconds;

            std::cout << "Enter End Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> endHours >> endMinutes >> endSeconds >> endMilliseconds;

            std::cout << "Enter Subtitle Text: ";
            std::cin.ignore();
            std::getline(std::cin, subtitleText);

            Timestamp startTime(startHours, startMinutes, startSeconds, startMilliseconds);
            Timestamp endTime(endHours, endMinutes, endSeconds, endMilliseconds);
            AudioSegment segment(startTime, endTime, subtitleText);

            allPodcasts[index - 1].addSegment(segment);
            std::cout << "Segment added successfully to podcast!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else if (typeChoice == 3 && !allVoiceMemos.isEmpty()) {
        for (size_t i = 0; i < allVoiceMemos.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            allVoiceMemos[i].printInfo();
        }
        size_t index;
        std::cout << "Select voice memo index: ";
        std::cin >> index;
        if (index >= 1 && index <= allVoiceMemos.getSize()) {
            int startHours, startMinutes, startSeconds, startMilliseconds;
            int endHours, endMinutes, endSeconds, endMilliseconds;
            std::string subtitleText;

            std::cout << "Enter Start Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> startHours >> startMinutes >> startSeconds >> startMilliseconds;

            std::cout << "Enter End Time (Hours Minutes Seconds Milliseconds): ";
            std::cin >> endHours >> endMinutes >> endSeconds >> endMilliseconds;

            std::cout << "Enter Subtitle Text: ";
            std::cin.ignore();
            std::getline(std::cin, subtitleText);

            Timestamp startTime(startHours, startMinutes, startSeconds, startMilliseconds);
            Timestamp endTime(endHours, endMinutes, endSeconds, endMilliseconds);
            AudioSegment segment(startTime, endTime, subtitleText);

            allVoiceMemos[index - 1].addSegment(segment);
            std::cout << "Segment added successfully to voice memo!\n";
        }
        else {
            std::cout << "Invalid index!\n";
        }
    }
    else {
        std::cout << "Invalid choice or no tracks available in this category.\n";
    }
}

void AudioSystemManager::handleTextSearch() const {
    int searchChoice = 0;
    std::cout << "\n--- Text & Subtitle Search Menu ---\n";
    std::cout << "1. Search in Songs Subtitles\n";
    std::cout << "2. Search in Podcasts Subtitles\n";
    std::cout << "3. Search in Voice Memos Subtitles\n";
    std::cout << "4. Search across ALL records Subtitles\n";
    std::cout << "Enter your choice: ";
    std::cin >> searchChoice;

    if (searchChoice < 1 || searchChoice > 4) {
        std::cout << "Invalid choice!\n";
        return;
    }

    std::string keyword;
    std::cout << "Enter keyword or phrase to search for in subtitles: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    if (keyword.empty()) {
        std::cout << "Search keyword cannot be empty!\n";
        return;
    }

    std::cout << "\nSearching subtitles for: \"" << keyword << "\"...\n";
    bool foundAny = false;

    // --- 1. Търсене в субтитрите на песните ---
    if (searchChoice == 1 || searchChoice == 4) {
        for (size_t i = 0; i < allSongs.getSize(); ++i) {
            bool matched = false;
            for (size_t s = 0; s < allSongs[i].segments.getSize(); ++s) {
                if (allSongs[i].segments[s].getText().find(keyword) != std::string::npos) {
                    matched = true;
                    std::cout << "  -> Found in segment: " << allSongs[i].segments[s] << "\n";
                }
            }
            if (matched) {
                std::cout << "[Song Match]: ";
                allSongs[i].printInfo();
                foundAny = true;
            }
        }
    }

    // --- 2. Търсене в субтитрите на подкастите ---
    if (searchChoice == 2 || searchChoice == 4) {
        for (size_t i = 0; i < allPodcasts.getSize(); ++i) {
            bool matched = false;
            for (size_t s = 0; s < allPodcasts[i].segments.getSize(); ++s) {
                if (allPodcasts[i].segments[s].getText().find(keyword) != std::string::npos) {
                    matched = true;
                    std::cout << "  -> Found in segment: " << allPodcasts[i].segments[s] << "\n";
                }
            }
            if (matched) {
                std::cout << "[Podcast Match]: ";
                allPodcasts[i].printInfo();
                foundAny = true;
            }
        }
    }

    // --- 3. Търсене в субтитрите на гласовите бележки ---
    if (searchChoice == 3 || searchChoice == 4) {
        for (size_t i = 0; i < allVoiceMemos.getSize(); ++i) {
            bool matched = false;
            for (size_t s = 0; s < allVoiceMemos[i].segments.getSize(); ++s) {
                if (allVoiceMemos[i].segments[s].getText().find(keyword) != std::string::npos) {
                    matched = true;
                    std::cout << "  -> Found in segment: " << allVoiceMemos[i].segments[s] << "\n";
                }
            }
            if (matched) {
                std::cout << "[Voice Memo Match]: ";
                allVoiceMemos[i].printInfo();
                foundAny = true;
            }
        }
    }

    if (!foundAny) {
        std::cout << "No matching subtitles found for keyword: \"" << keyword << "\".\n";
    }
}

template <typename T>

void AudioSystemManager::reindexContainer(AudioContainer<T>& container, const std::string& prefix) {
    for (size_t i = 0; i < container.getSize(); ++i) {
        std::string numStr = (i + 1 < 10) ? "0" + std::to_string(i + 1) : std::to_string(i + 1);
        std::string newId = prefix + numStr;
        container[i].setId(newId);
    }
}

void AudioSystemManager::reIndex() {
    reindexContainer(allSongs, "S");
    reindexContainer(allPodcasts, "P");
    reindexContainer(allVoiceMemos, "V");
}