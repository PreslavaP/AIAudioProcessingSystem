#pragma once
#include <string>
#include <ostream>
#include "AudioContainer.h"
#include "AudioSegment.h"

class AudioTrack {
protected:
    //Член-променливи
    std::string id;
    std::string title;
    std::string format;
    double duration;
    double size;

private:
    AudioContainer<AudioSegment> segments;

public:
    //Конструктори
    AudioTrack();
    AudioTrack(std::string id, std::string title, std::string format, double duration, double size);

    //Виртуален деструктор
    virtual ~AudioTrack();

    //Гетери
    std::string getId() const;
    std::string getTitle() const;
    std::string getFormat() const;
    double getDuration() const;
    double getSize() const;

    //Сетери
    void setId(std::string id);
    void setTitle(std::string title);
    void setFormat(std::string format);
    void setDuration(double duration);
    void setSize(double size);

    std::unique_ptr<AudioTrack> operator+(const AudioTrack& other) const;

    void addSegment(const AudioSegment& segment);

    AudioContainer<AudioSegment>& getSegments() {
        return segments;
    }

    const AudioContainer<AudioSegment>& getSegments() const {
        return segments;
    }

    virtual void analyze() = 0;
    virtual void printInfo() const = 0;
    virtual AudioTrack* clone() const = 0;
};