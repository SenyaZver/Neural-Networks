#pragma once
#include <string>


class SaveableObject {
public:
	virtual void save(std::string filename) = 0;
	virtual void load(std::string filename) = 0;
 };