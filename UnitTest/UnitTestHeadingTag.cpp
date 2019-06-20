#include "CppUnitTest.h"
#include"../Project1/HeadingTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void createHeadingTagWithEmptyDescription() {

	std::string description;
	std::string content("hello");
	size_t size = 5;
	HeadingTag hTag = HeadingTag(content, description, size);
}

void createHeadingTagWithEmptyContent() {

	std::string content;
	std::string description("hello");
	size_t size = 5;
	HeadingTag hTag = HeadingTag(content, description, size);
}

void createHeadingTagWithWrongSize() {
	std::string content("popo");
	std::string description("hello");
	size_t size = 8;
	HeadingTag hTag = HeadingTag(content, description, size);
}

namespace UnitTest1{
	TEST_CLASS(HeadingTagTest)
	{
	public:
		TEST_METHOD(ExceptionThrownWhenHeadingTagSizeIsWong){

			auto func = [] {createHeadingTagWithWrongSize(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenHeadingTagDescriptionIsEmpty) {

			auto func = [] {createHeadingTagWithEmptyDescription(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenHeadingTagContentIsEmpty) {

			auto func = [] {createHeadingTagWithEmptyContent(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(CheckDescriptionOfHeadingTagIsAsExpected) {

			HeadingTag h(std::string("FMI LIVE:"), std::string("<live>"), 5);
			std::string expectedDescription = "<live>";

			Assert::AreEqual(h.getDescription(), expectedDescription);
		}

		TEST_METHOD(CheckStringConvertOfHeadingTagIsAsExpected) {

			HeadingTag h(std::string("TODAYS LIVE"), std::string("<worse>"), 1);

			std::string expectedString = "Heading with description: <worse>, content: TODAYS LIVE and size: 1.\n";
			std::string actualString = h.toString();

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckVizualizationOfHeadingTagIsAsExpected) {

			HeadingTag h(std::string("TODAYS LIVE"), std::string("<worse>"), 1);
			std::fstream f("t.txt", std::ios::out);

			h.sendVisializedHTMLTagOn(f);
			f.close();

			f.open("t.txt", std::ios::in);
			
			std::string actualContent;
			std::getline(f, actualContent, '\n');

			f.close();

			std::string expectedContent = "<h1 descr=\"<worse>\">TODAYS LIVE</h1>";

			Assert::AreEqual(actualContent, expectedContent);

		}
		TEST_METHOD(CheckVizualizationOfTagWithBrokenStream) {

			HeadingTag h(std::string("TODAYS LIVE"), std::string("<worse>"), 1);

			std::fstream f("///////////////");

			bool result = h.sendVisializedHTMLTagOn(f);

			Assert::IsFalse(result, L"The stream must be broken!");
		}
		TEST_METHOD(CheckCpyCtorWorkProperly) {

			HeadingTag heading =
				HeadingTag(std::string("Some text..."), std::string("Some des..."), 4);

			HeadingTag copyHeading = heading;

			std::string actualString = copyHeading.toString();
			std::string expectedString = "Heading with description: Some des..., content: Some text... and size: 4.\n";

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckOperatorEqualWorkProperly) {

			HeadingTag fisrtsHeading =
				HeadingTag(std::string("Some text..."), std::string("Some des..."), 4);
			HeadingTag secondHeading =
				HeadingTag(std::string("Some text1..."), std::string("Some des2..."), 4);

			secondHeading = fisrtsHeading;

			std::string actualString = secondHeading.toString();
			std::string expectedString = "Heading with description: Some des..., content: Some text... and size: 4.\n";

			Assert::AreEqual(actualString, expectedString);
		}
		
	};
}
