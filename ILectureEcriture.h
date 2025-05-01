#pragma once
#include <string>

class ILectureEcriture
{
public:
	virtual void lireLabyrinthe(const std::string filePath) = 0;
	virtual void ecrireSolution(const std::string filePath) = 0;
};