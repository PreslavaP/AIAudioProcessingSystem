#include "AudioSystemManager.h"
#include "Exceptions.h"
#include <iostream>

int main() {
    AudioSystemManager systemManager;
    try {
        systemManager.run();
    }
    catch (const AudioSystemException& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}