#ifndef IMAGETAG_HEADER_INCLUDED
#define IMAGETAG_HEADER_INCLUDED

#include"HTMLTag.h"
#include"TagType.h"

class ImageTag : public HTMLTag {
public:
	ImageTag(const std::string& content, const std::string& description);
	ImageTag(const ImageTag& other) = default;
	ImageTag& operator=(const ImageTag& other) = default;
	~ImageTag() = default;
public:
	bool sendVisializedHTMLTagOn(std::ostream& fs)const;
public:
	std::string toString() const;
};

class ImageTagCreator : public HTMLTagCreator {
public:
	ImageTagCreator();
public:
	HTMLTag* createHTMLTagFromConsole(std::istream& is) const;
	HTMLTag* createHTMLTagFromFile(std::istream& is) const;

};
#endif