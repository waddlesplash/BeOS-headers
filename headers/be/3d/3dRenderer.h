#ifndef _3D_RENDERER_H
#define _3D_RENDERER_H

#include <InterfaceDefs.h>

#ifndef _3D_DEFS_H
#include "3dDefs.h"
#endif
#ifndef _RGBA_COLOR_H
#include "RGBAColor.h"
#endif
#ifndef _3D_LIGHTER_H
#include "3dLighter.h"
#endif

enum {
	B_RENDER_FILL_3_1 = 0,
	B_RENDER_FILL_3_3 = 1,

	B_RENDER_HOOK_COUNT = 2
};

typedef void (*render_hook) ();

typedef long (*B_FILL_3_1)(long, long,
						   long, long,
						   long, long,
						   void*,
						   void *, long);
typedef long (*B_FILL_3_3)(long, long, void*,
						   long, long, void*,
						   long, long, void*,
						   void*, long);

class B3dEraseOptions {
 public:
	RGBAColor     color;
};

class B3dRenderer {
 public:
	void     *bits;
	long     bytesPerRow;
	long     width;
	long     height;
	
	B3dRenderer(B3dLighter *lighter);
	virtual ~B3dRenderer();
	long SetBuffer(void *bits, long bytes_per_row, color_space mode,
				   long width, long height);
	void EraseBuffer(B3dEraseOptions *options);
	void SetIndexMap(uchar *map, rgb_color *color_list);
	inline render_hook *RenderHooks();
 private:
	bool        CopyBuffer;
	render_hook *myRenderHooks;
	ulong       *IndexMap;
	color_space cs;
	B3dLighter  *myLighter;
};
	
render_hook *B3dRenderer::RenderHooks() {
	return myRenderHooks;
}

#endif

















