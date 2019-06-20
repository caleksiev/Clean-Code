#include "LinkTag.h"

/////////////////////
//LINK TAG
/////////////////////

LinkTag::LinkTag(const std::string& content, const std::string& description, const std::string& destination) :
	HTMLTag(content, description) {

	if (destination.empty())
		throw std::invalid_argument("Destination is empty!\n");

	setDestination(destination);
}

bool LinkTag::sendVisializedHTMLTagOn(std::ostream& fs) const {

	if (!fs) {
		return false;
	}

	fs << "<a href=" << "\"" << content << "\"" << " descr=" << "\"" << description << "\"";
	fs << "> " << destination << "</a>" << "\n";

	if (fs.good()) {
		return true;
	}
	else {
		return false;
	}
}

std::string LinkTag::toString() const {

	std::string convertedString
	("Link with description: " + description +
		", content: " + content + " and destination: " + destination + "\n");

	return convertedString;
}

void LinkTag::setDestination(const std::string& destination) {
	this->destination = destination;
}

/////////////////////
//LINK TAG CREATOR
/////////////////////

LinkTagCreator::LinkTagCreator():HTMLTagCreator(LINK) {
}

HTMLTag* LinkTagCreator::createHTMLTagFromConsole(std::istream& is) const {

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

	skipSpacesOn(is);

	std::string destination;
	std::getline(is, destination, '\n');
	
	return new LinkTag(content, description, destination);
}

HTMLTag* LinkTagCreator::createHTMLTagFromFile(std::istream& is) const {

	if (!is) {
		return nullptr;
	}

	skipSpacesOn(is);

	std::string content;
	std::getline(is, content, ' ');
	content = content.substr(6, content.size() - 7);

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(7, description.size() - 8);

	skipSpacesOn(is);

	std::string destination;
	std::getline(is, destination, '<');

	is.ignore(SKIPINGSYMBOLS, '\n');

	return new LinkTag(content, description, destination);
}

static  LinkTagCreator __;
