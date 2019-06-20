#include "HeadingTag.h"

/////////////////////////
//HEADING TAG
/////////////////////////

HeadingTag::HeadingTag(const std::string& content, const std::string& description, size_t headingSize) :
	HTMLTag(content, description), headingSize(0) {

	if (!(headingSize >= 1 && headingSize <= 6)) {
		throw std::invalid_argument("THE ALLOWED HEADING SIZE IS IN THE INTERVAL 1-6!\n");
	}

	setSize(headingSize);
}

bool HeadingTag::sendVisializedHTMLTagOn(std::ostream& fs)const {

	if (!fs) {
		return false;
	}

	fs << "<h" << char(headingSize + '0') << " descr=" << "\"" << description << "\"";
	fs << ">" << content << "</h" << char(headingSize + '0') << ">" << "\n";

	if (fs.good()) {
		return true;
	}
	else {
		return false;
	}
}

std::string HeadingTag::toString() const {
	std::string convertedString
	("Heading with description: " + description +
		", content: " + content + " and size: " + std::to_string(headingSize) + ".\n");
	
	return convertedString;
}

void HeadingTag::setSize(size_t size) {
	this->headingSize = size;
}

//////////////////////////////
//HEADING TAG CREATOR
//////////////////////////////

HeadingTagCreator::HeadingTagCreator() : HTMLTagCreator(HEADING) {//define the type, which belongs to the creator
}

/*
Suggests, that the input stream is in the format <heading size> << description>> <content>
*/
HTMLTag* HeadingTagCreator::createHTMLTagFromConsole(std::istream& is) const {

	if (!is) {
		return nullptr;
	}

	skipSpacesOn(is);

	size_t headingSize;
	is >> headingSize;

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(1);

	skipSpacesOn(is);

	std::string content;
	std::getline(is, content, '\n');

	return new HeadingTag(content, description, headingSize);
}

/*
Suggests, that the input stream is in the standart format of html sintaxis
*/
HTMLTag* HeadingTagCreator::createHTMLTagFromFile(std::istream& is) const {

	if (!is) {
		return nullptr;
	}

	std::string headingSizeStr;
	is >> headingSizeStr;
	size_t headingSize;
	headingSize = std::atoi(headingSizeStr.c_str());

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(7, description.size() - 8);

	skipSpacesOn(is);
	
	std::string content;
	std::getline(is, content, '<');

	is.ignore(SKIPINGSYMBOLS, '\n');

	return new HeadingTag(content, description, headingSize);
}

static HeadingTagCreator __; // the registration in the factory, when the program is started
