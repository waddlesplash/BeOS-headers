/****************************************************************** 
	File: GLView.h
	Copyright (c) 1997 by Be Incorporated.  All Rights Reserved.
*******************************************************************/

#ifndef BGLVIEW_H
#define BGLVIEW_H

#include <GL/gl.h>

struct __glBeContext;

#include <AppKit.h>
#include <interface/Window.h>
#include <interface/View.h>
#include <interface/Bitmap.h>
#include <game/WindowScreen.h>

class BGLView : public BView {
public:

					BGLView(BRect rect, char *name,
						ulong resizingMode, ulong mode,
						ulong options);
					~BGLView();

		void		LockGL();
		void		UnlockGL();
		void		SwapBuffers();
		BView *     EmbeddedView();
		status_t    CopyPixelsOut(BPoint source, BBitmap *dest);
		status_t    CopyPixelsIn(BBitmap *source, BPoint dest);
virtual void        ErrorCallback(GLenum errorCode);
		
virtual	void		Draw(BRect updateRect);

virtual void		AttachedToWindow();
virtual void        AllAttached();
virtual void        DetachedFromWindow();
virtual void        AllDetached();
 
virtual void		FrameResized(float width, float height);
virtual status_t    Perform(perform_code d, void *arg);

/* The public methods below, for the moment,
   are just pass-throughs to BView */

virtual status_t    Archive(BMessage *data, bool deep = true) const;

virtual void        MessageReceived(BMessage *msg);
virtual void        SetResizingMode(uint32 mode);

virtual void        Show();
virtual void        Hide();

virtual BHandler   *ResolveSpecifier(BMessage *msg,
									                         int32 index,
									                         BMessage *specifier,
									                         int32 form,
									                         const char *property);
virtual status_t    GetSupportedSuites(BMessage *data);

private:

virtual void        _ReservedGLView1();
virtual void        _ReservedGLView2(); 
virtual void        _ReservedGLView3(); 
virtual void        _ReservedGLView4(); 
virtual void        _ReservedGLView5(); 
virtual void        _ReservedGLView6(); 
virtual void        _ReservedGLView7(); 
virtual void        _ReservedGLView8(); 

                    BGLView(const BGLView &);
	    BGLView     &operator=(const BGLView &);

		void        dither_front();
		bool        confirm_dither();
		void        draw(BRect r);
		
__glBeContext *		m_gc;
		uint32		m_options;
		uint32      m_ditherCount;
		BLocker		m_drawLock;
		BLocker     m_displayLock;
		BView *     m_embeddedFront;
		BView *     m_embeddedBack;
		BBitmap *   m_ditherMap;
		BRect       m_bounds;
		int16 *     m_errorBuffer[2];
		uint64      _reserved[8];
};

class BGLScreen : public BWindowScreen {
public:

					BGLScreen(char *name,
						ulong screenMode, ulong options,
						status_t *error, bool debug=false);
					~BGLScreen();

		void		LockGL();
		void		UnlockGL();
		void		SwapBuffers();
virtual void        ErrorCallback(GLenum errorCode);

virtual void		ScreenConnected(bool connected);
virtual void		FrameResized(float width, float height);
virtual status_t    Perform(perform_code d, void *arg);

/* The public methods below, for the moment,
   are just pass-throughs to BWindowScreen */

virtual status_t    Archive(BMessage *data, bool deep = true) const;
virtual void        MessageReceived(BMessage *msg);

virtual void        Show();
virtual void        Hide();

virtual BHandler   *ResolveSpecifier(BMessage *msg,
                        int32 index,
						BMessage *specifier,
						int32 form,
						const char *property);
virtual status_t    GetSupportedSuites(BMessage *data);

private:

virtual void        _ReservedGLScreen1();
virtual void        _ReservedGLScreen2();
virtual void        _ReservedGLScreen3();
virtual void        _ReservedGLScreen4();
virtual void        _ReservedGLScreen5();
virtual void        _ReservedGLScreen6();
virtual void        _ReservedGLScreen7();
virtual void        _ReservedGLScreen8(); 

                    BGLScreen(const BGLScreen &);
	    BGLScreen   &operator=(const BGLScreen &);

__glBeContext *		m_gc;
		long		m_options;
		BLocker		m_drawLock;
		uint64      _reserved[8];
};

#endif





