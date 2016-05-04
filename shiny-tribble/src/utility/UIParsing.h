#pragma once

#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>
#include <map>

namespace utility {
namespace parsing {

class DynamicObject {
public:
	DynamicObject(const std::string& type);

	void addVariable(const std::string& key, const std::string& value);
	std::string getType();
	std::map<std::string, std::string> getVariables();

	bool hasVariable(const std::string& key) const;
	std::string getValue(const std::string& key) const;

private:
	std::string type_;
	std::map<std::string, std::string> variables_;
};

std::vector<DynamicObject*> parse(char* filename);

std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
std::string fullStrip(const std::string& str);

std::vector<DynamicObject*> getObjects(const std::string& fileText);
DynamicObject* createObject(const std::string& rawObject);
void fillObject(DynamicObject* object, std::string& variablesText);

}
}