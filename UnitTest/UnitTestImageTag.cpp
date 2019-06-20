#include "CppUnitTest.h"
#include"../Project1/ImageTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void createImageTagWithEmptyDescription() {

	std::string description;
	std::string content("hello");
	ImageTag hTag = ImageTag(content, description);
}

void createImageTagWithEmptyContent() {

	std::string content;
	std::string description("hello");

	ImageTag hTag = ImageTag(content, description);
}

namespace UnitTestImageTag {
	TEST_CLASS(ImageTagTest)
	{
	public:
	
		TEST_METHOD(ExceptionThrownWhenImageTagDescriptionIsEmpty) {

			auto func = [] {createImageTagWithEmptyDescription(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenImageTagContentIsEmpty) {

			auto func = [] {createImageTagWithEmptyContent(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(CheckDescriptionOfImageTagIsAsExpected) {

			ImageTag image(std::string("party.jpg"), std::string("yolo"));

			std::string expectedDescription = "yolo";

			Assert::AreEqual(image.getDescription(), expectedDescription);
		}

		TEST_METHOD(CheckStringConvertOfImageTagIsAsExpected) {

			ImageTag image(std::string("party.jpg"), std::string("yolo"));

			std::string expectedString = "Image with description: yolo and content: party.jpg\n";
			std::string actualString = image.toString();

			Assert::AreEqual(actualString, expectedString);
		}
		
		TEST_METHOD(CheckVizualizationOfTagIsAsExpected) {

			ImageTag image(std::string("party.jpg"), std::string("yolo"));

			std::fstream f("t.txt", std::ios::out);

			image.sendVisializedHTMLTagOn(f);
			f.close();
			
			f.open("t.txt", std::ios::in);

			std::string actualContent;
			std::getline(f, actualContent, '\n');

			f.close();

			std::string expectedContent = "<img src=\"party.jpg\" descr=\"yolo\">";

			Assert::AreEqual(actualContent, expectedContent);

		}
		
		TEST_METHOD(CheckVizualizationOfTagWithBrokenStream) {

			ImageTag image(std::string("party.jpg"), std::string("yolo"));

			std::fstream f("///////////////");

			bool result = image.sendVisializedHTMLTagOn(f);

			Assert::IsFalse(result, L"The stream must be broken!");
		}
		
		TEST_METHOD(CheckCpyCtorWorkProperly) {

			ImageTag image =ImageTag(std::string("Some text..."), std::string("Some des..."));

			ImageTag copyImage = image;

			std::string actualString = copyImage.toString();
			std::string expectedString = "Image with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckOperatorEqualWorkProperly) {

			ImageTag fisrtsImage =
				ImageTag(std::string("Some text..."), std::string("Some des..."));
			ImageTag secondImage =
				ImageTag(std::string("Some text1..."), std::string("Some des2..."));

			secondImage = fisrtsImage;

			std::string actualString = secondImage.toString();
			std::string expectedString = "Image with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}
		
	};
}
