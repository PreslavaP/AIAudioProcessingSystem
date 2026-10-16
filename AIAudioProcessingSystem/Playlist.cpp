#include "Playlist.h"
#include <iostream>
#include <algorithm>

Playlist::Playlist() : playlistName("Default Playlist") {}
Playlist::Playlist(std::string name) {
	setPlaylistName(name);
}

Playlist& Playlist::operator=(const Playlist& other) {
	if (this == &other) {
		return *this;
	}

	playlistName = other.playlistName;
	tracks.clear(); 

	for (const auto& track : other.tracks) {
		if (track) {
			tracks.push_back(std::unique_ptr<AudioTrack>(track->clone()));
		}
	}

	return *this;
}

void Playlist::addTrack(std::unique_ptr<AudioTrack> track) {
	if (track) {
		tracks.push_back(std::move(track));
	}
}

void Playlist::removeTrack(size_t index) {
	if (index < tracks.size()) {
		tracks.erase(tracks.begin() + index);
	}
}

double Playlist::getTotalDuration() const {
	double total = 0.0;
	for (const auto& track : tracks) {
		if (track) {
			total += track->getDuration();
		}
	}
	return total;
}

void Playlist::sortByDuration() {
	std::sort(tracks.begin(), tracks.end(), [](const auto& a, const auto& b) {
		return a->getDuration() < b->getDuration();
	});
}

void Playlist::softByTitle() {
	std::sort(tracks.begin(), tracks.end(), [](const auto& a, const auto& b) {
		return a->getTitle() < b->getTitle();
		});
}

void Playlist::printPlaylist() const {
	std::cout << "Playlist: " << playlistName << " (Tracks: " << tracks.size() << ")" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	for (size_t i = 0; i < tracks.size(); ++i) {
		std::cout << "[" << i + 1 << "] ";
		tracks[i]->printInfo();
	}
	std::cout << "Total Duration: " << getTotalDuration() << " seconds." << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

std::string Playlist::getPlaylistName() const { return playlistName; }

void Playlist::setPlaylistName(std::string name) {
	if (!name.empty()) {
		playlistName = name;
	}
	else {
		playlistName = "Untitled Playlist";
	}
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
	os << "Playlist Name: " << playlist.playlistName << ", Tracks Count: " << playlist.tracks.size()
		<< ", Total Duration: " << playlist.getTotalDuration() << "s";
	return os;
}