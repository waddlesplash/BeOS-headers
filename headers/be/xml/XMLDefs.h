/*******************************************************************************
/
/	File:			XMLDefs.h
/
/   Description:    Classes and constant, etc. definitions for the XML Kit.
/					Includes the definitions for the main data classes of the
/					XML Kit.
/
/	Copyright 2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/


#ifndef _XMLDEFS_H
#define _XMLDEFS_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <String.h>
#include <Errors.h>


// If this is defined to 1, a lot of the conveninece methods are disabled
// so it has a smaller memory footprint for BeIA
// Don't just go and turn this on.  It breaks binary compatibility
// because of the ton of virtual functions that it adds.
#define _SMALL_XML_FOOTPRINT_ 1

// XML Type Code
// =====================================================================
enum
{
	B_XML_DOCUMENT_CONTENT						= 0x00000001,
	B_XML_DOCUMENT_TYPE_CONTENT					= 0x00000002,
	B_XML_ELEMENT_CONTENT						= 0x00000004,
	B_XML_ATTRIBUTE_CONTENT						= 0x00000008,
	B_XML_TEXT_CONTENT							= 0x00000010,
	B_XML_CDATA_CONTENT							= 0x00000020,
	B_XML_PROCESSING_INSTRUCTION_CONTENT		= 0x00000040,
	B_XML_COMMENT_CONTENT						= 0x00000080,
	B_XML_ATTRIBUTE_DECL_OBJECT					= 0x00000100,
	B_XML_ELEMENT_DECL_OBJECT					= 0x00000200,
	B_XML_ENTITY_DECL_OBJECT					= 0x00000400,
	B_XML_DTD_OBJECT							= 0x00000800,
	
	B_XML_ANY_CONTENT							= 0xFFFFFFFF,

	B_XML_BEOS_CONTENT_TYPE_MASK	= 0x0000FFFF	// Anything that masks with this
													// is reserved for use by Be. Other
													// people can use the rest for their
													// own purposes
};


#define B_XML_DTD_DIRECTORY "xml_dtds"


// XML Kit Errors
// =====================================================================
// These should go into Errors.h

#define B_XML_ERROR_BASE			B_GENERAL_ERROR_BASE + 0xb000
enum {
	B_XML_ALREADY_ATTACHED			= B_XML_ERROR_BASE,
	B_XML_NOT_ATTACHED,
	B_XML_CANT_CONVERT_STRING,
	B_XML_ONE_ELEMENT_PER_DOCUMENT,
	B_XML_ONE_DOCTYPE_PER_DOCUMENT,
	B_XML_BAD_PARENT,
	B_XML_MATCH_NOT_FOUND,
	B_XML_INVALID_XPATH,
	B_XML_INVALID_XSLT_DOCUMENT,
	B_XML_BAD_ELEMENT_NESTING,
	
	B_XML_MAX_TOKEN_LENGTH_EXCEEDED,			// Names, etc. can only be 256 chars long
												// because you need to set some limit
	B_XML_BAD_NAME_CHARACTER,					// Names for elements, etc.
	B_XML_PARSE_ERROR,							// General Parse Error -- Something in the wrong place
	B_XML_ENTITY_VALUE_NO_QUOTES,				// Entity values / IDs must be surrounded by quotation marks
	B_XML_RECURSIVE_ENTITY,
	B_XML_NO_UNPARSED_PARAMETER_ENTITIES,
	B_XML_ENTITY_NOT_FOUND,
	B_XML_DECLARATION_NOT_IN_DTD,
	B_XML_NO_DTD,
	B_XML_ILLEGAL_UNPARSED_ENTITY_REF,
	B_XML_INVALID_ATTR_TYPE,
	B_XML_BAD_ATTR_BEHAVIOR,
	B_XML_AMBIGUOS_CHILDREN_PATTERN,
	
	B_XML_ALREADY_DECLARED,
	
	// Validation Errors
	B_XML_ELEMENT_NOT_DECLARED,
	B_XML_ATTRIBUTE_NOT_DECLARED,
	B_XML_ATTRIBUTE_BAD_FIXED_VALUE,
	B_XML_REQUIRED_ATTRIBUTE_MISSING,
	B_XML_ENTITY_REF_NOT_UNPARSED,
	B_XML_BAD_ENUM_VALUE,
	B_XML_ELEMENT_NOT_EMPTY,
	B_XML_CHILD_ELEMENT_NOT_ALLOWED,
	B_XML_CHILD_TEXT_NOT_ALLOWED,
	B_XML_CHILD_CDATA_NOT_ALLOWED,
	B_XML_CHILD_PATTERN_NOT_FINISHED,
	
	// These are only warnings.  The default OnParseError fails on them.
	// Maybe this behavior should be changed.
	B_XML_WARNINGS_BASE,
	
	B_XML_ENTITY_ALREADY_EXISTS,				// The first one is the one that's used.
	
	B_XML_ERRORS_END
};

enum xml_attr_behavior
{
	B_XML_ATTRIBUTE_REQUIRED,
	B_XML_ATTRIBUTE_IMPLIED,
	B_XML_ATTRIBUTE_FIXED,
	B_XML_ATTRIBUTE_OPTIONAL,
	B_XML_ATTRIBUTE_DEFAULT
};

enum
{
	B_ENUM_TYPE			= 'ENUM',
	B_NOTATION_TYPE		= 'NOTN',		// Not supported yet
	B_ID_TYPE			= 'IDYO',
	B_IDREF_TYPE		= 'IDRF',
	B_IDREFS_TYPE		= 'IRFS',
	B_ENTITY_TYPE		= 'ENTI',
	B_ENTITIES_TYPE		= 'ENTS',
	B_NMTOKEN_TYPE		= 'NTKN',
	B_NMTOKENS_TYPE		= 'NTKS'
};


// Parsing Flags
// =====================================================================
enum
{
	B_XML_COALESCE_WHITESPACE			= 0x00000001,
	B_XML_HANDLE_ATTRIBUTE_ENTITIES		= 0x00000002,
	B_XML_HANDLE_CONTENT_ENTITIES		= 0x00000004,
	B_XML_HANDLE_ALL_ENTITIES			= 0x00000006
};


namespace BXmlKit {

// Forward References
// =====================================================================
class BContent;
class BNamed;
class BElement;
class BDocument;
class BValued;
class BAttribute;
class BText;
class BCData;
class BComment;
class BNamedSet;
class BDocumentType;
class BProcessingInstruction;


// =====================================================================
// Some xml objects (specifically BAttribute) don't have much in common
// functionally, but they all need a common base class.
class BXMLObject
{
public:
							BXMLObject(uint32 type);
	virtual					~BXMLObject();
	
							// Type Code
	uint32					Type() const;
	
private:
	uint32					_type;
};


// XML Content
// =====================================================================
// Base class of the classes that make up the document structure.
class BContent : public BXMLObject
{
public:
	
							// All elements have parents except for the
							// root element, where this returns null
	BElement				* Parent();
	
							// Each node has a pointer to the document it's
							// in (if it's in a document).  
	BDocument				* Document();
							
							// The next sibling in document order.
							// Mask looks until the next one that matches mask
							// Element is a convience wrapper for NextSibMask(ELEMENT);
	BContent				* NextSibling();
	BContent				* NextSibling(uint32 typeMask);
	BContent				* PreviousSibling();
	BContent				* PreviousSibling(uint32 typeMask);
	
	BElement				* NextSiblingElement();
	BElement				* PreviousSiblingElement();
	
	virtual BContent		* Clone() const;
protected:
	
							// You get a copy that is not connected to the document
							// hierarchy
	explicit				BContent(const BContent & copy);
	
							// Never create a plain BContent
							BContent(uint32 type);
	
	virtual					~BContent();
	
private:
							// Always need a type
							BContent();
	
	bool					check_content_for_connections();
	status_t				set_parent(BElement * parent);
	status_t				set_next_sibling(BContent * sibling);
	status_t				set_prev_sibling(BContent * sibling);
	status_t				set_document(BDocument * document);
	
	BElement				* _parent;
	BContent				* _nextSibling;
	BContent				* _prevSibling;
	BDocument				* _document;
	
	
	friend BElement;		// BElement manages its list of elements
	friend BDocument;		// BDocument manages its list of elements
};



// XML Named
// =====================================================================
// Simple mechanism for giving elements and attributes a name
// There is a corresponding BNamedSet that allows O(log n) access
// to named things.
class BNamed
{
public:
	const char *	Name() const;
	
	virtual			~BNamed();

protected:
	explicit		BNamed(const BNamed & copy);
	
					BNamed(const char * name);
					BNamed(BString & name, bool adopt = false);
	
	virtual void	SetName(const char * name);
	
private:
	BString			_name;
};


// Set of things with names
// =====================================================================
// Provides a set of BXMLNamed objects.  Used to keep track of attributes
// and some of the DTD declarations.  If you go through in index order,
// you get list sorted by name.
class BNamedSet
{
public:
	virtual status_t		Add(BNamed * named);				// O(log n)
	virtual status_t		Remove(BNamed * named);				// O(log n)
	virtual BNamed			* Find(const char * name);			// O(log n)
	
	int32					CountItems() const;					// O(1)
	BNamed					* ItemAt(int32 index);				// O(1)
	
							BNamedSet();
	virtual					~BNamedSet();
	
	virtual void			MakeEmpty(bool deleteData);
	
private:
	void	insert(BNamed * named, int32 at);
	BNamed	** _data;
	int32	_size;
}; 


// XML Element
// =====================================================================
// BElement maps directly to the element construction in an XML document.
// Only BElement know about their children, and the only way to add an
// element to ta document is to add it to an element, even though it is
// actually stored as a linked list.
// All the add functions take ownership -- don't try to delete things you add
class BElement : public BContent, public BNamed
{
public:
	
	// --- Constructor and Destructor  ----------------------
							BElement(const char * name);
							BElement(BString & name, bool adopt = false);
							BElement(const BElement & copy);
	virtual					~BElement();
	
	virtual BContent		* Clone() const;
	BElement				& operator=(BElement & copy);
	
	// --- Getting Children ---------------------------------
	
							// Access to the first and last children for iteration
							// iteration over all of the children of any type.
							// With a mask, it will find the first that fits it
	BContent				* FirstChild();
	BContent				* FirstChild(uint32 typeMask);
	BContent				* LastChild();
	BContent				* LastChild(uint32 typeMask);
	
							// Random access to element children only
							// the thought is to store a separate list
							// of the elements only, so that you can access
							// these in quick ways
	int32					CountChildrenElements() const;
	BElement				* ChildElementAt(int32 index);
	
							// Find the index of the first element named
							// name after index after
	int32					FindElementNamed(const char * name, int32 atOrAfter = 0);
	
	
	// --- Adding Children ----------------------------------
	
							// Make it the first one
	virtual status_t		AddChildFirst(BContent * content);
	
							// Make it the last one
	virtual status_t		AddChildLast(BContent * content);
	
							// Put it bofore "before"
	virtual status_t		AddChildBefore(BContent * content, BContent * before);
	
							// Put it after "after"
	virtual status_t		AddChildAfter(BContent * content, BContent * after);
	
	// --- Removing Children --------------------------------
	
	virtual status_t		RemoveChild(BContent * content);
	
	
	
	// --- Add Attributes -----------------------------------
	
	// The only way to find attributes is through their element.  Because they are
	// attached through a BXMLNamedSet, not through the BXMLNode linked list mechanism.
	
	// replace says what to do if it's already there:
	//     false: return an error if it already exists
	//     true:  replace it and return B_OK
							
							// The other add attributes call this one
	virtual status_t		AddAttribute(BAttribute * attribute, bool replace = false);
	
	virtual status_t		AddAttribute(const char * name, const char * val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, const BString & val, bool replace = false);


#if !_SMALL_XML_FOOTPRINT_

	virtual status_t		AddAttribute(const char * name, BRect val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, BPoint val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, int8 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, int16 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, int32 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, int64 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, uint8 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, uint16 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, uint32 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, uint64 val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, bool val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, float val, bool replace = false);
	virtual status_t		AddAttribute(const char * name, double val, bool replace = false);
	
							// Will always use #xxxxxx format
	virtual status_t		AddAttributeRGBColor(const char * name, rgb_color val, bool replace = false);
	
							// Will use HTML 4 colors if possible, else will use #xxxxxx format
	virtual status_t		AddAttributeHTMLColor(const char * name, rgb_color val, bool replace = false);
	
							// If it's in the same document, will give an XPath to it
	virtual status_t		AddAttributeXPath(const char * name, BContent * which, bool replace = false);

#endif
	
	// --- Find Attributes ----------------------------------
	
	int32					CountAttributes() const;
	BAttribute				* AttributeAt(int32 index) const;
	
							
							// Is there an attribute that exactly matches attribute, but may or
							// may not actually be the same object.
	bool					FindAttribute(BAttribute * attribute) const;
	
	// Find by name
	status_t				FindAttribute(const char * name, BAttribute ** attribute);
	status_t				FindAttribute(const char * name, const char ** val) const;
	status_t				FindAttribute(const char * name, BString * val) const;
	

#if !_SMALL_XML_FOOTPRINT_

	status_t				FindAttribute(const char * name, BRect * val) const;
	status_t				FindAttribute(const char * name, BPoint * val) const;
	status_t				FindAttribute(const char * name, int8 * val) const;
	status_t				FindAttribute(const char * name, int16 * val) const;
	status_t				FindAttribute(const char * name, int32 * val) const;
	status_t				FindAttribute(const char * name, int64 * val) const;
	status_t				FindAttribute(const char * name, uint8 * val) const;
	status_t				FindAttribute(const char * name, uint16 * val) const;
	status_t				FindAttribute(const char * name, uint32 * val) const;
	status_t				FindAttribute(const char * name, uint64 * val) const;
	status_t				FindAttribute(const char * name, bool * val) const;
	status_t				FindAttribute(const char * name, float * val) const;
	status_t				FindAttribute(const char * name, double * val) const;
	status_t				FindAttribute(const char * name, rgb_color * val) const;
	
							// Will try to find a pointer to a BXMLNode at that XPath
	status_t				FindAttributeXPath(const char * name, BContent ** which);

#endif
	
	// These take a default argument, if it doesn't find the attribute, it gives
	// you the default and returns false.  If it does find it it gives it to you
	// and returns true.  Use these if you don't want to do error checking, and you
	// have a default value that you can use without a problem.
	//
	// Replaces the code:
	// int32 val;
	// if (element->FindAttribute("name", &val) != B_OK)
	//		val = 5;
	//
	// With:
	// element->FindAttribute("name", &val, 5);
	//


	bool					FindAttribute(const char * name, const char ** val, const char * def) const;
	bool					FindAttribute(const char * name, BString * val, const char * def) const;

#if !_SMALL_XML_FOOTPRINT_
	bool					FindAttribute(const char * name, BRect * val, BRect def) const;
	bool					FindAttribute(const char * name, BPoint * val, BPoint def) const;
	bool					FindAttribute(const char * name, int8 * val, int8 def) const;
	bool					FindAttribute(const char * name, int16 * val, int16 def) const;
	bool					FindAttribute(const char * name, int32 * val, int32 def) const;
	bool					FindAttribute(const char * name, int64 * val, int64 def) const;
	bool					FindAttribute(const char * name, uint8 * val, uint8 def) const;
	bool					FindAttribute(const char * name, uint16 * val, uint16 def) const;
	bool					FindAttribute(const char * name, uint32 * val, uint32 def) const;
	bool					FindAttribute(const char * name, uint64 * val, uint64 def) const;
	bool					FindAttribute(const char * name, bool * val, bool def) const;
	bool					FindAttribute(const char * name, float * val, float def) const;
	bool					FindAttribute(const char * name, double * val, double def) const;
	bool					FindAttribute(const char * name, rgb_color * val, rgb_color def) const;
	
							// Will try to find a pointer to a BXMLNode at that XPath
							// The default in this function isn't all that useful
	bool					FindAttributeXPath(const char * name, BContent ** which, BContent * def);
	
#endif	
	
	// --- Remove Attributes --------------------------------
	
	virtual status_t		RemoveAttribute(BAttribute * attribute);
	virtual status_t		RemoveAttribute(const char * name);
	
	
	// --- Some Interesting Functions -----------------------
	
							// If there is a DTD, set it back to the default provided by
							// the DTD.  If there isn't a DTD, empty it out.  Also deletes
							// objects.  No leakage.
	// XXX virtual status_t		ResetAll();
	// XXX virtual status_t		ResetAttributes();
	// XXX virtual status_t		ResetChildren();
	
							// Put this element into some normalized form.  TBD.
							// For example, coalesce adjacent text or CData nodes
	// XXX void					Normalize();
	
	
	// --- Value of the Element... --------------------------
	
	// If the data inside this element can be coalesced by removing comments and/or
	// processing instructions, and joining all text and CData, then these functions
	// can get the values of the result of that coalescing.  If not, return an error.
	// Could also possibly put some convience methods into here to make
	// it do some fun stuff with attributes elements.  
	// For example, to get a rect, look at the top, left, bottom, right attributes,
	// if they all exist and can be floating point numbers, then this function would
	// work.  More thought needed here
	// These are const functions.
	//
	// This makes the following constructs simple to access, where they would be a
	// pain; but it's a fairly common piece of XML.
	//		<Element>42</Element>	gives: "42"
	//		<Element>Whoah <!-- Hey Dude -->Momma!</Element>    gives: "Whoah Momma!"
	
	status_t				GetData(BString * data);
	
#if 0 && !_SMALL_XML_FOOTPRINT_

	status_t				GetData(BRect * data);
	status_t				GetData(BPoint * data);
	status_t				GetData(int8 * data);
	status_t				GetData(int16 * data);
	status_t				GetData(int32 * data);
	status_t				GetData(int64 * data);
	status_t				GetData(uint8 * data);
	status_t				GetData(uint16 * data);
	status_t				GetData(uint32 * data);
	status_t				GetData(uint64 * data);
	status_t				GetData(bool * data);
	status_t				GetData(float * data);
	status_t				GetData(double * data);
	status_t				GetData(rgb_color * data);
	
	status_t				GetDataXPath(BContent * pathTo);
	
	
	// Similar idea as before, except here we set it.  This just fails if there
	// are already any children except a single text or a CData present.  Create
	// a Text object if there is nothing.
	virtual status_t		SetData(const char * data);
	virtual status_t		SetData(BString * data);
	virtual status_t		SetData(BRect * data);
	virtual status_t		SetData(BPoint * data);
	virtual status_t		SetData(int8 * data);
	virtual status_t		SetData(int16 * data);
	virtual status_t		SetData(int32 * data);
	virtual status_t		SetData(int64 * data);
	virtual status_t		SetData(uint8 * data);
	virtual status_t		SetData(uint16 * data);
	virtual status_t		SetData(uint32 * data);
	virtual status_t		SetData(uint64 * data);
	virtual status_t		SetData(bool * data);
	virtual status_t		SetData(float * data);
	virtual status_t		SetData(double * data);
	virtual status_t		SetData(rgb_color * data);
	
	virtual status_t		SetDataXPath(BContent * pathTo);
	
#endif

private:
	
	void			insert_into_elements(BElement * element, int32 at);
	
	BContent			* _firstChild;
	BContent			* _lastChild;
	BElement			** _elementsArray;
	int32				_elementsCount;
	mutable BNamedSet	_attributes;
};



// XML Valued
// =====================================================================
// BValued does not attempt to coalesce anything like BElement does --
// they don't have children.
class BValued
{
public:
	
	// --- Getting Value ------------------------------------
	
	status_t				GetValue(const char ** value) const;
	status_t				GetValue(BString * value) const;

#if !_SMALL_XML_FOOTPRINT_

	status_t				GetValue(BRect * value) const;
	status_t				GetValue(BPoint * value) const;
	status_t				GetValue(int8 * value) const;
	status_t				GetValue(int16 * value) const;
	status_t				GetValue(int32 * value) const;
	status_t				GetValue(int64 * value) const;
	status_t				GetValue(uint8 * value) const;
	status_t				GetValue(uint16 * value) const;
	status_t				GetValue(uint32 * value) const;
	status_t				GetValue(uint64 * value) const;
	status_t				GetValue(bool * value) const;
	status_t				GetValue(float * value) const;
	status_t				GetValue(double * value) const;
	status_t				GetValue(rgb_color * value) const;
	
	virtual status_t		GetValueXPath(BContent ** pathTo);
	
#endif

							// This function gets what you would see if you
							// outputed to XML and read with StyledEdit.
	virtual void			GetValueRaw(BString & value) const;
	
	// --- Setting Value ------------------------------------
	
	virtual status_t		SetValue(const char * value);
	virtual status_t		SetValue(const char * value, int32 length);
	
							// Adopt takes the buffer from value, so there
							// is no copy.
	virtual status_t		SetValue(BString & value, bool adopt = false);
	
#if !_SMALL_XML_FOOTPRINT_

	virtual status_t		SetValue(BRect value);
	virtual status_t		SetValue(BPoint value);
	virtual status_t		SetValue(int8 value);
	virtual status_t		SetValue(int16 value);
	virtual status_t		SetValue(int32 value);
	virtual status_t		SetValue(int64 value);
	virtual status_t		SetValue(uint8 value);
	virtual status_t		SetValue(uint16 value);
	virtual status_t		SetValue(uint32 value);
	virtual status_t		SetValue(uint64 value);
	virtual status_t		SetValue(bool value);
	virtual status_t		SetValue(float value);
	virtual status_t		SetValue(double value);
	
	virtual status_t		SetValueRGBColor(rgb_color value);
	virtual status_t		SetValueHTMLColor(rgb_color value);
	
	virtual status_t		SetValueXPath(BContent * pathTo);
#endif

	// --- Useful Functions ---------------------------------
	
							// Start will become the index of the first char (-1 for end)
							// Len is the number of chars to replace/delete, etc. (-1 is all)
	virtual status_t		Append(const char * str);
	virtual status_t		Insert(const char * str, int32 start = -1);
	virtual status_t		Remove(int32 start = -1, int32 len = -1);
	virtual status_t		Replace(const char * str, int32 start = 0, int32 len = -1);
	
	
protected:
	// --- Validation ---------------------------------------
	
							// Hook function.  Easier than re-implementing
							// all of the virtual set functions
							// Check to see if the new value is okay
							// return fals if it's not
							// default impl returns true to approve it
							// e.g. used by attribute to validate types
	virtual status_t		ValidateValueChange(BString & newVal);
	
	
public:
	explicit				BValued(const BValued & copy);
							BValued(const char * value);
							BValued();
	virtual					~BValued();
protected:
	// Give access just for efficiency.
	// Do not change this value directly.
	BString					_value;
};


// XML Attribute
// =====================================================================
// Elements are stored as a set of attributes and an ordered set of children
// nodes.  This is the object that represents attributes.
// All the value methods come from the BXMLValued class
class BAttribute	: public BValued, public BNamed, public BXMLObject
{
public:
							BAttribute(const char * name);
							BAttribute(const char * name, const char * value);
							BAttribute(BString & name, bool adopt = false);
							BAttribute(const BAttribute & copy);	// deep copy
	virtual					~BAttribute();
	virtual BAttribute		* Clone() const;
	
	virtual void			GetValueRaw(BString & value) const;
	
private:
							BAttribute();
};


// XML Processing Instruction
// =====================================================================
class BProcessingInstruction 	: public BValued, public BNamed, public BContent
{
public:
							BProcessingInstruction(const char * target);
							BProcessingInstruction(const char * name, const char * value);
							BProcessingInstruction(BString & name, bool adopt = false);
							BProcessingInstruction(const BProcessingInstruction & copy);	// deep copy
	
	virtual					~BProcessingInstruction();
	
	virtual BProcessingInstruction	* Clone() const;
	
	virtual void			GetValueRaw(BString & value) const;
private:
							BProcessingInstruction();
};


// XML Text
// =====================================================================
// Text is character data that might get escaped when written to XML.
class BText : public BContent, public BValued
{
public:
							BText();
							BText(const BText & copy);
							BText(const char * value);
	virtual					~BText();
	virtual BContent		* Clone() const;
};


// XML CData
// =====================================================================
// CData is text that does not get escaped, except for one case. It
// gets surrounded by the strings "<![CDATA[" and "]]>".  So if the
// string "]]>" appears in the string will be escaped to "]]&gt;"
// as required by Section 2.4 of the XML spec.
// The only difference between BText and BCData is how it is displayed
// in XML
class BCData : public BContent, public BValued
{
public:
							BCData();
							BCData(const BCData & copy);
							BCData(const char * value);
	virtual					~BCData();
	virtual BContent		* Clone() const;
};


// XML Comment
// =====================================================================
class BComment : public BContent, public BValued
{
public:
							BComment();
							BComment(const BComment & copy);
							BComment(const char * value);
	virtual					~BComment();
	virtual BContent		* Clone() const;
	
							// Comments are escaped slightly differently
	virtual void			GetValueRaw(BString & value) const;
	
private:
							// some substrings are illegal in comments
	virtual status_t		ValidateValueChange(BString & newVal);
};


// XML Document
// =====================================================================
// This class represents the document as a whole. It looks like an
// element, but it's not.  The document element has its parent set to NULL
// If it's NULL, you can always access the document through the Document() function.
// It's also not derived from BContent
// The document does not derive from element, but it has a bunch of similar
// functions, but it is much more limiting, because what a document can
// contain directly is limited by the XML spec.
class BDocument : public BXMLObject
{
public:
	
	// --- Constructor and Destructor  ----------------------
							BDocument();
							BDocument(const BDocument & copy);
	virtual					~BDocument();
	
	
	// --- Getting Children ---------------------------------
	
							// Access to the first and last children for iteration
							// iteration over all of the children of any type.
							// With a mask, it will find the first that fits it
	BContent				* FirstChild();
	BContent				* FirstChild(uint32 typeMask);
	BContent				* LastChild();
	BContent				* LastChild(uint32 typeMask);
	

							// Access to some of the meaningful children
	BDocumentType			* DocumentType();
	BElement				* Element();
	
	
	// --- Adding Children ----------------------------------
	
							// Make it the first one
	virtual status_t		AddChildFirst(BContent * content);
	
							// Make it the last one
	virtual status_t		AddChildLast(BContent * content);
	
							// Put it bofore "before"
	virtual status_t		AddChildBefore(BContent * content, BContent * before);
	
							// Put it after "after"
	virtual status_t		AddChildAfter(BContent * content, BContent * after);
	
	// --- Removing Children --------------------------------
	
	virtual status_t		RemoveChild(BContent * content);
	

	// --- Some Interesting Functions -----------------------
	
							// If there is a DTD, set it back to the default provided by
							// the DTD.  If there isn't a DTD, empty it out.  Also deletes
							// objects.  No leakage.
	// XXX virtual status_t		ResetAll();
	// XXX virtual status_t		ResetAttributes();
	// XXX virtual status_t		ResetChildren();
	
							// Put this element into some normalized form.  TBD.
							// For example, coalesce adjacent text or CData nodes
	// XXX void					Normalize();
	
							// Sometimes you don't wan't DTD checking.  When you
							// turn it back on, any validation is done, if force
							// is false, it fails, if true, it fixes it.
	// XXX virtual status_t		EnableDTD(bool on, bool force = false);
	// XXX bool					IsDTDEnabled() const;

private:
	
	mutable BContent		* _firstChild;
	mutable BContent		* _lastChild;
	mutable BElement		* _element;
	mutable BDocumentType	* _documentType;
};







}; //namespace BXmlKit

#endif // _XMLDEFS_H



