#pragma once
#include "AudioTrack.h" 
#include <ostream>
#include <string>

class PodcastTrack : public AudioTrack{
private: 
	std::string podcastHost;
	std::string podcastLanguage;

public:
	PodcastTrack();
	PodcastTrack(std::string id, std::string title, std::string format, double duration, double size,
		std::string podcastHost, std::string podcastLanguage);

	std::string getPodcastHost() const;
	std::string getPodcastLanguage() const;

	void setPodcastHost(std::string host);
	void setPodcastLanguage(std::string language);

	void analyze() override;
	void printInfo() const override;
	AudioTrack* clone() const override;

	friend std::ostream& operator<<(std::ostream& os, const PodcastTrack& track);
};