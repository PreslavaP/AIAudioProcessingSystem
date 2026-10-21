#pragma once
#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "AudioTrack.h"

class Playlist {
private: 
	std::string playlistName;
	// Колекция от указатели към тракове
	std::vector<std::unique_ptr<AudioTrack>> tracks; 

public:
	Playlist();
	Playlist(std::string name);

	Playlist& operator=(const Playlist& other);

	//Добавяне на трак
	void addTrack(std::unique_ptr<AudioTrack> track);

	//Премахване на трак
	void removeTrack(size_t index);

	//Изчисляване на времетраенето на плейлиста в секунди
	double getTotalDuration() const;

	//Сортиране на тракове
	void sortByDuration();
	void softByTitle();

	//Връща броя на песните в плейлиста
	size_t getTracksCount() const {
		return tracks.size();
	}

	//Връща указател към конкретен трак по индекс (или неговото ID)
	const AudioTrack* getTrack(size_t index) const {
		if (index < tracks.size()) {
			return tracks[index].get();
		}
		return nullptr;
	}


	void printPlaylist() const;

	std::string getPlaylistName() const;
	void setPlaylistName(std::string name);

	friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
};