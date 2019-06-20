#include "HTMLTag.h"
#include "HTMLTagFactory.h"

HTMLTag::HTMLTag(const std::string& content, const std::string& description) {

	if (content.empty() || description.empty()) {
		throw std::invalid_argument("THE STRING ARE EMPTY!\n");
	}
	setContent(content);
	setDescription(description);
}


std::string HTMLTag::getDescription() const {
	return description;
}

void HTMLTag::setContent(const std::string& content) {
	this->content = content;
}

void HTMLTag::setDescription(const std::string& description) {
	this->description = description;
}

/////////////////////////////////////////
//About the tag's factory
////////////////////////////////////////

// The work of the ctor is to save the type of the tag
// and to register itself in the factory

HTMLTagCreator::HTMLTagCreator(const TagType& type):type(type) {
	HTMLTagFactory::getFactory().registerHTMLTag(this);
}

const char* HTMLTagCreator::getTypeString() const {

	const char* convertedEnum = ConvertTagType::convertToStringSign(type);
	return convertedEnum;
}

const char* HTMLTagCreator::getTypeHTMLSign() const {

	const char* convertedEnum = ConvertTagType::convertToHTMLSign(type);
	return convertedEnum;
}

void HTMLTagCreator::skipSpacesOn(std::istream& is) const {

	char s = is.get();
	while (s == ' ')
		s = is.get();
	is.unget();
}


