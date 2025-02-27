/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/tools/Util.hpp>

std::string getFilePathExtension(const std::string & fileName) {
    if (fileName.find_last_of(".") != std::string::npos)
        return fileName.substr(fileName.find_last_of(".") + 1);
    return "";
}

unsigned nextInt(unsigned threshold) {
    return rand() % threshold;
}

float random() {
    return (float) rand() / RAND_MAX;
}

float randomFloat(float min, float max) {
    if (min > max) std::swap(min, max);
    return random() * (max - min) + min;
}

int randomInt(int min, int max) {
    if (min > max) std::swap(min, max);
    return nextInt(max - min + 1) + min;
}

bool P(float probability) {
    return random() < probability;
}


