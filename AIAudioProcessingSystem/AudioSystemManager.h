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
    ~AudioSystemManager();

    void run();

private:
    void showMenu() const;
    void handleChoice(int choice);

    void handleAddTrack();
    void handleShowAllTracks() const;
    void handlePlaylistManagement();

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};