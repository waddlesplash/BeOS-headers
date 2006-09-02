#ifndef FORMATTER_H
#define FORMATTER_H

#include <String.h>

namespace Z {
namespace Locale {


class BFormatter
{
	public:
						BFormatter(const char* FormatStr, char Value);
						BFormatter(const char* FormatStr, uint8 Value);
						BFormatter(const char* FormatStr, int8 Value);
						BFormatter(const char* FormatStr, uint16 Value);
						BFormatter(const char* FormatStr, int16 Value);
						BFormatter(const char* FormatStr, uint32 Value);
						BFormatter(const char* FormatStr, int32 Value);
						BFormatter(const char* FormatStr, uint64 Value);
						BFormatter(const char* FormatStr, int64 Value);
						BFormatter(const char* FormatStr, float Value);
						BFormatter(const char* FormatStr, double Value);
						
						
						operator const char*() const;
		const char*		String() const;

	protected:

	private:
		BString			fValue;
};
#endif

inline 
BFormatter::operator const char*() const
{
	return String();
}

inline const char* 
BFormatter::String() const
{
	return fValue.String();
}

}	//  Locale
}	//	Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Locale::BFormatter;
#endif
