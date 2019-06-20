#ifndef HTMLTAG_HEADER_INCLUDED
#define HTMLTAG_HEADER_INCLUDED

#include<string>
#include <stdexcept>
#include<iostream>
#include"TagType.h"
#include<fstream>
const int SKIPINGSYMBOLS = 4096;
class HTMLTag {
public:
	HTMLTag(const std::string& content, const std::string& description);
	HTMLTag(const HTMLTag& other) = default;
	HTMLTag& operator= (const HTMLTag& other) = default;
	virtual ~HTMLTag(){}
public:
	//transform the tag into html sintaxis
	virtual bool sendVisializedHTMLTagOn(std::ostream& fs)const = 0;
	virtual std::string toString() const = 0; // more info about the tag
public:
	std::string getDescription() const;
private:
	void setContent(const std::string& content);
	void setDescription(const std::string& description);
protected:
	std::string description;
	std::string content;
};

//The class is needed for realization of the abstract factory

class HTMLTagCreator
{
public:
	HTMLTagCreator(const TagType& type);
	virtual ~HTMLTagCreator(){}
public:
	//convert enum type into string
	const char* getTypeString()const;
	const char* getTypeHTMLSign()const;
public:
	//A purely virtual methods, carrying the knowledge to create a specific tag from the input stream
	virtual HTMLTag* createHTMLTagFromConsole(std::istream& is) const = 0;
	virtual HTMLTag* createHTMLTagFromFile(std::istream& is) const = 0;
protected:
	void skipSpacesOn(std::istream& is) const;
private:
	TagType type; //by the type each creator is uniquely defined
};
#endif
