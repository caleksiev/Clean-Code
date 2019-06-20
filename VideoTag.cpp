#include "VideoTag.h"

/////////////////////
//VIDEO TAG
/////////////////////

VideoTag::VideoTag(const std::string& content, const std::string& description):HTMLTag(content,description) {
}

bool VideoTag::sendVisializedHTMLTagOn(std::ostream& fs) const
{
	if (!fs) {
		return false;
	}

	fs << "<iframe src=" << "\"" << content << "\"" << " descr=" << "\"" << description << "\"";
	fs << ">" << "</iframe>" << "\n";

	if (fs.good()) {
		return true;
	}
	else {
		return false;
	}
}

std::string VideoTag::toString() const {

	std::string convertedString
	("Video with description: " + description + " and content: " + content + "\n");

	return convertedString;
}

/////////////////////
//VIDEO TAG CREATOR
/////////////////////

VideoTagCreator::VideoTagCreator():HTMLTagCreator(VIDEO) {
}

HTMLTag* VideoTagCreator::createHTMLTagFromConsole(std::istream& is) const {

	if (!is) {
		return nullptr;
	}

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(1);

	skipSpacesOn(is);

	std::string content;
	is >> content;

	return new VideoTag(content, description);
}

HTMLTag* VideoTagCreator::createHTMLTagFromFile(std::istream& is) const {
	if (!is) {
		return nullptr;
	}

	skipSpacesOn(is);

	std::string content;
	std::getline(is, content, ' ');
	content = content.substr(5, content.size() - 6);

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(7, description.size() - 8);

	is.ignore(SKIPINGSYMBOLS, '\n');

	return new VideoTag(content, description);
}

static VideoTagCreator __;
