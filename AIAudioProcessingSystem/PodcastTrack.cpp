#include "PodcastTrack.h" 
#include <ostream>
#include <string>
#include <iostream>

PodcastTrack::PodcastTrack() : AudioTrack(), podcastHost("UNKNOWN"), podcastLanguage("No Language") {}
PodcastTrack::PodcastTrack(std::string id, std::string title, std::string format, double duration, double size,
	std::string host, std::string language)
	: AudioTrack(id, title, format, duration, size) {
	setPodcastHost(host);
	setPodcastLanguage(language);
}

std::string PodcastTrack::getPodcastHost() const { return podcastHost; }
std::string PodcastTrack::getPodcastLanguage() const { return podcastLanguage; }

void PodcastTrack::setPodcastHost(std::string host) {
	if (!host.empty()) {
		podcastHost = host;
	}
	else {
		podcastHost = "UNKNOWN";
	}
}

void PodcastTrack::setPodcastLanguage(std::string language) {
	if (!language.empty()) {
		podcastLanguage = language;
	}
	else {
		podcastLanguage = "No Language";
	}
}

void PodcastTrack::analyze() {
	std::cout << "[Podcast Analysis] Track: " << getTitle()
		<< " | Host: " << podcastHost
		<< " | Language: " << podcastLanguage
		<< " -> Status: Speech transcription completed." << std::endl;
}

void PodcastTrack::printInfo() const {
	std::cout << "Podcast: " << getTitle()
		<< " | Host: " << podcastHost
		<< " | Language: [" << podcastLanguage << "]" << std::endl;
}

AudioTrack* PodcastTrack::clone() const {
	return new PodcastTrack(*this);
}