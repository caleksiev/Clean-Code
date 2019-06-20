#include "CppUnitTest.h"
#include"../Project1/LinkTag.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void createLinkTagWithEmptyContent() {

	std::string content;
	std::string description("hello");
	std::string destination("there");
	LinkTag lTag = LinkTag(content, description, destination);
}

void createLinkTagWithEmptyDescritpion() {

	std::string content("hello");
	std::string description;
	std::string destination("there");
	LinkTag lTag = LinkTag(content, description, destination);
}

void createLinkTagWithEmptyDestination() {

	std::string content("hello");
	std::string description("there");
	std::string destination;
	LinkTag lTag = LinkTag(content, description, destination);
}



namespace UnitTest2 {
	TEST_CLASS(LinkTagTest)
	{
	public:

		TEST_METHOD(ExceptionThrownWhenLinkTagContentIsEmpty) {

			auto func = [] {createLinkTagWithEmptyContent(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenLinkTagDescriptionIsEmpty) {

			auto func = [] {createLinkTagWithEmptyDescritpion(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenLinkTagDestinationIsEmpty) {

			auto func = [] {createLinkTagWithEmptyDestination(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}


		TEST_METHOD(CheckDescriptionOfLinkTagIsAsExpected) {

			LinkTag link(std::string("www.facebook.com:"), std::string("help"),
				std::string("wanna help"));

			std::string expectedDescription = "help";

			Assert::AreEqual(link.getDescription(), expectedDescription);
		}

		TEST_METHOD(CheckStringConvertOfLinkTagIsAsExpected) {

			LinkTag link(std::string("www.facebook.com"), std::string("help"),
				std::string("wanna help"));
			std::string expectedString = "Link with description: help, content: www.facebook.com and destination: wanna help\n";
			std::string actualString = link.toString();

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckVizualizationOfLinkTagIsAsExpected) {

			LinkTag link(std::string("www.facebook.com"), std::string("help"),
				std::string("wanna help"));

			std::fstream f("t.txt", std::ios::out);

			link.sendVisializedHTMLTagOn(f);
			f.close();

			f.open("t.txt", std::ios::in);

			std::string actualContent;
			std::getline(f, actualContent, '\n');

			f.close();
			std::string expectedContent = "<a href=\"www.facebook.com\" descr=\"help\"> wanna help</a>";

			Assert::AreEqual(actualContent, expectedContent);

		}

		TEST_METHOD(CheckVizualizationOfTagWithBrokenStream) {

			LinkTag link(std::string("www.facebook.com"), std::string("help"),
				std::string("wanna help"));

			std::fstream f("///////////////");

			bool result = link.sendVisializedHTMLTagOn(f);

			Assert::IsFalse(result, L"The stream must be broken!");
		}

		TEST_METHOD(CheckCpyCtorWorkProperly) {

			LinkTag link =
				LinkTag(std::string("Some text..."),
					std::string("Some des..."), std::string("Some dest..."));

			LinkTag copyLink = link;

			std::string actualString = copyLink.toString();
			std::string expectedString = "Link with description: Some des..., content: Some text... and destination: Some dest...\n";

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckOperatorEqualWorkProperly) {

			LinkTag firstLink =
				LinkTag(std::string("Some text..."), std::string("Some des..."), std::string("Some dest..."));
			LinkTag secondLink =
				LinkTag(std::string("Some text1..."), std::string("Some des2..."), std::string("Some dest3..."));

			secondLink = firstLink;

			std::string actualString = secondLink.toString();
			std::string expectedString = "Link with description: Some des..., content: Some text... and destination: Some dest...\n";

			Assert::AreEqual(actualString, expectedString);
		}

	};

};

