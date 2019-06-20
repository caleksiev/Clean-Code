#ifndef FILE_HEADER_INCLUED
#define FILE_HEADER_INCLUED
#include"HTMLTag.h"
#include"HTMLTagFactory.h"
#include"vector"
#include<fstream>

//The class control the html page - set of tags
class HTMLFile {

	enum FileResult {
		WRONG_FILE_PATH,
		FILE_MUST_BE_HTML,
		NEW_FILE_CREATED,
		FILE_EXIST,
		FILE_NOT_OPEN,
		FILE_PROBLEM_READ,
		UKNOWN_FILE_DATA,
		NO_DESCR_IN_FILE,
		SUCCSEES_FILE_READ,
		END_OF_FILE,
		NO_PROBLEM_FILE,
		WHAT_IS_THIS,
	};

public:
	HTMLFile(const std::string& fileName);
	HTMLFile(const HTMLFile& other) = delete;
	HTMLFile& operator= (const HTMLFile& other) = delete;
	~HTMLFile();
public://names speak for themselves
	bool addHTMLTag(std::istream& is);
	void removeHTMLTag(const std::string & descripton); //-> std::out_of_range
	void moveHTMLTagTo(size_t index, const std::string& descripton); //-> std::out_of_range
	bool saveHTMLFile()const;
	void printHTMLTagInformationOn(std::ostream& fs)const;
private:
	bool readFromFile(const std::string& fileName);
private:
	FileResult checkFileStatus(const std::string& fileName);
	void setFileName(const std::string& fileName);
private:
	size_t getHTMLTagIndex(const std::string& desription);//return the index or åxception it the tag doesn't exist
private:
	void clean();
private:
	std::string fileName;
	std::vector <HTMLTag*> tags;//collection of pointers -> Polymorphism :))))))))))
};
#endif
