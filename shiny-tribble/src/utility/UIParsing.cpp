#include "UIParsing.h"

using namespace utility;
using namespace parsing;

//DynamicObject MEMBER FUNCTIONS
DynamicObject::DynamicObject(const std::string& type) : type_(type) {

}

std::string DynamicObject::getType() {
	return type_;
}

std::map<std::string, std::string> DynamicObject::getVariables() {
	return variables_;
}

void DynamicObject::addVariable(const std::string& key, const std::string& val) {
	variables_[key] = val;
}

bool DynamicObject::hasVariable(const std::string& key) const {
	return variables_.find(key) != variables_.end();
}

std::string DynamicObject::getValue(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator iter = variables_.find(key);

	if (iter == variables_.end()) return "";
	else return iter->second;
}

//PARSING FUNCTIONS

//Parse a file into a vector of DynamicObjects
std::vector<DynamicObject*> utility::parsing::parse(char* filename) {
	std::vector<DynamicObject*> output;

	std::ifstream in_str(filename);
	if (in_str.good()) {

		std::string wholeFile((std::istreambuf_iterator<char>(in_str)), std::istreambuf_iterator<char>());

		std::vector<DynamicObject*> objects = getObjects(fullStrip(wholeFile));

		for (unsigned int i = 0; i < objects.size(); i++) {
			if (objects[i] != NULL) output.push_back(objects[i]);
		}

	}else {
		std::cerr << "ERROR: Unable to open " << filename << std::endl;
	}

	in_str.close();

	return output;
}

//From the text contained in a file, create DynamicObjects
std::vector<DynamicObject*> utility::parsing::getObjects(const std::string& fileText) {
	//split it into declarations of individual objects
	std::vector<std::string> rawObjects = split(fileText, '}');

	std::vector<DynamicObject*> objects;

	//create an object for each object declaration
	for (unsigned int i = 0; i < rawObjects.size(); i++) {
		objects.push_back(createObject(rawObjects[i]));
	}

	return objects;
}

//Create a DynamicObject from the raw text
DynamicObject* utility::parsing::createObject(const std::string& rawObject) {

	//Split the raw text into the type of object (BUTTON, TEXTBOX, etc.) and the body (containing variables)
	std::vector<std::string> objTypeAndBody = split(rawObject, '{');

	if (objTypeAndBody.size() < 1) {
		std::cerr << "SYNTAX ERROR: Extra '}'?;" << std::endl;
		return NULL;
	}

	DynamicObject* object = new DynamicObject(objTypeAndBody[0]);

	//Parse all of the variables into the object
	if (objTypeAndBody.size() > 1) fillObject(object, objTypeAndBody[1]);

	return object;
}

//Parse text into variables for a DynamicObject
void utility::parsing::fillObject(DynamicObject* object, std::string& variablesText) {
	//get each variable assignment; should be separated by semicolons
	std::vector<std::string> variables = split(variablesText, ';');

	std::vector<std::string> currentSplitLine;

	//get each side of the assignment
	for (unsigned int i = 0; i < variables.size(); i++) {
		currentSplitLine = split(variables[i], '=');
		if (currentSplitLine.size() != 2) {
			std::cerr << "SYNTAX ERROR: Malformed line" << std::endl;
			continue;
		}
		object->addVariable(currentSplitLine[0], currentSplitLine[1]);
	}
}

//Credit to Evan Teran via StackOverflow: http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& utility::parsing::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//Credit to Evan Teran via StackOverflow: http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> utility::parsing::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

//Strip a string of all whitespace
//Ignores whitespace within single or double quotes
//Single or double quotes can be escaped with '\'
std::string utility::parsing::fullStrip(const std::string& str) {
	std::string result;
	bool ignoringWhitespace = false;
	bool escaped = false;

	for (unsigned int i = 0; i < str.size(); i++) {
		//Check if this char is whitespace
		if ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') && !ignoringWhitespace) continue;
		//Check if this char is quotation marks
		if ((str[i] == '"' || str[i] == '\'') && !escaped) { ignoringWhitespace = !ignoringWhitespace; continue; }
		//Check if this char is an escape character
		if ((str[i] == '\\') && !escaped) { escaped = true; std::cout << "test\n"; continue; }
		result.push_back(str[i]);

		if (escaped) escaped = false;
	}

	return result;
}
