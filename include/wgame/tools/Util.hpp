/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_UTIL_H__
#define __WG_UTIL_H__

#include <iostream>
#include <vector>

typedef std::string String;

String getFilePathExtension(const String & fileName);

unsigned nextInt(unsigned threshold);

float randomProbability();

float randomFloat(float min, float max);

int randomInt(int min, int max);

bool P(float probability);

template <typename T>
T & randomChoice(std::vector<T> & list) {
    return list[nextInt((unsigned) list.size())];
}

#endif
