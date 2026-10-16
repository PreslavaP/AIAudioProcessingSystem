#pragma once
#include "Timestamp.h"

class AudioSegment {
private:
	Timestamp startTime;
	Timestamp endTime;
	std::string text;

public:
	AudioSegment();
	AudioSegment(const Timestamp& start, const Timestamp& end, std::string text);

	Timestamp getStartTime() const;
	Timestamp getEndTime() const;
	std::string getText() const;

	void setStartTime(const Timestamp& start);
	void setEndTime(const Timestamp& end);
	void setText(std::string text);

	long long getDuration() const;
	friend std::ostream& operator<<(std::ostream& os, const AudioSegment& segment);
};