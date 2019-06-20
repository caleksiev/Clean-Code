#ifndef HEADINGTAG_HEADER_INCLUDED
#define HEADINGTAG_HEADER_INCLUDED
#include"HTMLTag.h"
#include"TagType.h"

class HeadingTag : public HTMLTag {
public:
	HeadingTag(const std::string& content, const std::string& description, size_t headingSize);
	HeadingTag(const HeadingTag& other) = default;
	HeadingTag& operator=(const HeadingTag& other) = default;
	~HeadingTag() = default;
public:
	bool sendVisializedHTMLTagOn(std::ostream& fs)const;
public:
	std::string toString() const;
private:
	void setSize(size_t size);
private:
	size_t headingSize; // in the interval 1-6]
};

class HeadingTagCreator : public HTMLTagCreator {
public:
	HeadingTagCreator();
public:
	HTMLTag* createHTMLTagFromConsole(std::istream& is) const;
	HTMLTag* createHTMLTagFromFile(std::istream& is) const;

};
#endif
