#pragma once
#include <string>
#include <ostream>
#include "AudioTrack.h"
#include "Date.h"

class VoiceMemoTrack : public AudioTrack {
private:
	Date creationDate;
	int priority;

public:
	VoiceMemoTrack();
	VoiceMemoTrack(std::string id, std::string title, std::string format, double duration, double size,
		Date creationDate, int priority);

	Date getCreationDate() const;
	int getPriority() const;

	void setCreationDate(Date date);
	void setPriority(int priority);

	void analyze() override;
	void printInfo() const override;
	AudioTrack* clone() const override;

	friend std::ostream& operator<<(std::ostream& os, const VoiceMemoTrack& track);
};