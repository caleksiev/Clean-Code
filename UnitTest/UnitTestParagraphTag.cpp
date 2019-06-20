#include "CppUnitTest.h"
#include"../Project1/ParagraphTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void createParagraphTagWithEmptyDescription() {

	std::string description;
	std::string content("hello");
	ParagraphTag pTag = ParagraphTag(content, description);
}

void createParagraphTagWithEmptyContent() {

	std::string content;
	std::string description("hello");

	ParagraphTag pTag = ParagraphTag(content, description);
}

namespace UnitTest4 {
	TEST_CLASS(ParagraphTagTest)
	{
	public:

		TEST_METHOD(ExceptionThrownWhenParagraphTagDescriptionIsEmpty) {

			auto func = [] {createParagraphTagWithEmptyDescription(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenParagraphTagContentIsEmpty) {

			auto func = [] {createParagraphTagWithEmptyContent(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(CheckDescriptionOfParagraphTagIsAsExpected) {

			ParagraphTag par(std::string("The live before FMI"), std::string("before"));

			std::string expectedDescription = "before";

			Assert::AreEqual(par.getDescription(), expectedDescription);
		}
		
		TEST_METHOD(CheckStringConvertOfParagraphTagIsAsExpected) {

			ParagraphTag par(std::string("The live before FMI"), std::string("before"));

			std::string expectedString = "Paragraph with description: before and content: The live before FMI\n";
			std::string actualString = par.toString();

			Assert::AreEqual(actualString, expectedString);
		}
		
		TEST_METHOD(CheckVizualizationOfTagIsAsExpected) {

			ParagraphTag par(std::string("The live before FMI"), std::string("before"));

			std::fstream f("t.txt", std::ios::out);

			par.sendVisializedHTMLTagOn(f);
			f.close();

			f.open("t.txt", std::ios::in);

			std::string actualContent;
			std::getline(f, actualContent, '\n');

			f.close();

			std::string expectedContent = "<p descr=\"before\">The live before FMI</p>";

			Assert::AreEqual(actualContent, expectedContent);

		}
		
		TEST_METHOD(CheckVizualizationOfTagWithBrokenStream) {

			ParagraphTag par(std::string("The live before FMI"), std::string("before"));

			std::fstream f("///////////////");

			bool result = par.sendVisializedHTMLTagOn(f);

			Assert::IsFalse(result, L"The stream must be broken!");
		}
		
		TEST_METHOD(CheckCpyCtorWorkProperly) {

			ParagraphTag par = ParagraphTag(std::string("Some text..."), std::string("Some des..."));

			ParagraphTag copyPar = par;

			std::string actualString = copyPar.toString();
			std::string expectedString = "Paragraph with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckOperatorEqualWorkProperly) {

			ParagraphTag firstPar =
				ParagraphTag(std::string("Some text..."), std::string("Some des..."));
			ParagraphTag secondPar =
				ParagraphTag(std::string("Some text1..."), std::string("Some des2..."));

			secondPar = firstPar;

			std::string actualString = secondPar.toString();
			std::string expectedString = "Paragraph with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}

	};
}
