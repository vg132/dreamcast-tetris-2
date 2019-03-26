#ifndef __CAA7CB6E8B9667CCAAFAB5__CXMLPARSER__HPP__
#define __CAA7CB6E8B9667CCAAFAB5__CXMLPARSER__HPP__

#include <kos.h>
#include <expat/expat.h>

class CXMLParser
{
public:
	CXMLParser();
	virtual ~CXMLParser();

	void Init();
	void Reset();

	bool Execute(char *buffer, int size);
	int GetCurrentLineNumber() const;

	// static versions to pass to parser, note underscore convention;
	// these are used as callbacks to the "real" xml parser
	static void __StartElement(void *userData, const char *name, const char **atts);
	static void __EndElement(void *userData, const char *name);
	static void __EndData(void *userData, const char *s, int len);

	// member versions actually do the work; note "this" is the missing
	// userData; define these in a derived class to implement parser actions
	virtual void StartElement(const char *name, const char **atts) = 0;
	virtual void EndElement(const char *name) = 0;
	virtual void EndData(const char *data, int len) = 0;
	XML_Parser parser;
};

#endif // __CAA7CB6E8B9667CCAAFAB5__CXMLPARSER__HPP__
