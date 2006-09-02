/*
 * File:		DriverParameter.h
 * Author:		Rene Gollent
 * Company:		yellowTAB
 * Date:		03/12/2004
 * Description:
 * Support class intended as a basis for creating an object-oriented user space
 * interface to kernel settings files created via the driver_settings API.
 *
 */

#ifndef _DRIVERPARAMETER_H_
#define _DRIVERPARAMETER_H_

#include <support/StreamIO.h>
#include <support/String.h>
#include <support/Vector.h>

namespace Z {
namespace Support {

using B::Support::BVector;

class BDriverParameter;

class BAbstractParameterStore
{
	
	public:
		// sub-parameter manipulation
		virtual						~BAbstractParameterStore();
		
		size_t						CountParameters() const;
		BDriverParameter &			GetParameterAt(size_t _index) const;
		status_t					RemoveParameterAt(size_t _index);
		BDriverParameter &			AddParameter(const BString& _paramname);
		
		BDriverParameter &			operator[](size_t _index);
	
	private:
		virtual void				BachelorPad1();
		virtual void				BachelorPad2();
		virtual void				BachelorPad3();
		virtual void				BachelorPad4();
		virtual void				BachelorPad5();
		virtual void				BachelorPad6();
		virtual void				BachelorPad7();
		virtual void				BachelorPad8();
		virtual void				BachelorPad9();
		virtual void				BachelorPad10();
		virtual void				BachelorPad11();
		
		BVector<BDriverParameter *> fParameters;
		char						_MattressPadding[32];
};

class BDriverParameter : public BAbstractParameterStore
{
	public:
									BDriverParameter(const BString& _name);
		virtual						~BDriverParameter();
		
		const	BString &			GetName() const;
		
		// value manipulation
		size_t 						CountValues() const;
		const BString &				GetValueAt(size_t _index) const;
		status_t					UpdateValueAt(const BString &_value, size_t _index);
		status_t 					RemoveValueAt(size_t _index);
		status_t 					AddValue(const BString& _value);
		bool						HasValue(const BString& _value) const;

		const BString &				GetComment() const;
		void						SetComment(const BString& _comment);
		
		void						PrintToStream(BDataIO &_output = BOut, size_t _level = 0) const;
				
	private:
									BDriverParameter();
		virtual void				BachelorPad1();
		virtual void				BachelorPad2();
		virtual void				BachelorPad3();
		virtual void				BachelorPad4();
		virtual void				BachelorPad5();
		virtual void				BachelorPad6();
		virtual void				BachelorPad7();
		virtual void				BachelorPad8();
		virtual void				BachelorPad9();
		virtual void				BachelorPad10();
		virtual void				BachelorPad11();
	
	private:
		BString 					fName;
		BString						fComment;
		BVector<BString> 			fValues;
		char						_Paddles[32];	
};

} // namespace Private
} // namespace Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Support::BDriverParameter;
#endif

#endif // _DRIVERPARAMETER_H_
