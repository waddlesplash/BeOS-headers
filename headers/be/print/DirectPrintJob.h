/*******************************************************************************
/
/	File:			DirectPrintJob.h
/
/	Copyright 1996-2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/

#ifndef	_DIRECT_PRINTJOB_H
#define	_DIRECT_PRINTJOB_H

#include <OS.h>
#include <Message.h>
#include <Rect.h>
#include <PrintJob.h>
#include <print/PrinterRasterAddOn.h>

class BView;
class BPicture;


class BDirectPrintJob : public BPrintJob
{
public:
			BDirectPrintJob(const char *job_name);
	virtual	~BDirectPrintJob();


	struct bitmap_header_t
	{
		color_space space;
		uint32 flags;
		int pixelWidth;
		int pixelHeight;
		int xdpi;
		int ydpi;
		uint32 rsvr[4];
	};

	struct bitmap_rect_t
	{
		int pixelLeft;
		int pixelTop;
		int pixelWidth;
		int pixelHeight;
		int pixelOffsetLeft;
		int pixelOffsetTop;
		uint32 rsvr[4];
	};

	status_t StartJob(uint32 nbPages, const bitmap_header_t& bitmapHdr);


protected:

	virtual status_t BeginDirectMode(BBitmap& bitmap);
	virtual status_t EndDirectMode();

	virtual status_t BeginPage(const uint32 page);
	virtual status_t EndPage();

	virtual status_t FillBitmap(const bitmap_rect_t& rect, BBitmap& bitmap);

private:
			BDirectPrintJob(const BDirectPrintJob &);
	BDirectPrintJob& operator = (const BDirectPrintJob &);
	virtual void _ReservedDirectPrintJob1();
	virtual void _ReservedDirectPrintJob2();
	virtual void _ReservedDirectPrintJob3();
	virtual void _ReservedDirectPrintJob4();

			status_t	BeginJob();
			status_t	SpoolPage();
			status_t	CommitJob();
	virtual	status_t	DrawView(BView *, BRect, BPoint);
			status_t	DrawPictures(BPicture * const *, const BRect *, const BPoint *, const uint32);

private:
	void *fPrivate;
	uint32 Reserved[4];
};

 
#endif

