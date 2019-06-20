#ifndef LINK_TAG_HEADER_INCLUDED
#define LINK_TAG_HEADER_INCLUDED
#include"HTMLTag.h"
#include"TagType.h"

class LinkTag : public HTMLTag {
public:
	LinkTag(const std::string& content, const std::string& description, const std::string& destination);
	LinkTag(const LinkTag& other) = default;
	LinkTag& operator=(const LinkTag& other) = default;
	~LinkTag() = default;
public:
	bool sendVisializedHTMLTagOn(std::ostream& fs)const;
public:
	std::string toString() const;
private:
	void setDestination(const std::string& destination);
private:
	std::string destination;
};

class LinkTagCreator : public HTMLTagCreator {
public:
	LinkTagCreator();
public:
	HTMLTag* createHTMLTagFromConsole(std::istream& is) const;
	HTMLTag* createHTMLTagFromFile(std::istream& is) const;

};
#endif
