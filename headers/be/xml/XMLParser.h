/*******************************************************************************
/
/	File:			XMLParser.h
/
/   Description:    Classes that parse XML.
/
/	Copyright 2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/


#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include <XMLDefs.h>

#include <String.h>
#include <StringMap.h>
#include <SmartArray.h>

// Forward References not in namespace BXmlKit
// =====================================================================
class BDataIO;

namespace BXmlKit {

// Forward References in namespace BXmlKit
// =====================================================================
class BXMLParseContext;
class BXMLDocumentParseContext;
class BXMLEntityParseContext;
class BXMLObjectFactory;
class BXMLDataSource;
class BXMLDataIOSource;
class BXMLBufferSource;
class BEntityStore;

class BEntityDecl;
class BElementDecl;
class BAttributeDecl;
class BDocumentTypeDefinition;

class BXMLStream;

// Generic Set
// =====================================================================
template <class T>
class _Pointer_Set_
{
public:
				_Pointer_Set_()
					:_list(5) { };
				~_Pointer_Set_() { };
	void		AddItem(T item) { _list.AddItem(item); };
	int32		CountItems() const { return _list.CountItems(); };
	T			ItemAt(int32 index){ return (T) _list.ItemAt(index); };
	void		DeleteItems()	{	int32 c = CountItems();
									for (int32 i=0; i<c; ++i) delete ItemAt(i);
									_list.MakeEmpty();
							 	}
	void		Transfer(_Pointer_Set_<T> & to)
								{	int32 c = CountItems();
									for (int32 i=0; i<c; ++i) to.AddItem(ItemAt(i));
									_list.MakeEmpty();
							 	}
 	void		RemoveItem(T item) { _list.RemoveItem(item); }
 	void		MakeEmpty()		{ _list.MakeEmpty(); }
 	bool		FindItem(T item){	int32 c = CountItems();
									for (int32 i=0; i<c; ++i)
										if (ItemAt(i) == item)
											return true;
									return false;
							 	}
private:
	BList _list;
};


// Some Sets of Pointers
// =====================================================================
typedef _Pointer_Set_<BElement *> ElementSet;
typedef _Pointer_Set_<BXMLObject *> XMLObjectSet;			// XXX should be fixed.
typedef _Pointer_Set_<BXMLObject *> BXMLObjectSet;
typedef _Pointer_Set_<BString *> _StringSet_;



// ParseXML -- Do the parsing
// =====================================================================
// The only flag that matters here is B_XML_COALESCE_WHITESPACE
status_t	ParseXML(BDocument * document, BDataIO * dataIO, uint32 flags = 0);
status_t	ParseXML(BDocument * document, const char * data, int32 length = -1, uint32 flags = 0);
status_t	ParseXML(BDocument * document, BXMLDataSource * data, uint32 flags = 0);
status_t	ParseXML(BXMLParseContext * context, BXMLDataSource * data, uint32 flags = 0);
status_t	ParseXML(BXMLParseContext * context, BXMLDataSource * data, uint32 flags = 0);



// BXMLParseContext -- Hook Functions for what the parser encounters
// =====================================================================
class BXMLParseContext
{
public:
				BXMLParseContext();
	virtual		~BXMLParseContext();
	
	// These fields are always set to the current line and column (or as
	// close of an approximation as possible).  They are probably most
	// useful for error messages.
	int32 line;
	int32 column;

						// Called at the beginning of the document parsing process.
	virtual status_t	OnDocumentBegin(uint32 flags);
	
						// Called at the end of the document parsing process.
						// If you get this call, then you know that parsing was successful.
	virtual status_t	OnDocumentEnd();
	
	// The following functions are fairly self explanitory.
	// Whenever there's a BString that isn't const, you are allowed to use the
	// BString::Adopt function to take the string buffer, and leave the original
	// string empty.  This is really just a performance optimization.
	
	virtual status_t	OnStartTag(				BString		& name,
												BStringMap	& attributes		);
									
	virtual status_t	OnEndTag(				BString		& name				);
	
	virtual status_t	OnTextData(				const char	* data,
												int32		size				);
	
	virtual status_t	OnCData(				const char	* data,
												int32		size				);
	
	virtual status_t	OnComment(				const char	* data,
												int32		size				);
	
	virtual status_t	OnDocumentTypeBegin(	BString		& name				);
	
	virtual status_t	OnExternalSubset(		BString		& publicID,
												BString		& systemID,
												uint32 		parseFlags			);
	
	virtual status_t	OnInternalSubsetBegin();
	
	virtual status_t	OnInternalSubsetEnd();
	
	virtual status_t	OnDocumentTypeEnd();
	
	virtual status_t	OnProcessingInstruction(BString		& target,
												BString		& data				);
	
	virtual	status_t	OnElementDecl(			BString		& name,
												BString		& data				);
	
	virtual status_t	OnAttributeDecl(		BString		& element,
												BString		& name,
												BString		& type,
												BString		& behavior,
												BString		& defaultVal		);
	
	virtual status_t	OnInternalParsedEntityDecl(	BString	& name,
													BString & internalData,
													bool	parameter,
													uint32	parseFlags			);
	
	virtual status_t	OnExternalParsedEntityDecl(	BString	& name,
													BString & publicID,
													BString & systemID,
													bool	 parameter,
													uint32	parseFlags			);
	
	virtual status_t	OnUnparsedEntityDecl(		BString	& name,
													BString & publicID,
													BString & systemID,
													BString & notation			);
	
	virtual status_t	OnNotationDecl(				BString	& name,
													BString	& value				);
	
						// This is a hook function to notify the subclass that we
						// encountered a PE in a text section.  Subclasses might
						// either look up replacement text and insert it, or look
						// parsed objects and insert them.
	virtual status_t	OnGeneralParsedEntityRef(	BString	& name				);
	
						// This is a hook function to find out the replacement text
						// for a general entity when it occurs in an attribute.  The
						// value is then substituted into the attribute as if it
						// had never been there.  If you want this behavior, you must
						// set the B_XML_HANDLE_ATTRIBUTE_ENTITIES flag.
	virtual status_t	OnGeneralParsedEntityRef(	BString	& name,
													BString & replacement		);
	
						// This is a hook function to notify the subclass when an 
						// entity occurred in the DTD, but in a place where it would
						// be better for the subclass to just insert its objects into
						// the stream than to send back the replacement text, and 
						// have this parser have to reparse it each time it occurs.
	virtual status_t	OnParameterEntityRef(		BString	& name				);
	
						// This is a hook function to find the replacement text for
						// a parameter entity.  It will then be parsed, and the normal
						// other functions will be called.
	virtual status_t	OnParameterEntityRef(		BString	& name,
													BString & replacement		);


};



// BXMLDocumentCreationContext
// =====================================================================
// This is a one-use-only object.  Never directly instantiate this class.
// It's a base class for DocumentParseContext and EntityParseContext. It's
// purpose is to create elements, and stuff, but just pass them on the
// their subclass when done.
// --> BXMLDocumentParseContext is the one that
//     adds the elements that are created here to their parents, etc.
// --> Note the naming differences.  This class does OnBeginXXX where
//     BXMLParseContext does OnXXXBegin.
class BXMLDocumentCreationContext : public BXMLParseContext
{
public:
				BXMLDocumentCreationContext(bool inDTD, // true only for parameter entities
											BXMLObjectFactory * factory = NULL,
											BEntityStore * entityStore = NULL);
	virtual		~BXMLDocumentCreationContext();
	
	// Hook functions
	virtual status_t	OnBeginDocumentNode() = 0;
	virtual status_t	OnEndDocumentNode() = 0;
	virtual status_t	OnStartTagNode(BElement * element) = 0;
	virtual status_t	OnEndTagNode(BElement * element) = 0;
	virtual status_t	OnTextNode(BText * text) = 0;
	virtual status_t	OnCDataNode(BCData * cData) = 0;
	virtual status_t	OnCommentNode(BComment * comment) = 0;
	virtual status_t	OnBeginDocumentTypeNode(BDocumentType * dt) = 0;
	virtual status_t	OnExternalSubsetNode(BDocumentTypeDefinition * dtd) = 0;
	virtual status_t	OnBeginInternalSubsetNode(BDocumentTypeDefinition * dtd) = 0;
	virtual status_t	OnEndInternalSubsetNode() = 0;
	virtual status_t	OnEndDocumentTypeNode() = 0;
	virtual status_t	OnProcessingInstructionNode(BProcessingInstruction * pi) = 0;
	virtual	status_t	OnElementDeclNode(BElementDecl * decl) = 0;
	virtual status_t	OnAttributeDeclNode(BAttributeDecl * decl) = 0;
	virtual status_t	OnEntityDeclNode(BEntityDecl * decl) = 0;
	//virtual status_t	OnNotationDeclNode(BNotationDecl * decl) = 0;	XXX Not implemented
	
	virtual BDocumentType * GetDocumentType() = 0;
	
protected:
	BElement			* _currentElement;
	uint32				_flags;
	BXMLObjectFactory	* _factory;
	BEntityStore		* _entityStore;
	
private:
	bool				_inDTD;
	
public:
	// Implementations of BXMLParseContext functions
	virtual status_t	OnDocumentBegin(uint32 flags);
	virtual status_t	OnDocumentEnd();
	virtual status_t	OnStartTag(BString & name, BStringMap & attributes);
	virtual status_t	OnEndTag(BString & name);
	virtual status_t	OnTextData(const char * data, int32 size);
	virtual status_t	OnCData(const char * data, int32 size);
	virtual status_t	OnComment(const char * data, int32 size);
	virtual status_t	OnDocumentTypeBegin(BString & name);
	virtual status_t	OnExternalSubset(BString & publicID, BString & systemID,
												uint32 parseFlags);
	virtual status_t	OnInternalSubsetBegin();
	virtual status_t	OnInternalSubsetEnd();
	virtual status_t	OnDocumentTypeEnd();
	virtual status_t	OnProcessingInstruction(BString & target, BString & data);
	virtual	status_t	OnElementDecl(BString & name, BString & data);
	virtual status_t	OnAttributeDecl(BString & element, BString & name,
										BString & type, BString & behavior,
										BString & defaultVal);
	virtual status_t	OnInternalParsedEntityDecl(BString & name, BString & internalData,
													bool parameter, uint32	parseFlags);
	virtual status_t	OnExternalParsedEntityDecl(BString & name, BString & publicID,
													BString & systemID, bool parameter,
													uint32	parseFlags);
	virtual status_t	OnUnparsedEntityDecl(BString & name, BString & publicID,
												BString & systemID, BString & notation);
	virtual status_t	OnNotationDecl(BString & name, BString	& value);
};



// BXMLDocumentParseContext
// =====================================================================
// This is a one-use-only object.  
class BXMLDocumentParseContext : public BXMLDocumentCreationContext 
{
public:
				BXMLDocumentParseContext(BDocument * document,
											BXMLObjectFactory * factory = NULL,
											BEntityStore * entityStore = NULL);
	virtual		~BXMLDocumentParseContext();
	
private:
	BDocument * _document;

public:
	// Implementations of BXMLDocumentCreationContext functions
	virtual status_t	OnBeginDocumentNode();
	virtual status_t	OnEndDocumentNode();
	virtual status_t	OnStartTagNode(BElement * element);
	virtual status_t	OnEndTagNode(BElement * element);
	virtual status_t	OnTextNode(BText * text);
	virtual status_t	OnCDataNode(BCData * cData);
	virtual status_t	OnCommentNode(BComment * comment);
	virtual status_t	OnBeginDocumentTypeNode(BDocumentType * dt);
	virtual status_t	OnExternalSubsetNode(BDocumentTypeDefinition * dtd);
	virtual status_t	OnBeginInternalSubsetNode(BDocumentTypeDefinition * dtd);
	virtual status_t	OnEndInternalSubsetNode();
	virtual status_t	OnEndDocumentTypeNode();
	virtual status_t	OnProcessingInstructionNode(BProcessingInstruction * pi);
	virtual	status_t	OnElementDeclNode(BElementDecl * decl);
	virtual status_t	OnAttributeDeclNode(BAttributeDecl * decl);
	virtual status_t	OnEntityDeclNode(BEntityDecl * decl);
	//virtual status_t	OnNotationDeclNode(BNotationDecl * decl);	XXX Not implemented
	
	virtual BDocumentType *	GetDocumentType();
	
	// Implementations of BXMLParseContext functions
	virtual status_t	OnGeneralParsedEntityRef(BString & name);
	virtual status_t	OnGeneralParsedEntityRef(BString & name, BString & replacement);
	virtual status_t	OnParameterEntityRef(BString & name);
	virtual status_t	OnParameterEntityRef(BString & name, BString & replacement);
};



// BXMLDataSource -- Allows you to get some data to parse with minimal copying
// =====================================================================
class BXMLDataSource
{
public:
	// GetNextBuffer is the same idea as DataIO, except it doesn't require
	// a data copy.  It will be provided with a buffer in *data, so if you
	// have to copy data, then copy into that, but if you have your own
	// buffer, then just replace *data with your pointer.
	// You should return how much data there is in size, and
	// if this is the last iteration, then return a non-zero value in done.
	virtual status_t	GetNextBuffer(size_t * size, uchar ** data, int * done) = 0;
	virtual 			~BXMLDataSource(){;};
};



// Get Data from a BDataIO
// =====================================================================
class BXMLDataIOSource : public BXMLDataSource
{
public:
						BXMLDataIOSource(BDataIO * data);
	virtual				~BXMLDataIOSource();
	virtual status_t	GetNextBuffer(size_t * size, uchar ** data, int * done);

private:
						// Illegal
						BXMLDataIOSource(){;};
						BXMLDataIOSource(const BXMLDataIOSource & copy){;};
	BDataIO		* _data;
};



// Get Data from a Raw Buffer
// =====================================================================
class BXMLBufferSource : public BXMLDataSource
{
public:
						// If len < 0, it is null terminated, so do strlen
						BXMLBufferSource(const char * buffer, int32 len = -1);
	virtual				~BXMLBufferSource();
	virtual status_t	GetNextBuffer(size_t * size, uchar ** data, int * done);

private:
						// Illegal
						BXMLBufferSource();
						BXMLBufferSource(const BXMLBufferSource & copy);
	const char	* _data;
	int32		_length;
};

class BParser {
public:
						BParser();
	virtual				~BParser();
	
	virtual status_t	StartTag(BString &name, BStringMap &attributes, BParser **newParser);
	virtual status_t	EndTag(BString &name);
	virtual status_t	TextData(const char	* data, int32 size);
};

class BDocumentParser : public BXMLParseContext
{
	public:
								BDocumentParser(BParser *root);
		virtual					~BDocumentParser();
	
		virtual status_t		OnDocumentBegin(uint32 flags);
		virtual status_t		OnDocumentEnd();
	
		virtual status_t		OnStartTag(BString &name, BStringMap &attributes);
		virtual status_t		OnEndTag(BString &name);
		virtual status_t		OnTextData(const char *data, int32 size);
		virtual status_t		OnCData(const char *data, int32 size);

		virtual status_t		OnGeneralParsedEntityRef(BString &name);
		virtual status_t		OnGeneralParsedEntityRef(BString &name, BString &replacement);

	private:

		struct parser_rec {
			BParser *parser;
			int32 depth;

			parser_rec() { parser = NULL; depth = 0; };
			~parser_rec() { if (parser) delete parser; };
		};

		uint32					m_flags;
		SmartArray<parser_rec>	m_stack;
};

// BXMLObjectFactory -- Create XML Objects (allows subclassing)
// =====================================================================
class BXMLObjectFactory
{
public:
	// The default implementation returns new allocated standard
	// Be objects, without any fancy subclassing
	virtual BElement				* ElementFactory(BString & name);
	virtual BAttribute				* AttributeFactory(BString & name);
	virtual BText					* TextFactory();
	virtual BCData					* CDataFactory();
	virtual BComment				* CommentFactory();
	virtual BProcessingInstruction	* PIFactory(BString & target);
	virtual BDocumentType			* DocumentTypeFactory();
	virtual BEntityDecl				* EntityDeclFactory(const char * name);
	virtual BElementDecl			* ElementDeclFactory(const char * name);
	virtual BAttributeDecl			* AttributeDeclFactory(BString & element,
											BString & name, uint32 type,
											BString & enumVals, xml_attr_behavior behave,
											BString & defaultVal);
	virtual	BDocumentTypeDefinition	* DTDFactory(BString & name);
	
	virtual ~BXMLObjectFactory(){;};
};

}; // namespace BXmlKit


#endif // _XMLPARSER_H
