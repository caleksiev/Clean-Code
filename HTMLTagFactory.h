#ifndef HTMLTAG_FACTORY_HEADER_INCLUDED
#define HTMLTAG_FACTORY_HEADER_INCLUDED

#include<vector>
#include"HTMLTag.h"
// The class factory for creating tags by datas into stream
class HTMLTagFactory
{
public:
	//It is singleton
	static HTMLTagFactory& getFactory();
public:
	void registerHTMLTag(const HTMLTagCreator* creator);
public:
	HTMLTag* createHTMLTag(std::istream& is);
private:
	const HTMLTagCreator* getCreator(const std::string& str, bool& isTagFromConsole, std::istream& stream)const;
	bool isMetaData(std::string& data)const;//check if some data of the stream is a meta and skip it
private:
	bool checkIsAlreadyRegister(const HTMLTagCreator* creator);
private:
	HTMLTagFactory() = default;
	~HTMLTagFactory() {}
	HTMLTagFactory(const HTMLTagFactory&) = delete;
	HTMLTagFactory& operator=(const HTMLTagFactory&) = delete;
private:
	std::vector<const HTMLTagCreator*> creators;//the registered creators
};
#endif
