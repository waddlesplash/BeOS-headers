#ifndef _3D_FACE_LOOK_H
#define _3D_FACE_LOOK_H

#ifndef _3D_MODEL_H
#include "3dModel.h"
#endif
#ifndef _3D_LOOK_H
#include "3dLook.h"
#endif

class B3dLightProc;

enum {
	B_BODY_COLOR,
	B_FACE_COLOR,
	B_CORNER_COLOR
};

class B3dFlatFaceLook : public B3dLook {
 public:
	short  *lookTable;
	B3dFlatFaceLook(char *name, B3dModel *model, RGBAColor *color,
					ulong status = B_SMOOTH_SHADE);
	virtual ~B3dFlatFaceLook();
	virtual void *ClipHook(void *look1, float rel1, void *look2, float rel2);
};

class B3dFlat1FaceLook : public B3dFlatFaceLook {
 public:
	B3dFlat1FaceLook(char *name, B3dModel *model, RGBAColor *color,
					 ulong status = B_SMOOTH_SHADE);
	virtual ~B3dFlat1FaceLook();
	virtual void Draw(ulong           flags,
					  B3dMatrix       *rotation,
					  B3dVector       *translation,
					  B3dLens         *lens,
					  B3dRenderer     *renderer,
					  B3dLightProc    *lightProc);
 private:
	ulong    *BufferLook;
};

class B3dFlat2FaceLook : public B3dFlatFaceLook {
 public:
	B3dFlat2FaceLook(char *name, B3dModel *model, RGBAColor *color, RGBAColor *list,
					 ulong status = B_SMOOTH_SHADE);
	virtual ~B3dFlat2FaceLook();
	virtual void Draw(ulong         flags,
					  B3dMatrix     *rotation,
					  B3dVector     *translation,
					  B3dLens       *lens,
					  B3dRenderer   *renderer,
					  B3dLightProc  *lightProc);
	RGBAColor    *listColor;
 private:
	RGBAColor    *BufferLook;
};

class B3dFlat3FaceLook : public B3dFlatFaceLook {
 public:
	B3dFlat3FaceLook(char *name, B3dModel *Model, RGBAColor *color, RGBAColor *list,
					 ulong status = B_SMOOTH_SHADE);
	virtual ~B3dFlat3FaceLook();
	virtual void Draw(ulong         flags,
					  B3dMatrix     *rotation,
					  B3dVector     *translation,
					  B3dLens       *lens,
					  B3dRenderer   *renderer,
					  B3dLightProc  *lightProc);
	RGBAColor    *listColor;
 private:
	ulong    *BufferLook;
};

#endif

 









