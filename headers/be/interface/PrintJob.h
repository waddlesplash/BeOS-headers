//******************************************************************************
//
//	File:		PrintJob.h
//
//	Description:	client region class.
//
//	Copyright 1992-97, Be Incorporated
//
//******************************************************************************

#pragma once

#ifndef	_PRINTSESSION_H
#define	_PRINTSESSION_H

#include <InterfaceDefs.h>
#include <Rect.h>
#include <View.h>
#include <ClassInfo.h>

//------------------------------------------------------------------

struct	print_file_header {
	int32	version;
	int32	page_count;
	int32	_reserved_1_;
	int32	_reserved_2_;
	int32	_reserved_3_;
	int32	_reserved_4_;
	int32	_reserved_5_;
};

//------------------------------------------------------------------------------

class BPrintJob {
public:

					BPrintJob(const char *job_name);
virtual				~BPrintJob();

		int32		ConfigPage();
		int32		ConfigJob();
virtual	void		DrawView(BView *a_view, BRect a_rect, BPoint where);
		void		CommitJob();	
		int32		FirstPage();
		int32		LastPage();
		BRect		PaperRect();
		BRect		PrintableRect();
		bool		CanContinue();
		void		BeginJob();	
		void		SpoolPage();
		BMessage	*Settings();	
		void		SetSettings(BMessage *a_msg);	
		void		CancelJob();
private:

virtual void		_ReservedPrintJob1();
virtual void		_ReservedPrintJob2();
virtual void		_ReservedPrintJob3();
virtual void		_ReservedPrintJob4();

					BPrintJob(const BPrintJob &);
		BPrintJob	&operator=(const BPrintJob &);

		int			AddToSpoolQueue(BPicture *a_picture, BRect *a_rect, BPoint where);
		void		mangle_name(char *filename);
		void		add_setup_spec();
		void		HandlePageSetup(BMessage *setup);
		void		HandlePrintSetup(BMessage *setup);
		void		seek_to_end();
		int32		current_position();
		int			end_of_page();

		char		*print_job_name;
		int32		page_number;
		int32		spool_file_ref;
		print_file_header	current_header;
		BRect				paper_size;
		BRect				usable_size;
		int					pr_error;
		char				spool_file_name[256];	
		BMessage			*setup_msg;
		BMessage			*job_msg;
		char				stop_the_show;
		int32				cur_page_desc_offset;
		int32				num_pict_in_page;
		int32				first_page;
		int32				last_page;
		uint32				_reserved[4];
};

#endif
