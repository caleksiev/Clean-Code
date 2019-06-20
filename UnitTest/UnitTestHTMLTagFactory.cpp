#include "CppUnitTest.h"
#include"../Project1/HTMLTagFactory.h"
#include"../Project1/VideoTag.h"
#include"../Project1/HeadingTag.h"
#include"../Project1/ImageTag.h"
#include"../Project1/LinkTag.h"
#include"../Project1/ParagraphTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void registerExistCreator() {

	HTMLTagCreator* creator = new VideoTagCreator();
	HTMLTagFactory::getFactory().registerHTMLTag(creator);

}

namespace UnitTest6 {
	TEST_CLASS(VideoTagTest)
	{
	public:

		TEST_METHOD(ExceptionThrownWhenAlreadyCreatorIsRegister) {

			auto func = [] {registerExistCreator(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(checkCreateHTMLTagFromConsoleCommandIsOK) {

			HTMLTag** tags = new HTMLTag * [10];

			std::fstream fs1("testAddConsole.txt", std::ios::in);

			for (size_t i = 0; i < 10; ++i) {
				tags[i] = HTMLTagFactory::getFactory().createHTMLTag(fs1);
			}
			fs1.close();

			std::fstream fs2("actualTestAddConsole.html", std::ios::out);
			for (size_t i = 0; i < 10; ++i) {
				tags[i]->sendVisializedHTMLTagOn(fs2);
			}
			fs2.close();

			fs2.open("actualTestAddConsole.html", std::ios::in);
			std::fstream fs3("expectedTestAddConsole.html", std::ios::in);

			std::string actualContent;
			std::string expectedContent;
			for (size_t i = 0; i < 10; ++i) {

				std::getline(fs2, actualContent, '\n');
				std::getline(fs3, expectedContent, '\n');

				Assert::AreEqual(actualContent, expectedContent);
			}
			fs2.close();
			fs3.close();

			for (int i = 0; i < 10; ++i)
				delete tags[i];
			delete[] tags;
		}

		TEST_METHOD(checkCreateHTMLTagFromFileCommandIsOK) {

			HTMLTag** tags = new HTMLTag * [10];

			std::fstream fs1("testAddFile.html", std::ios::in);

			for (size_t i = 0; i < 10; ++i) {
				tags[i] = HTMLTagFactory::getFactory().createHTMLTag(fs1);
			}
			fs1.close();

			std::fstream fs2("actualTestAddFile.html", std::ios::out);
			for (size_t i = 0; i < 10; ++i) {
				tags[i]->sendVisializedHTMLTagOn(fs2);
			}
			fs2.close();

			fs2.open("actualTestAddFile.html", std::ios::in);
			std::fstream fs3("expectedTestAddFile.html", std::ios::in);

			std::string actualContent;
			std::string expectedContent;
			for (size_t i = 0; i < 10; ++i) {

				std::getline(fs2, actualContent, '\n');
				std::getline(fs3, expectedContent, '\n');

				Assert::AreEqual(actualContent, expectedContent);
			}
			fs2.close();
			fs3.close();

			for (int i = 0; i < 10; ++i)
				delete tags[i];
			delete[] tags;
		}
	};
}
