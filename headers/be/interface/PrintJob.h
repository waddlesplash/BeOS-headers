//******************************************************************************
//
//	File:		PrintJob.h
//
//	Description:	client region class.
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef	_PRINTSESSION_H
#define	_PRINTSESSION_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_RECT_H
#include "Rect.h"
#endif
#ifndef	_OBJECT_H
#include <Object.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------

typedef	struct	{
	long	version;
	long	page_count;
	long	_reserved_1_;
	long	_reserved_2_;
	long	_reserved_3_;
	long	_reserved_4_;
	long	_reserved_5_;
} print_file_header;

//------------------------------------------------------------------------------

class BPrintJob : public BObject {
public:

					BPrintJob(char *job_name);
virtual				~BPrintJob();

		long		InitJob();
virtual	void		DrawView(BView *a_view, BRect a_rect, BPoint where);
		void		Commit();
		long		FirstPage();
		long		LastPage();
		BRect		PaperRect();
		BRect		PrintableRect();
		bool		CanContinue();
		void		BeginPrinting();
		void		SpoolPage();
		BMessage	*Config();
		void		SetConfig(BMessage *a_msg);
		void		CancelJob();
private:
		int			AddToSpoolQueue(BPicture *a_picture, BRect *a_rect, BPoint where);
		void		mangle_name(char *filename);
		void		add_setup_spec();
		void		HandleSetup(BMessage *a_message);
		void		seek_to_end();
		long		current_position();
		int			end_of_page();
private:
		char				*print_job_name;
		long				page_number;
		long				spool_file_ref;
		print_file_header	current_header;
		BRect				paper_size;
		BRect				usable_size;
		int					pr_error;
		char				spool_file_name[256];	
		BMessage			*setup_msg;
		BMessage			*job_msg;
		char				stop_the_show;
		long				cur_page_desc_offset;
		long				num_pict_in_page;
};

#endif
