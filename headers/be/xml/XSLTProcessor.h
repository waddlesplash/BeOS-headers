
#ifndef _XSLT_PROCESSOR_H
#define _XSLT_PROCESSOR_H

#include <XMLParser.h>
#include <List.h>
#include <String.h>

namespace BXmlKit {

class BXsltParseTree;


class _XPath_Patterns_
{
public:
				_XPath_Patterns_();
	virtual		~_XPath_Patterns_();
	
	status_t	AddTemplate(BElement * element);
	BElement	* MatchPattern(BXMLObject * source, BXMLObject * root, BXMLObject * context);
	
private:
	BList	_names;
	BList	_data;
};


class BXsltParseTree
{
public:
	
	// Find a the best template for this content to match
	BElement * MatchSourceNode(BXMLObject * source, BXMLObject * root, BXMLObject * context);
	
private:
	_XPath_Patterns_	patterns;
	
	friend status_t MakeXsltTree(BElement * xslt, BXsltParseTree * tree);
	friend status_t ProcessXSLT(BXsltParseTree * xslt, BElement * source, BElement * out);
};

status_t MakeXsltTree(BElement * xslt, BXsltParseTree * tree);
status_t FindElementsByName(const char * name, BElement * element, ElementSet * set);
status_t TraceXPath(BXMLObject * root, BXMLObject * context,
						BString xPath, XMLObjectSet * results);


status_t BootstrapXSLTProcessing(BElement * out, BXsltParseTree * xslt, BXMLObject * source);

}; // namespace BXmlKit

#endif // _XSLT_PROCESSOR_H
