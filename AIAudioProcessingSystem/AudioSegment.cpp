#include "AudioSegment.h"
#include "Timestamp.h"
#include <iomanip>

AudioSegment::AudioSegment() : startTime(), endTime(), text("") {}

AudioSegment::AudioSegment(const Timestamp& start, const Timestamp& end, std::string text) {
	setStartTime(start);
	setEndTime(end);
	setText(text);
}

Timestamp AudioSegment::getStartTime() const { return startTime; }
Timestamp AudioSegment::getEndTime() const { return endTime; }
std::string AudioSegment::getText() const { return text; }

//Начално време
void AudioSegment::setStartTime(const Timestamp& start) {
	startTime = start;
}

//Крайно време -> крайния момент не предхожда началния
void AudioSegment::setEndTime(const Timestamp& end) {
	if (!(end < startTime)) {
		endTime = end;
	}
	else {
		endTime = startTime;
	}
}

//Не позволява празни редове
void AudioSegment::setText(std::string text) {
	if (!text.empty()) {
		this->text = text;
	}
	else {
		this->text = "[Empty Segment]";
	}
}

//Връща продължителността в милисекунди
long long AudioSegment::getDuration() const {
	return endTime.getTotalMilliseconds() - startTime.getTotalMilliseconds();
}

//Функция за печат в конзолата
std::ostream& operator<<(std::ostream& os, const AudioSegment& segment) {
	os << "[" << segment.startTime << " --> " << segment.endTime << "] \"" << segment.text << "\"";
	return os;
}