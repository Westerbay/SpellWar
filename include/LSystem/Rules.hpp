/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __RULES__
#define __RULES__
 
#include <string>
 
class Rules {
public:
	virtual std::string nextSuccessor(char predecessor) = 0;
};
 
#endif
 
