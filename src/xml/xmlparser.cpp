#include "xmlparser.hpp"

CXMLParser::CXMLParser()
{
	/*
	parser = XML_ParserCreate(NULL);
	XML_SetElementHandler(parser, CXMLParser::__StartElement, CXMLParser::__EndElement);
	XML_SetCharacterDataHandler(parser, CXMLParser::__EndData);
	*/
}

CXMLParser::~CXMLParser()
{
//	XML_ParserFree(parser);
}

void CXMLParser::Init()
{
	parser = XML_ParserCreate(NULL);
	XML_SetElementHandler(parser, CXMLParser::__StartElement, CXMLParser::__EndElement);
	XML_SetCharacterDataHandler(parser, CXMLParser::__EndData);
}

void CXMLParser::Reset()
{
	XML_ParserFree(parser);
}

bool CXMLParser::Execute(char *buffer, int size)
{
	XML_SetUserData(parser, this);
  if(XML_Parse(parser, buffer, size, 1) == XML_STATUS_ERROR)
		return(false);
	return(true);
}

// userData is our c++ parser object -- just send it a message
void CXMLParser::__StartElement(void *userData, const char *name, const char **atts)
{
	CXMLParser *generator=(CXMLParser*)userData;
	generator->StartElement(name, atts);
}

void CXMLParser::__EndElement(void *userData, const char *name)
{
	CXMLParser *generator=(CXMLParser*)userData;
	generator->EndElement(name);
}

// XML will pass whitespace, and as most editors like to add it for
// formatting purposes, we need to strip off or we'll be very surprised
// by the data we see (!)

void CXMLParser::__EndData(void *userData, const char *s, int len)
{
	CXMLParser *generator=(CXMLParser*)userData;
	generator->EndData(s,len);
}
