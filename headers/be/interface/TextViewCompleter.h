#ifndef _TEXTVIEW_COMPLETETER_H
#define _TEXTVIEW_COMPLETETER_H

#include <MessageFilter.h>
#include <String.h>
#include <Vector.h>
#include <OrderedVector.h>

class BTextView;

namespace Z {
namespace Interface {
	
namespace Private {
	class ChoiceList;
}

enum completion_mode
{
	cmSingle,
	cmMulti
};

class BTextViewCompleter : public BMessageFilter
{
	public:
								BTextViewCompleter(completion_mode _mode = cmSingle);
								BTextViewCompleter(bool _match_case, 
								                   completion_mode _mode = cmSingle);

		virtual	filter_result	Filter(BMessage* _message, BHandler** _target);

				void			SetMatchCase(bool _match);
				bool			MatchesCase();
				void			AddCompletion(const BString& _string);
				void			AddDelimiter(const BString& _delimiter);
				void			ClearDelimiterList();
				
				void			SetMode(completion_mode _mode);
				completion_mode	GetMode() const;


	protected:
				status_t		PopulateMatchList(const BString& _bytes, 
				                                  const BTextView& _control, 
				                                  int32 _start, 
				                                  int32 _caret);

		virtual	void			MatchesFound(ssize_t _wordstart, 
								             int32 _matchstart, 
								             int32 _matchend,
								             BTextView& _control,
								             B::Support::BOrderedVector<BString>& _matches);
								              	
	private:
				bool			IsDelimiter(const BString& _bytes);
				BPoint			GetListPos(const BTextView& _control, int32 _textoffset);
				
		virtual	void			PaddingtonBear();
		virtual	void			PaddingtonHat();
		virtual	void			PaddingtonUmbrella();
		virtual	void			PaddingtonMarmaladeSandwitch();
		virtual	void			PaddingtonBriefcase();
		virtual	void			PaddingtonRaincoat();
		virtual	void			PaddingtonBoots();
		

	protected:
		B::Support::
		BOrderedVector<BString>		fCompletions;						

		B::Support::
		BOrderedVector<BString>		fMatchList;						

		B::Support::
		BVector<BString>			fDelimiters;						

	private:
		ssize_t						fCompareStart;		
		completion_mode				fMode;
		bool						fCaseSensitive;
		uint32						fPaddington[7];
		Private::
		ChoiceList*					fChoiceList;
};

} // Interface
} // Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BTextViewCompleter;
using Z::Interface::completion_mode;
using Z::Interface::cmSingle;
using Z::Interface::cmMulti;
#endif

#endif	// _TEXTVIEW_COMPLETER_H
