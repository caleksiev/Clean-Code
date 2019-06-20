#ifndef COMMANDINT_HEADER_INCLUDED
#define COMMANDINT_HEADER_INCLUDED
#include"HTMLFile.h"

enum CommandResult {
	OK,
	EXIT,
	NEWFILELOADED
};

//Execute the command from the console

class CommandInterpreter {
	//some posible errors during operating the file

public:
	CommandInterpreter(const std::string& fileName);
public:
	CommandResult executeCommand(std::istream& is, std::ostream& os);
private:
	CommandResult addCommand(std::istream& is, std::ostream& os);
	CommandResult removeCommand(std::istream& is, std::ostream& os);
	CommandResult printCommand(std::ostream& os)const;
	CommandResult moveCommand(std::istream& is, std::ostream& os);
	CommandResult saveCommand(std::ostream& os);
	CommandResult loadCommand(std::ostream& os);
	CommandResult exitCommand(std::ostream& os);
	CommandResult unknownCommand(std::istream& is, std::ostream& os);
private:
	void skipSpacesOn(std::istream& is)const;
private:
	CommandInterpreter(const CommandInterpreter& other) = delete;
	CommandInterpreter operator=(const CommandInterpreter& other) = delete;
private:
	HTMLFile file;
	bool isLoadFile;
};
#endif
