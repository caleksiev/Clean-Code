#include "HTMLFile.h"

HTMLFile::HTMLFile(const std::string& fileName) {

	FileResult result = checkFileStatus(fileName);

	if (result == FILE_MUST_BE_HTML) {
		throw std::invalid_argument("The file type must be a html!\n");
	}
	else if (result == WRONG_FILE_PATH) {
		throw std::invalid_argument("The file path is wrong!\n");
	}
	else {
		if (readFromFile(fileName))
			setFileName(fileName);
		else
			throw "Problem while operating with the file!\n";

	}
}


HTMLFile::~HTMLFile() {
	clean();
}

bool HTMLFile::addHTMLTag(std::istream& is) {
	//the beauty of the abstract factory :)
	HTMLTag* tag = HTMLTagFactory::getFactory().createHTMLTag(is);

	if (tag) {
		tags.push_back(tag);
		return true;
	}
	else {
		return false;
	}
}

void HTMLFile::removeHTMLTag(const std::string& descripton) {

	size_t size = tags.size();
	size_t index = getHTMLTagIndex(descripton);

	if (index >= size) {
		throw std::out_of_range("INVALID INDEX FOR REMOVING TAG!\n");
	}

	if (!size) {
		throw std::out_of_range("THERE IS NO MORE TAGS LEFT FOR REMOVING !\n"); \
	}

	if (index == size - 1) {//just remove the last element
		tags.pop_back();
	}
	else {//shift right all element from the wanted position
		for (size_t i = index; i < size - 1; ++i) {
			std::swap(tags[i], tags[i + 1]);
		}
		tags.pop_back();
	}
}

void HTMLFile::moveHTMLTagTo(size_t index, const std::string& descripton) {

	size_t size = tags.size();
	size_t where = getHTMLTagIndex(descripton);

	if (index >= size || where >= size) {
		throw std::out_of_range("INVALID INDEX FOR MOVING TAG!\n");
	}

	HTMLTag* element = tags[index];//save the element

	if (index == where) {
		return;
	}

	size_t iteration = index;

	try {
		if (index > where) {
			for (; iteration > where; --iteration) {
				tags[iteration] = tags[iteration - 1];
			}
		}
		else {
			for (; iteration < where; ++iteration) {
				tags[iteration] = tags[iteration + 1];
			}
		}
	}
	catch (const std::bad_alloc& ()) {

		tags[iteration] = element; //in case of problem with the memory return the element
		throw;
	}

	tags[where] = element;
}

bool HTMLFile::saveHTMLFile() const {

	std::fstream f(fileName, std::ios::out);

	if (!f.is_open()) {
		return false;
	}

	f << "<!DOCTYPE html>\n" << "<html>\n" << "<head> </head>\n" << "<body>\n";

	size_t size = tags.size();
	for (size_t i = 0; i < size && f.good(); ++i) {
		if (!tags[i]->sendVisializedHTMLTagOn(f)) { // POLYMORPHISM :)))))
			return false;
		}
	}

	f << "</body>\n" << "</html>";

	f.close();

	if (f.good()) {
		return true;
	}
	else {
		return false;
	}
}

void HTMLFile::printHTMLTagInformationOn(std::ostream& fs) const {

	if (!fs) {
		return;
	}

	size_t size = tags.size();
	fs << "There are " << size << " tags:\n";

	for (size_t i = 0; i < size; ++i) {
		fs << tags[i]->toString() << "\n"; // POLYMORPHISM :)))))
	}
}

bool HTMLFile::readFromFile(const std::string& fileName)
{

	std::fstream f(fileName, std::ios::in);

	if (!f.is_open()) {
		return false;
	}

	while (f.good()) {
		addHTMLTag(f); // Abstraction 
	}

	f.close();

	if (f.eof()) {
		return true;
	}
	//else
	return false;
}

typename HTMLFile::FileResult HTMLFile::checkFileStatus(const std::string& fileName)
{
	size_t size = fileName.size();

	if (fileName[size - 1] != 'l' || fileName[size - 2] != 'm' ||
		fileName[size - 3] != 't' || fileName[size - 4] != 'h') {
		return FILE_MUST_BE_HTML;
	}

	std::fstream f(fileName, std::ios::in);

	if (!f.is_open()) {//the file doesn't exist
		f.close();

		f.open(fileName, std::ios::out);
		if (!f.is_open()) {//the file path is wrong
			return WRONG_FILE_PATH;
		}
		else {
			return NEW_FILE_CREATED;
		}
	}
	//else
	return FILE_EXIST;
}

void HTMLFile::setFileName(const std::string& fileName) {
	this->fileName = fileName;
}

size_t HTMLFile::getHTMLTagIndex(const std::string& desription) {

	size_t size = tags.size();
	for (size_t i = 0; i < size; ++i) {
		if (tags[i]->getDescription() == desription) {
			return i;
		}
	}
	throw std::out_of_range("THERE IS NO TAG WITH DESCRIPTON " + desription);
}

void HTMLFile::clean() {

	size_t size = tags.size();
	for (size_t i = 0; i < size; ++i) {
		delete tags[i];
	}
}