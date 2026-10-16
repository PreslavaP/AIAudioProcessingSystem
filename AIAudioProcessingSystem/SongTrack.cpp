#include "SongTrack.h"
#include <iomanip>
#include <iostream>

SongTrack::SongTrack() : AudioTrack(), performer("UNKNOWN"), genre("No Genre") {}
SongTrack::SongTrack(std::string id, std::string title, std::string format, double duration, double size, 
	std::string performer, std::string genre) 
	: AudioTrack(id, title, format, duration, size) {
	setPerformer(performer);
	setGenre(genre);
}

std::string SongTrack::getPerformer() const { return performer; }
std::string SongTrack::getGenre() const { return genre; }

void SongTrack::setPerformer(std::string performer) {
	if (!performer.empty()) {
		this->performer = performer;
	}
	else {
		this->performer = "[No Performer]";
	}
}

void SongTrack::setGenre(std::string genre) {
	if (!genre.empty()) {
		this->genre = genre;
	}
	else {
		this->genre = "[No Genre]";
	}
}

void SongTrack::analyze() {
	std::cout << "[Song Analysis] Track: " << getTitle()
		<< " | Genre: " << genre
		<< " | Duration: " << getDuration() << "s"
		<< " -> Status: Beats per minute (BPM) detected successfully." << std::endl;
}

void SongTrack::printInfo() const {
	std::cout << "Song: " << getTitle() << " by " << performer << " [" << genre << "]" << std::endl;
}

AudioTrack* SongTrack::clone() const {
	return new SongTrack(*this);
}