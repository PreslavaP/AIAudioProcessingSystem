#include "AudioTrack.h"
#include <iomanip>

AudioTrack::AudioTrack() : id("UNKNOWN"), title("Untitled"), format("mp3"), duration(0.0), size(0.0) {}

AudioTrack::AudioTrack(std::string id, std::string title, std::string format, double duration, double size) {
	setId(id);
	setTitle(title);
	setFormat(format);
	setDuration(duration);
	setSize(size);
}

AudioTrack::~AudioTrack() {}

std::string AudioTrack::getId() const { return id; }
std::string AudioTrack::getTitle() const { return title; }
std::string AudioTrack::getFormat() const { return format; }
double AudioTrack::getDuration() const { return duration; }
double AudioTrack::getSize() const { return size; }

void AudioTrack::setId(std::string id) {
    if (!id.empty()) {
        this->id = id;
    }
    else {
        this->id = "UNKNOWN_ID";
    }
}

void AudioTrack::setTitle(std::string title) {
    if (!title.empty()) {
        this->title = title;
    }
    else {
        this->title = "Untitled Track";
    }
}

void AudioTrack::setFormat(std::string format) {
    if (!format.empty()) {
        this->format = format;
    }
    else {
        this->format = "mp3";
    }
}

void AudioTrack::setDuration(double duration) {
    if (duration >= 0) {
        this->duration = duration;
    }
    else {
        this->duration = 0.0;
    }
}

void AudioTrack::setSize(double size) {
    if (size >= 0) {
        this->size = size;
    }
    else {
        this->size = 0.0;
    }
}