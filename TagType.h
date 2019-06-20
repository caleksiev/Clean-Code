#ifndef TAGTYPE_HEADER_INCLUDED
#define TAGTYPE_HEADER_INCLUDED

//Manage the work enum TagType, which descripe the type of every html tag

enum TagType
{
	HEADING,
	IMAGE,
	LINK,
	VIDEO,
	PARAGRAPH
};

class ConvertTagType
{
public:
	static const char* convertToStringSign(const TagType type) {
		switch (type)
		{
		case HEADING:
			return "heading";
		case IMAGE:
			return "image";
		case LINK:
			return "link";
		case VIDEO:
			return "video";
		case PARAGRAPH:
			return "text";
		default:
			return nullptr;
		}
	}

	static const char* convertToHTMLSign(const TagType type) {
		switch (type)
		{
		case HEADING:
			return "<h";
		case IMAGE:
			return "<img";
		case LINK:
			return "<a";
		case VIDEO:
			return "<iframe";
		case PARAGRAPH:
			return "<p";
		default:
			return nullptr;
		}
	}
};
#endif