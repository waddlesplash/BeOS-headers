#ifndef _3D_ETHERIC_WORLD_H
#define _3D_ETHERIC_WORLD_H

#ifndef _3D_WORLD_H 
#include "3dWorld.h"
#endif

class B3dEthericWorld : public B3dWorld {
 public:
	B3dEthericWorld(char *name, B3dUniverse *universe = 0);
	~B3dEthericWorld();

	virtual void        AddThing(B3dThing *thing, ulong flags);
	inline long         CountThings();
	virtual B3dThing    *GetThing(long id);
	virtual long        GetThingId(char *name);
	virtual long        GetNthThingId(long index);
	virtual void        RemoveThing(long id);
	virtual void        CheckNewThings();
	virtual void        UpdateThings();

	virtual bool        GetTouch(B3dVector *origin, B3dVector *axis, B3dTouchDesc *touch);

	virtual void        RenderHook(B3dCamera *camera, B3dRenderer *renderer);
	
 private:
/*	typedef struct BENode {
		long          NbObject;
		B3dVector     PtRef;
		B3dVector     Norm;
		struct BENode *pipo;
	} BENode;
	
	char         RootType;
	long         Root;
	long         NodeFree;
	struct Node  *NodeList;
	long         NodeCount;
	long         LeafFree;
	struct Leaf  *LeafList;
	long         LeafCount;
	long         LeafNew;
	long         LeafDyn;
	long         *OrderList;

	void         ExtendNodeList();
	void         ExtendLeafList();
	long         ExpandNode(long node, long prev = -1);
	void         FreeNode(long node);
	long         NewNode();
	long         CountLeafList(long leaf);
	long         ParseLeaf(long leaf, long count);
	long         SortThings(B3dVector *camera);
	long         SortNode(B3dVector *camera, long node, long index);
*/
	struct Node  *ObjList;
	long         ListCount;
	long         ObjUsed;
	long         ObjFree;
	long         *OrderList;
	float        *DepthList;
	
	void         ExtendList();
	long         SortThings(B3dVector *camera, B3dMatrix *rotation);
};

#endif















