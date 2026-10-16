#pragma once
#include <string>
#include <ostream>

class AudioTrack {
protected:
    //Член-променливи
    std::string id;
    std::string title;
    std::string format;
    double duration;
    double size;

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

    virtual void analyze() = 0;
    virtual void printInfo() const = 0;
    virtual AudioTrack* clone() const = 0;
};