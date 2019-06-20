#include "ImageTag.h"

/////////////////////
//IMAGE TAG
/////////////////////

ImageTag::ImageTag(const std::string& content, const std::string& description):HTMLTag(content, description) {
}

bool ImageTag::sendVisializedHTMLTagOn(std::ostream& fs) const {

	if (!fs) {
		return false;
	}

	fs << "<img src=" << "\"" << content << "\"" << " descr=" << "\""
	   << description << "\"" << ">" << "\n";

	if (fs.good()) {
		return true;
	}
	else {
		return false;
	}
}

std::string ImageTag::toString() const {
	std::string convertedString
	("Image with description: " + description + " and content: " + content + "\n");

	return convertedString;
}

/////////////////////
//IMAGE TAG CREATOR
/////////////////////

ImageTagCreator::ImageTagCreator():HTMLTagCreator(IMAGE) {
}

HTMLTag* ImageTagCreator::createHTMLTagFromConsole(std::istream& is) const {

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

	return new ImageTag(content, description);
}

HTMLTag* ImageTagCreator::createHTMLTagFromFile(std::istream& is) const {

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

	return new ImageTag(content, description);
}

static ImageTagCreator __;