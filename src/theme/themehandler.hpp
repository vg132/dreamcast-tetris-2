#ifndef __98EA34F973F8DBD9C4FA59__THEMEHANDLER__HPP__
#define __98EA34F973F8DBD9C4FA59__THEMEHANDLER__HPP__

#include <kos.h>
#include "themeinfo.hpp"
#include "background.hpp"
#include "../xml/xmlparser.hpp"
#include "../../../dccommon/src/linkedlist.hpp"

class CThemeHandler : public CXMLParser
{
private:
	char m_Text[5000];
	bool m_InBackground;
	CBackground *m_CurrentBackground;
	CThemeInfo *m_CurrentInfo;

	char* Trim(char *str);

	void ReadDir(const char *dir, CLinkedList *list);
public:
  void StartElement(const char *name, const char **atts);
  void EndElement(const char *name);
  void EndData(const char *data, int len);

	CThemeInfo* LoadTheme(const char *name);
	CLinkedList* LoadThemes(const char *folder);
	CThemeHandler(void);
	~CThemeHandler(void);
};

#endif // __98EA34F973F8DBD9C4FA59__THEMEHANDLER__HPP__
