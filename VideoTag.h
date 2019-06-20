#ifndef VIDEO_TAG_HEADER_INCLUDED
#define VIDEO_TAG_HEADER_INCLUDED

#include"HTMLTag.h"
#include"TagType.h"

class VideoTag : public HTMLTag {
public:
	VideoTag(const std::string& content, const std::string& description);
	VideoTag(const VideoTag& other) = default;
	VideoTag& operator=(const VideoTag& other) = default;
	~VideoTag() = default;
public:
	bool sendVisializedHTMLTagOn(std::ostream& fs)const;
public:
	std::string toString() const;
};

class VideoTagCreator : public HTMLTagCreator {
public:
	VideoTagCreator();
public:
	HTMLTag* createHTMLTagFromConsole(std::istream& is) const;
	HTMLTag* createHTMLTagFromFile(std::istream& is) const;

};
#endif