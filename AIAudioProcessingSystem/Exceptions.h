#pragma once

#include <exception>
#include <string>

class AudioSystemException : public std::exception {
protected:
	std::string message;

public: 
    AudioSystemException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileNotFoundException : public AudioSystemException {
public:
    FileNotFoundException(const std::string& filename)
        : AudioSystemException("Error: Could not open file: " + filename) {
    }
};