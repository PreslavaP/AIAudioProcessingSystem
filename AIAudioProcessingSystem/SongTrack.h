#pragma once
#include "AudioTrack.h"
#include <ostream>
#include <string>

class SongTrack : public AudioTrack {
private:
	std::string performer;
	std::string genre;

public:
	SongTrack();
	SongTrack(std::string id, std::string title, std::string format, double duration, double size, 
		std::string performer, std::string genre);

	std::string getPerformer() const;
	std::string getGenre() const;

	void setPerformer(std::string performer);
	void setGenre(std::string genre);

	void analyze() override;
	void printInfo() const override;
	AudioTrack* clone() const override;

	friend std::ostream& operator<<(std::ostream& os, const SongTrack& segment);
};