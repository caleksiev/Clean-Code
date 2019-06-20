#include "CppUnitTest.h"
#include"../Project1/VideoTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void createVideoTagWithEmptyDescription() {

	std::string description;
	std::string content("hello");
	VideoTag vTag = VideoTag(content, description);
}

void createVideoTagWithEmptyContent() {

	std::string content;
	std::string description("hello");

	VideoTag vTag = VideoTag(content, description);
}

namespace UnitTestVideo {
	TEST_CLASS(VideoTagTest)
	{
	public:

		TEST_METHOD(ExceptionThrownWhenVideoTagDescriptionIsEmpty) {

			auto func = [] {createVideoTagWithEmptyDescription(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ExceptionThrownWhenParagraphTagContentIsEmpty) {

			auto func = [] {createVideoTagWithEmptyContent(); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(CheckDescriptionOfVideoTagIsAsExpected) {

			VideoTag video(std::string("www.youtube.com"), std::string("break"));

			std::string expectedDescription = "break";

			Assert::AreEqual(video.getDescription(), expectedDescription);
		}

		TEST_METHOD(CheckStringConvertOfVideoTagIsAsExpected) {

			VideoTag video(std::string("www.youtube.com"), std::string("break"));

			std::string expectedString = "Video with description: break and content: www.youtube.com\n";
			std::string actualString = video.toString();

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckVizualizationOfTagIsAsExpected) {

			VideoTag video(std::string("www.youtube.com"), std::string("break"));

			std::fstream f("t.txt", std::ios::out);

			video.sendVisializedHTMLTagOn(f);
			f.close();

			f.open("t.txt", std::ios::in);

			std::string actualContent;
			std::getline(f, actualContent, '\n');

			f.close();
		
			std::string expectedContent = "<iframe src=\"www.youtube.com\" descr=\"break\"></iframe>";

			Assert::AreEqual(actualContent, expectedContent);

		}

		TEST_METHOD(CheckVizualizationOfTagWithBrokenStream) {

			VideoTag video(std::string("www.youtube.com"), std::string("break"));

			std::fstream f("///////////////");

			bool result = video.sendVisializedHTMLTagOn(f);

			Assert::IsFalse(result, L"The stream must be broken!");
		}

		TEST_METHOD(CheckCpyCtorWorkProperly) {

			VideoTag video = VideoTag(std::string("Some text..."), std::string("Some des..."));

			VideoTag copyVideo = video;

			std::string actualString = copyVideo.toString();
			std::string expectedString = "Video with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}

		TEST_METHOD(CheckOperatorEqualWorkProperly) {

			VideoTag firstVideo =
				VideoTag(std::string("Some text..."), std::string("Some des..."));
			VideoTag secondVideo =
				VideoTag(std::string("Some text1..."), std::string("Some des2..."));

			secondVideo = firstVideo;

			std::string actualString = secondVideo.toString();
			std::string expectedString = "Video with description: Some des... and content: Some text...\n";

			Assert::AreEqual(actualString, expectedString);
		}

	};
}
