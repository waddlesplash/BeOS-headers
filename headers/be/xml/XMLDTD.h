/*******************************************************************************
/
/	File:			XMLDTD.h
/
/   Description:    The classes associated with the document type definition
/					that help the XML kit validate XML documents.
/
/					This is private.  I don't want to release the DTD stuff
/					because I can't see how it won't change as it is updated
/					when new specs happen.
/
/	Copyright 2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/


#ifndef _XMLDTD_H
#define _XMLDTD_H

#ifndef _XMLDEFS_H
#include <XMLDefs.h>
#endif
#include <XMLParser.h>

#include <StringMap.h>
#include <TypeConstants.h>

namespace BXmlKit {


// Forward References
// =====================================================================
class BDocumentType;
class BDocumentTypeDefinition;
class BElementDecl;
class BAttributeDecl;
class BEntityDecl;
class BXMLEntityParser;

// XML Document Type
// =====================================================================
// This class holds everything about the DTD that is used for validating the document
class BDocumentType : public BContent
{
public:
	BDocumentTypeDefinition		* InternalSubset();
	BDocumentTypeDefinition		* ExternalSubset();
	
	status_t					SetInternalSubset(BDocumentTypeDefinition * dtd);
	status_t					SetExternalSubset(BDocumentTypeDefinition * dtd);
	
	BElementDecl	* FindElementDecl(const char * name);
	BEntityDecl		* FindEntityDecl(const char * name, bool parameter);
	
					BDocumentType();
	virtual			~BDocumentType();
	
private:
	BDocumentTypeDefinition		* _internalSubset;
	BDocumentTypeDefinition		* _externalSubset;
};


// XML Document Type Definition
// =====================================================================
// This holds the DTD for both internal, external, and namespace DTDs
// Note that namespace DTDs are really just DTDs that have been given
// two names: a systemID and a publicID.  System IDs tell how to access
// the dtd file (e.g. a URL), publicIDs are guaranteed to be unique and stable.
class BDocumentTypeDefinition : public BXMLObject, public BNamed
{
public:
	// Element Declarations
	status_t			AddElementDecl(BElementDecl * decl);
	status_t			RemoveElementDecl(BElementDecl * decl);
	BElementDecl		* FindElementDecl(const char * name);
	int32				CountElementDecls() const;
	BElementDecl		* ElementDeclAt(int32 index);
	
	status_t			AddAttributeDecl(BAttributeDecl * decl);
	
	// Entity Declarations
	status_t			AddEntityDecl(BEntityDecl * decl);
	status_t			RemoveEntityDecl(BEntityDecl * decl);
	BEntityDecl			* FindEntityDecl(const char * name, bool parameter);
	int32				CountEntityDecls() const;
	BEntityDecl			* EntityDeclAt(int32 index);
	
						BDocumentTypeDefinition(const char * name);
	virtual				~BDocumentTypeDefinition();
	
	// ExternalID / InternalID
	const char *		PublicID() const;
	const char *		SystemID() const;
	void				SetPublicID(const char * id);
	void				SetSystemID(const char * id);
	
private:				
	BNamedSet	_elements;
	BNamedSet	_paramEntities;
	BNamedSet	_generalEntities;
	BString		_publicID;
	BString		_systemID;
};


// XML Element Declaration
// =====================================================================
// The structure that declares what is allowed in an element -- including
// what its children may be, which elements it has, etc.
// There is some pattern matching allowed, and this class includes
// subclasses for the data structures for that.
class BElementDecl : public BXMLObject, public BNamed
{
public:
	
	// --- Constructor / Destructor / Etc. ------------------
								BElementDecl(const char * name);
	virtual						~BElementDecl();
	
	virtual status_t			SetTo(BString & contentSpec);
	
	
	enum element_children_allowed
	{
		EMPTY,
		ANY,
		MIXED,
		CHILDREN
	};
	
	element_children_allowed	Mode() const;
	void						SetMode(element_children_allowed mode);
	
	
	// --- MIXED Mode ---------------------------------------
	status_t					AllowElement(const char * name);
	status_t					AllowElement(const char * name, int32 length);
	status_t					DisallowElement(const char * name);
	bool						IsElementAllowed(const char * name);	// false on error
	int32						CountAllowedElements() const;
	const BString 				& AllowedElementAt(int32 index);
	
	
	// --- CHILDREN Mode ------------------------------------
	typedef enum
	{
		ONE,					// 
		ONE_OR_MORE,			// +
		ZERO_OR_MORE,			// *
		ONE_OR_ZERO				// ?
	}node_cardinality;
	
	class List;
	
	struct ListNode
	{
		typedef enum {LIST, STRING, NO_INIT} Type;
		Type type;
		List * list;
		node_cardinality cardinality;
		BString element;
		ListNode(Type atype, List * alist)
			:type(atype), list(alist)
			 {};
	};
	
	class List
	{
	public:
		typedef enum {SEQ, CHOICE} Type;
		Type type;
		void AddNode(ListNode * node);
		void AddNode(ListNode * node, int32 index);
		int32 CountItems() const;
		ListNode * NodeAt(int32 index);
		void RemoveNode(ListNode * node);
		void RemoveNode(int32 index);
		void MakeEmpty();
	private:
		BList _list;
	};
	
	ListNode			* GetPattern();
	static bool			AllChildrenOptional(const ListNode * node);
	
	// --- Attributes ---------------------------------------
	
	status_t				AddAttributeDecl(BAttributeDecl * decl);
	BAttributeDecl			* FindAttributeDecl(const char * name);
	int32					CountAttributeDecls() const;
	BAttributeDecl			* GetAttributeDecl(int32 index);
	status_t				RemoveAttributeDecl(BAttributeDecl * decl);
	
private:
	
	status_t	handle_mixed_content_spec(BString & contentSpec);
	status_t	handle_element_content_spec(BString & contentSpec);
	status_t	handle_element_pattern(const char *& p, List * into, node_cardinality & cardin);
	
	// General Info
	element_children_allowed	_mode;
	
	// For MIXED mode
	BStringSet					_mixed_AllowedChildren;
	
	// For CHILDREN mode
	ListNode					_children_pattern;
	
	// Attributes
	BNamedSet					_attributes;
};


// XML Attribute Declaration
// =====================================================================
class BAttributeDecl : public BXMLObject, public BNamed
{
public:
	// A Be type code
	void				SetType(uint32 type);
	uint32				GetType() const;
	
	xml_attr_behavior	GetBehavior() const;
	void				SetBehavior(xml_attr_behavior behavior);
	
	// If it's type is enumeration
	status_t			AddEnumValue(const char * val);
	status_t			RemoveEnumValue(const char * val);
	int32				CountEnumValues() const;
	const char			* GetEnumValue(int32 index) const;
	bool				IsEnumValue(const char * val) const;
	
						// A string in the form "a|b|c"
	status_t			SetEnumValues(BString & str);
	
	// If it's behavior is "default" or "fixed"
	void				SetDefault(const char * value);
	BString				GetDefault() const;
	
	// Constructor
						BAttributeDecl(const char * name);
						BAttributeDecl(const BAttributeDecl & copy);
	virtual				~BAttributeDecl();
	BAttributeDecl		& operator=(const BAttributeDecl & copy);
	
	BString				GetElement() const;
	void				SetElement(const char * element);
	
private:
	BString				_element;	// I would really like to not store this.
	uint32				_typeCode;	// Be type code
	BStringSet			_enumVals;
	BString				_defaultVal;
	xml_attr_behavior	_behavior;
};


// XML Entity Declaration
// =====================================================================
// Go try and figure out the XML spec.  I dare you.  Basically entities are
// replacement text, but there are a million and one ways of declaring them, 
// and finding out where they come from.  I want to make the XML kit do as
// much of that as possible.
typedef enum
{
	B_XML_PARSED_ENTITY,
	B_XML_UNPARSED_ENTITY	
}xml_entity_type;
typedef enum
{
	B_XML_PARAMETER_ENTITY,
	B_XML_GENERAL_ENTITY
}xml_entity_scope;
typedef enum
{
	B_XML_INTERNAL_ENTITY,
	B_XML_EXTERNAL_ENTITY
}xml_entity_storage;

class BEntityDecl : public BXMLObject, public BNamed
{
public:
						BEntityDecl(const char		* name);
	virtual				~BEntityDecl();
	
	using BNamed::SetName;
	
	void				SetType(xml_entity_type type);
	xml_entity_type		GetType() const;
	
	void				SetScope(xml_entity_scope scope);
	xml_entity_scope	GetScope() const;
	
	void				SetStorage(xml_entity_storage storage);
	xml_entity_storage	GetStorage() const;
	
	const BString		& GetReplacementText();
	BXMLObjectSet		* GetReplacementContent();
	
	status_t			SetValue(const BString & str, BXMLObjectFactory * factory,
								uint32 parseFlags, BDocumentType * dt,
								BEntityStore * entityStore);

										// Will take the string data
	status_t			SetValueAdopt(BString & str, BXMLObjectFactory * factory,
								uint32 parseFlags, BDocumentType * dt,
								BEntityStore * entityStore);

										// Will not parse anything.  Will adopt the string.
	status_t			SetValueText(BString & str, BXMLObjectFactory * factory);
	
	void				AddItem(BXMLObject * object);
	
private:
	xml_entity_type		_type;
	xml_entity_scope	_scope;
	xml_entity_storage	_storage;
	BString				_replacementText;
	BXMLObjectSet		_objects;
};


// XML Entity Store
// =====================================================================
// When given a publicID, BEntityStore will look in the 
class BEntityStore
{
public:
	// Constructor / Destructor
					BEntityStore(uint32 parseFlags);
	virtual			~BEntityStore();
	
	// Fetch will go get it if necessary
	status_t		FetchExternalDTD(const BString & publicID, const BString & systemID,
							BXMLObjectFactory * factory, BDocumentType * dt,
							uint32 parseFlags, BDocumentTypeDefinition * dtd);
	status_t		FetchEntity(const BString & publicID, const BString & systemID,
							BEntityDecl ** returnDecl, bool parameter,
							BXMLObjectFactory * factory, uint32 parseFlags,
							BDocumentType * dt);

private:
	status_t	go_get_document(const BString & publicID, const BString & systemID,
								BDataIO ** dataIO);
	status_t	try_public_id(const BString & publicID, BDataIO ** dataIO);
	status_t	try_system_id(const BString & systemID, BDataIO ** dataIO);
	
	uint32 _parseFlags;
};

}; //namespace BXmlKit

#endif // _XMLDTD_H
