#include "HTMLTagFactory.h"

HTMLTagFactory& HTMLTagFactory::getFactory() {
	static HTMLTagFactory factory;
	return factory;
}

void HTMLTagFactory::registerHTMLTag(const HTMLTagCreator* creator) {

	if (checkIsAlreadyRegister(creator)) {
		throw std::invalid_argument("The creator is already registered!\n");
	}
	creators.push_back(creator);
}

HTMLTag* HTMLTagFactory::createHTMLTag(std::istream& is) {
	//read for the type of the tag
	std::string type;
	is >> type;

	if (isMetaData(type)) {//do nothing
		return nullptr;
	}

	bool isTagFromConsole;
	//try to find a factory to guess the type and to check from which stream the tag will be created
	const HTMLTagCreator* creator = getCreator(type,isTagFromConsole, is);

	if (creator && isTagFromConsole) {
		return creator->createHTMLTagFromConsole(is);
	}
	else if (creator && !isTagFromConsole) {
		return creator->createHTMLTagFromFile(is);
	}
	else {
		is.ignore(SKIPINGSYMBOLS, '\n');
		return nullptr;
	}
}

const HTMLTagCreator* HTMLTagFactory::getCreator(const std::string& str,bool& isTagFromConsole,std::istream& stream)const {

	size_t size = creators.size();
	for (size_t i = 0; i < size; ++i) {
		//check if the tag match with console command string
		if (creators[i]->getTypeString() == str) {
			isTagFromConsole = true;
			return creators[i];
		}
		//check if the tag match with file html string
		if (creators[i]->getTypeHTMLSign() == str) {
			isTagFromConsole = false;
			return creators[i];
		}
		//special tag case to catch the size of heading tag
		if ((str == "<h1") || (str == "<h2") || (str == "<h3") ||
			(str == "<h4") || (str == "<h5") || (str == "<h6")) {
			stream.unget();//to take the digit
			isTagFromConsole = false;
			return creators[i];
		}
	}
	return nullptr;
}

bool HTMLTagFactory::isMetaData(std::string& data) const{

	if ((data == "<!DOCTYPE html") || (data == "<html") ||
		(data == "<head") || (data == "<body") || (data == "</head") ||
		(data == "</html") || (data == "</body") || data == "") {
		return true;
	}
	else {
		return false;
	}
}

bool HTMLTagFactory::checkIsAlreadyRegister(const HTMLTagCreator* creator){

	size_t size = creators.size();

	for (size_t i = 0; i < size; ++i) {
		if (creators[i] == creator) {
			return true;
		}
	}
	return false;
}

