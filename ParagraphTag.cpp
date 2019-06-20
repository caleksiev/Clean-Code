#include "ParagraphTag.h"

/////////////////
//PARAGRAPH TAG
/////////////////

ParagraphTag::ParagraphTag(const std::string& content, const std::string& description):HTMLTag(content, description) {
}

bool ParagraphTag::sendVisializedHTMLTagOn(std::ostream& fs) const {

	if (!fs) {
		return false;
	}

	fs << "<p" << " descr=" << "\"" << description << "\"" << ">" << content << "</p>" << "\n";

	if (fs.good()) {
		return true;
	}
	else {
		return false;
	}
}

std::string ParagraphTag::toString() const {

	std::string convertedString
	("Paragraph with description: " + description + " and content: " + content + "\n");

	return convertedString;
}

///////////////////////////
//PARAGRAPH TAG CREATOR
///////////////////////////

ParagraphTagCreator::ParagraphTagCreator():HTMLTagCreator(PARAGRAPH) {
}

HTMLTag* ParagraphTagCreator::createHTMLTagFromConsole(std::istream& is) const {

	if (!is) {
		return nullptr;
	}

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(1);

	skipSpacesOn(is);

	std::string content;
	std::getline(is, content, '\n');

	return new ParagraphTag(content, description);
}

HTMLTag* ParagraphTagCreator::createHTMLTagFromFile(std::istream& is) const {

	if (!is)
		return nullptr;

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '>');
	description = description.substr(7, description.size() - 8);

	skipSpacesOn(is);

	std::string content;
	std::getline(is, content, '<');

	is.ignore(SKIPINGSYMBOLS, '\n');

	return new ParagraphTag(content, description);
}

static ParagraphTagCreator __;