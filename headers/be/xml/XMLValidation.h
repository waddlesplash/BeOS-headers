/*******************************************************************************
/
/	File:			XMLValidation.h
/
/   Description:    Parse the XML, and while you're doing that, check for
/					validity.
/
/	Copyright 2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/
#ifndef _XMLVALIDATION_H
#define _XMLVALIDATION_H

#include <XMLDefs.h>
#include <XMLParser.h>
#include <XMLDTD.h>

namespace BXmlKit {


class BXMLValidatingContext : public BXMLDocumentParseContext
{
public:
	BXMLValidatingContext(BDocument * document,
							BXMLObjectFactory * factory = NULL,
							BEntityStore * entityStore = NULL);
	~BXMLValidatingContext();
	
	
private:
	BDocumentType	* _dt;
	BList 			_elementTrackerStack;
	
	
	struct _ElementChildrenTracker_
	{
		_ElementChildrenTracker_(BElementDecl * elementDecl);
		BElementDecl * decl;
		const void * data;
		bool dataFromAboveInStack;
		uint16 state;
	};

	status_t		check_attr_type(BAttribute * attr, BAttributeDecl * attrDecl);
	status_t		check_next_element(const char * element);
	void			push_element_stack(BElementDecl * decl);
	status_t		pop_element_stack();
	_ElementChildrenTracker_ * element_stack_top();
	status_t		is_text_value_allowed(BString & value, bool & allow);
	
public:
	// Implementations of BXMLDocumentCreationContext functions
	//virtual status_t	OnBeginDocumentNode();
	//virtual status_t	OnEndDocumentNode();
	virtual status_t	OnStartTagNode(BElement * element);
	virtual status_t	OnEndTagNode(BElement * element);
	virtual status_t	OnTextNode(BText * text);
	virtual status_t	OnCDataNode(BCData * cData);
	//virtual status_t	OnCommentNode(BComment * comment);
	virtual status_t	OnBeginDocumentTypeNode(BDocumentType * dt);
	//virtual status_t	OnExternalSubsetNode(BDocumentTypeDefinition * dtd);
	//virtual status_t	OnBeginInternalSubsetNode(BDocumentTypeDefinition * dtd);
	//virtual status_t	OnEndInternalSubsetNode();
	virtual status_t	OnEndDocumentTypeNode();
	//virtual status_t	OnProcessingInstructionNode(BProcessingInstruction * pi);
	//virtual	status_t	OnElementDeclNode(BElementDecl * decl);
	//virtual status_t	OnAttributeDeclNode(BAttributeDecl * decl);
	//virtual status_t	OnEntityDeclNode(BEntityDecl * decl);
	//virtual status_t	OnNotationDeclNode(BNotationDecl * decl);	XXX Not implemented
	
	//virtual BDocumentType *	GetDocumentType();
	
	// Implementations of BXMLParseContext functions
	//virtual status_t	OnGeneralParsedEntityRef(BString & name);
	//virtual status_t	OnGeneralParsedEntityRef(BString & name, BString & replacement);
	//virtual status_t	OnParameterEntityRef(BString & name);
	//virtual status_t	OnParameterEntityRef(BString & name, BString & replacement);
	
};


}; // namespace BXmlKit

#endif // _XMLVALIDATION_H
