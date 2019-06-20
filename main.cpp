#include"CommandInterpreter.h"
#include"HeadingTag.h"
int main() {

	std::cout << "The allowed commads are:\n"
		<< "1.1:<add><heading><size(1-6)><<descr>><content>\n"
		<< "1.2:<add><link><<descr>><content><linkDesciption>\n"
		<< "1.3:<add><image><<descr>><content>\n"
		<< "1.4:<add><video><<descr>><content>\n"
		<< "1.5:<add><text><<descr>><content>\n"
		<< "2:remove<<descr>>\n"
		<< "3.print\n"
		<< "4.moveTo<pos><<descr>>\n"
		<< "5.load<filePath>\n"
		<< "6.save\n"
		<< "7.exit\n";

	bool exit = false;
	while (true && !exit) {

		try {
			std::cout << "Enter a file path:";
			std::string filePath;
			std::cin >> filePath;

			std::cin.ignore(SKIPINGSYMBOLS, '\n');

			CommandInterpreter interpreter(filePath);
			std::cout << "The file was loaded!\n";
			while (true) {

				try {
					CommandResult result = interpreter.executeCommand(std::cin, std::cout);

					if (result == EXIT) {
						exit = true;
						break;
					}

					if (result == NEWFILELOADED) {
						break;
					}

					//std::cin.ignore(SKIPINGSYMBOLS, '\n');
				}
				catch (const std::bad_alloc&) {
					std::cout << "Not enough memory!\n";
					exit = true;
					break;
				}
				catch (std::exception& ex) {
					std::cout << ex.what();
				}
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what();
		}
	}
	return 0;
}