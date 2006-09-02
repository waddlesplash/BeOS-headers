
#ifndef _SUPPORT_CALLSTACK_H
#define _SUPPORT_CALLSTACK_H

#include <support/SupportDefs.h>
#include <support/Vector.h>

class BCallTree;
class BDataIO;

typedef int32 (*b_demangle_func)(	const char *mangled_name,
									char *unmangled_name,
									size_t buffersize);

enum {
	B_CALLSTACK_DEPTH		= 16
};

class BCallStack {
public:
							BCallStack();
							BCallStack(const BCallStack& o);
	
			BCallStack		&operator=(const BCallStack& o);
			
			void			Update(int32 ignoreDepth=0);
			
			size_t			AddressAt(int32 level) const;
			void			SPrint(char *buffer) const;
			void			Print(BDataIO &io) const;
			void			LongPrint(BDataIO &io, b_demangle_func demangler=NULL, const char *prefix = NULL) const;
		
			bool			operator==(const BCallStack& o) const;
	inline	bool			operator!=(const BCallStack& o) const	{ return !(*this == o); }
	
private:

	friend	class			BCallTree;
	
			size_t			GetCallerAddress(int32 level) const;

			size_t			m_caller[B_CALLSTACK_DEPTH];
			int32			_reserved[2];
};

class BCallTreeNode {
public:
							BCallTreeNode();
	virtual					~BCallTreeNode();
	
			void			PruneNode();
			void			ShortReport(BDataIO & io);
			void			LongReport(BDataIO & io, b_demangle_func demangler=NULL,
									   char *buffer=NULL, int32 bufferSize=0);
	
private:
							BCallTreeNode(const BCallTreeNode& o);
			BCallTreeNode&	operator=(const BCallTreeNode& o);
	
	friend	class					BCallTree;
			
			size_t					addr;
			int32					count;
			BCallTreeNode *			higher;
			BCallTreeNode *			lower;
			BCallTreeNode *			parent;
			BVector<BCallTreeNode*>	branches;
};

class BCallTree : public BCallTreeNode {
public:
							BCallTree(const char *name);
	virtual					~BCallTree();
	
			void			Prune();
			void			AddToTree(BCallStack *stack, BDataIO & io);
			void			Report(BDataIO & io, int32 count, bool longReport=false);

private:
							BCallTree(const BCallTree& o);
			BCallTree&		operator=(const BCallTree& o);
			
			BCallTreeNode*	highest;
			BCallTreeNode*	lowest;
};

#endif /* _SUPPORT_CALLSTACK_H */
