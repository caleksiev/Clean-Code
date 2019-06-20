#include "CppUnitTest.h"
#include"..//Project1/HTMLFile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void openNotHTMLFile()
{
	HTMLFile file("f.txt");
}

void openWrongFile() {
	HTMLFile file("////////////.html");
}

void removeNotExistHTMLTag() {
	HTMLFile file("actualHtmlFileContentAfterRemove.html");

	file.removeHTMLTag("NOT EXIST");
}

void moveInvalidIndexHTMLTag() {
	HTMLFile file("htmlFileMove.html");

	file.moveHTMLTagTo(200, "help");
}

namespace UnitTest6 {
	TEST_CLASS(VideoTagTest){
	public:

		TEST_METHOD(ExceptionThrownWhenNotHTMLFileIsOpen) {
		
			auto func = [ ] {openNotHTMLFile(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenWrongHTMLFileIsOpen) {

			auto func = [] {openNotHTMLFile(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(CheckReadFromHTMLFileIsOK) {

			HTMLFile file("actualHtmlFileContent.html");

			file.saveHTMLFile();

			std::fstream ef("expectedHTMLFileContent.html", std::ios::in);
			std::fstream af("actualHtmlFileContent.html", std::ios::in);

			std::string actualString;
			std::string expectedString;

			while (ef.good() && af.good()) {

				std::getline(ef, expectedString, '\n');
				std::getline(af, actualString, '\n');

				Assert::AreEqual(expectedString, actualString);
			}

			ef.close();
			af.close();
		}
		TEST_METHOD(CheckNotExistRemoveHTMLTagFromFileIsOK) {

			auto func = [] {removeNotExistHTMLTag(); };
			Assert::ExpectException < std::out_of_range>(func);
		}

		TEST_METHOD(CheckRemoveHTMLTagFromFileIsOK) {

			HTMLFile file("actualHtmlFileContentAfterRemove.html");

			file.removeHTMLTag("main heading");
			file.removeHTMLTag("help");

			file.saveHTMLFile();

			std::fstream ef("expectedHTMLFileContentAfterRemove.html", std::ios::in);
			std::fstream af("actualHtmlFileContentAfterRemove.html", std::ios::in);

			std::string actualString;
			std::string expectedString;

			while (ef.good() && af.good()) {

				std::getline(ef, expectedString, '\n');
				std::getline(af, actualString, '\n');

				Assert::AreEqual(expectedString, actualString);
			}

			ef.close();
			af.close();
		}

		TEST_METHOD(ExceptionThrownWhenImvaliIndexForMoveIsEnter) {

			auto func = [] {moveInvalidIndexHTMLTag(); };
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(CheckMoveHTMLTagInotFileIsOK) {

			HTMLFile file("htmlFileMove.html");

			file.moveHTMLTagTo(8, "yolo");

			file.saveHTMLFile();

			std::fstream ef("htmlFileMove.html", std::ios::in);
			std::fstream af("htmlFileExpectedMove.html", std::ios::in);

			std::string actualString;
			std::string expectedString;

			while (ef.good() && af.good()) {

				std::getline(ef, expectedString, '\n');
				std::getline(af, actualString, '\n');

				Assert::AreEqual(expectedString, actualString);
			}

			ef.close();
			af.close();
		}

	};
}