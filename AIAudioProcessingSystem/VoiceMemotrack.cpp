#include "VoiceMemoTrack.h"
#include <iostream>
#include <iomanip>

VoiceMemoTrack::VoiceMemoTrack() : AudioTrack(), creationDate(), priority(1) {}

VoiceMemoTrack::VoiceMemoTrack(std::string id, std::string title, std::string format, double duration, double size,
    Date creationDate, int priority)
    : AudioTrack(id, title, format, duration, size), creationDate(creationDate)
{
    setPriority(priority);
}

Date VoiceMemoTrack::getCreationDate() const { return creationDate; }
int VoiceMemoTrack::getPriority() const { return priority; }

void VoiceMemoTrack::setCreationDate(Date date) {
    this->creationDate = date;
}

void VoiceMemoTrack::setPriority(int priority) {
    if (priority >= 1 && priority <= 5) {
        this->priority = priority;
    }
    else {
        this->priority = 1;
    }
}

void VoiceMemoTrack::analyze() {
    std::cout << "[Voice Memo Analysis] Track: " << getTitle()
        << " | Date: " << creationDate
        << " | Priority: " << priority
        << " -> Status: Noise reduction and compression applied." << std::endl;
}

void VoiceMemoTrack::printInfo() const {
    std::cout << "Voice Memo: " << getTitle()
        << " | Date: " << creationDate
        << " | Priority: Level " << priority << std::endl;
}

AudioTrack* VoiceMemoTrack::clone() const {
    return new VoiceMemoTrack(*this);
}