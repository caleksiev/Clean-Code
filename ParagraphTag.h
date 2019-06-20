#ifndef PARTAG_HEADER_INCLUDED
#define PARTAG_HEADER_INCLUDED
#include"HTMLTag.h"
#include"TagType.h"

class ParagraphTag : public HTMLTag {
public:
	ParagraphTag(const std::string& content, const std::string& description);
	ParagraphTag(const ParagraphTag& other) = default;
	ParagraphTag& operator=(const ParagraphTag& other) = default;
	~ParagraphTag() = default;
public:
	bool sendVisializedHTMLTagOn(std::ostream& fs)const;
public:
	std::string toString() const;
};

class ParagraphTagCreator : public HTMLTagCreator {
public:
	ParagraphTagCreator();
public:
	HTMLTag* createHTMLTagFromConsole(std::istream& is) const;
	HTMLTag* createHTMLTagFromFile(std::istream& is) const;

};
#endif
