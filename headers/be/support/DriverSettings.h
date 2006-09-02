/*
 * File:		DriverSettings.h
 * Author:		Rene Gollent
 * Company:		yellowTAB
 * Date:		03/18/2004
 * Description:
 * Support class intended as a general purpose interface for creating, 
 * retrieving and modifying driver settings files as used via the kernel
 * driver_settings API.
 *
 */
 
#ifndef _SUPPORT_DRIVER_SETTINGS_H_
#define _SUPPORT_DRIVER_SETTINGS_H_

#include <storage/Path.h>
#include <support/DriverParameter.h>
#include <support/Flattenable.h>
#include <support/KeyedVector.h>
#include <support/StreamIO.h>
#include <support/String.h>

#include <be_prim.h>

namespace Z {
namespace Support {

struct driver_parameter;
struct driver_settings;

class BDriverParameter;

class BDriverSettings : public BFlattenable, public BAbstractParameterStore
{
	public:
		// create indicates that the settings file should be created
		// if it does not already exist
									BDriverSettings();
									BDriverSettings(const BString& _path, bool _create = false);
									BDriverSettings(const BPath& _path, bool _create = false);
									BDriverSettings(entry_ref& _path, bool _create = false);
		virtual			 			~BDriverSettings();
		
				status_t			InitCheck() const;

		// BFlattenable interface			
		virtual	status_t		 	Flatten(void* _buffer, ssize_t _bufferSize) const;
		virtual status_t		 	Unflatten(type_code _type, const void* _buffer, ssize_t _bufferSize);
		virtual ssize_t				FlattenedSize() const;
		virtual bool				IsFixedSize() const;
		virtual type_code			TypeCode() const;
		virtual bool				AllowsTypeCode(type_code _code) const;
		
				status_t			SetTo(const BString& _path, bool _create = false);
				status_t			SetTo(const BPath& _path, bool _create = false);
				status_t			SetTo(entry_ref& _path, bool _create = false);
		
		// settings manipulation and retrieval functions
				void				PrintToStream(BDataIO& _output = BOut) const;
		
				void				MakeEmpty();
		
		const	BString&			GetTopLevelComment() const;
				void				SetTopLevelComment(const BString& _comment);
		
		// write settings to given path
				status_t			Save();

	private:
				void				BuildTopLevelComments(char* _buffer);
				status_t			BuildSettings(entry_ref& _path);
				void				BuildSettingsRoot(driver_settings* _settings);
				void				RecursiveBuildDriverParameters(driver_parameter* _param,
							                               BDriverParameter& _current);
							                               
				virtual void		_ReservedVirtual1();
				virtual void		_ReservedVirtual2();
				virtual void		_ReservedVirtual3();
				virtual void		_ReservedVirtual4();
				virtual void		_ReservedVirtual5();
				virtual void		_ReservedVirtual6();
				virtual void		_ReservedVirtual7();
				virtual void		_ReservedVirtual8();
				virtual void		_ReservedVirtual9();
				virtual void		_ReservedVirtual10();
	private:
		BPath				fPath;
		status_t			fInitStatus;
		BString				fTopComment;
		char				_FBCPadding[32];	
};

} // namespace Support
} // namespace Z

#ifndef _ZETA_IMPLICIT_NAMESPACE
using Z::Support::BDriverSettings;
#endif

#endif // _SUPPORT_DRIVER_SETTINGS_H_
