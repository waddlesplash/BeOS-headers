
#ifndef _XML_WRITER_H
#define _XML_WRITER_H

#include <XMLDefs.h>
#include <String.h>
#include <StringMap.h>

namespace BXmlKit {

// WriteHTML takes a BXMLObject and writes it to a stream.
status_t WriteHTML(BXMLObject * object, BDataIO * stream);
status_t WriteXML(BXMLObject * object, BDataIO * stream, bool noWhitespace);

enum {
	stfLeaf		= 0x00000001,
	stfCanAddWS	= 0x00000002
};

class BCodifier {
public:
						BCodifier();
	virtual				~BCodifier();
	
	virtual status_t	StartTag(const BString &name, const BStringMap &attributes, uint32 formattingHints=0);
	virtual status_t	EndTag(const BString &name);
	virtual status_t	TextData(const char	* data, int32 size);
	virtual status_t	Comment(const char *data, int32 size);
};

class BOutputStream : public BCodifier {
public:
						BOutputStream(BDataIO &stream, bool writeHeader=false);
	virtual				~BOutputStream();
	
	virtual status_t	StartTag(const BString &name, const BStringMap &attributes, uint32 formattingHints=0);
	virtual status_t	EndTag(const BString &name);
	virtual status_t	TextData(const char	* data, int32 size);
	virtual status_t	Comment(const char *data, int32 size);

private:

			void		Indent();

			BDataIO	&	m_stream;
			int32		m_depth;
			int32		m_lastPrettyDepth;
			bool		m_isLeaf:1;
			bool		m_openStartTag:1;
			uint8		m_reserved:6;
};

}; //namespace BXmlKit


#endif // _XML_WRITER_H
