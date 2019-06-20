#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(const std::string& fileName):file(fileName), isLoadFile(true) {
}

CommandResult CommandInterpreter::executeCommand(std::istream& is, std::ostream& os) {

	os << "Enter a command:";
	std::string command;
	is >> command;

	if (command == "add") {
		return addCommand(is, os);
	}
	else if (command == "remove") {
		return removeCommand(is, os);
	}
	else if (command == "print") {
		return printCommand(os);
	}
	else if (command == "moveTo") {
		return moveCommand(is, os);
	}
	else if (command == "load") {
		return loadCommand(os);
	}
	else if (command == "save") {
		return saveCommand(os);
	}
	else if (command == "exit") {
		return exitCommand(os);
	}
	else {
		return unknownCommand(is, os);
	}
}

CommandResult CommandInterpreter::addCommand(std::istream& is, std::ostream& os) {

	if (file.addHTMLTag(is)) {
		os << "The tag was added!\n";
	}
	else {
		os << "The tag isnt' added! The command is wrong!\n";
	}
	return OK;
}

CommandResult CommandInterpreter::removeCommand(std::istream& is, std::ostream& os) {

	skipSpacesOn(is);

	std::string description;
	std::getline(is, description, '\n');

	file.removeHTMLTag(description);

	os << "The tag was removed!\n";


	return OK;
}

CommandResult CommandInterpreter::printCommand(std::ostream& os) const {

	file.printHTMLTagInformationOn(os);
	return OK;
}

CommandResult CommandInterpreter::moveCommand(std::istream& is, std::ostream& os) {
	skipSpacesOn(is);

	size_t position;
	std::string description;
	is >> position;

	skipSpacesOn(is);

	std::getline(is, description, '\n');

	file.moveHTMLTagTo(position, description);

	os << "The tag was moved!\n";

	return OK;
}

CommandResult CommandInterpreter::saveCommand(std::ostream& os) {

	isLoadFile = false;

	if (file.saveHTMLFile()) {
		os << "The new file was saved\n";
	}
	else {
		os << "Problem with saving the file \n";
	}
	return OK;
}

CommandResult CommandInterpreter::loadCommand(std::ostream& os) {

	if (isLoadFile) {
		os << "First save the current file before load another!\n";
		return OK;
	}
	else {
		isLoadFile = true;
		return NEWFILELOADED;
	}
}

CommandResult CommandInterpreter::exitCommand(std::ostream& os) {

	file.saveHTMLFile();

	os << "Exiting.....Byå :(...\n";
	
	return EXIT;
}

CommandResult CommandInterpreter::unknownCommand(std::istream& is, std::ostream& os) {

	os << "No such command!\n";

	is.ignore(SKIPINGSYMBOLS, '\n');

	return OK;
}

void CommandInterpreter::skipSpacesOn(std::istream& is) const
{

	char s = is.get();
	while (s == ' ')
		s = is.get();
	is.unget();
}
