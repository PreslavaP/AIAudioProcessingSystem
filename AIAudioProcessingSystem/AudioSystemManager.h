#pragma once

#include "AudioContainer.h"
#include "SongTrack.h"
#include "PodcastTrack.h"
#include "VoiceMemoTrack.h"
#include "Playlist.h"
#include <string>

class AudioSystemManager {
private:
    AudioContainer<SongTrack> allSongs;
    AudioContainer<PodcastTrack> allPodcasts;
    AudioContainer<VoiceMemoTrack> allVoiceMemos;
    AudioContainer<Playlist> playlists;

public:
    AudioSystemManager();
    AudioSystemManager(const std::string& filename);
    ~AudioSystemManager();

    void run();

private:
    void showMenu() const;
    void handleChoice(int choice);

    bool isIdUnique(const std::string& id) const;
    void handleAddTrack();
    void handleShowAllTracks() const;
    void handlePlaylistManagement();
    void removeTrackFromAllPlaylists(const std::string& trackId);
    void handleDeleteMenu();
    void handleDeleteTrack();
    void handleDeletePlaylist();
    void handleConcatenation();
    void handleFilterTracks() const;
    void handleAddSegments();
    void handleTextSearch() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};