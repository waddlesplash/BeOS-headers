/*******************************************************************************
/
/	File:			skip_list.h
/
/	Description:	Kernel skip_list module API
/
/	Copyright 1999, Be Incorporated, All Rights Reserved.
/
*******************************************************************************/

#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

#include <module.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	skip_list is an implementation of William Pugh's "skip lists".
	Skip lists are probablistic alternatives to balanced trees.

	Note that these routines are *NOT* safe to call inside an interrupt
	handler.  They may block on semaphores.
	
	SMP Safety
		insert(), remove(), search(), iterate() and size() are NOT SMP-safe
		with respect to one another, or in regards to delete_list().  In other
		words, don't call delete_list() until you know the other routines are
		not in use.  create_list() and delete_list() ARE SMP-safe with respect
		to each other and themselves.

	When the last user of the module puts it away, any remaining lists are
	deleted.  Note, however, that in this case any memory allocated with
	a custom allocator will NOT be free()'d, and any list specific item delete
	hook will NOT be called, as the module can't depend on the function pointers
	being valid.  If this happens, it's a bug in the _CALLING_ code that needs
	to be fixed.

	const void * create_list(
						skip_list_compare cmp,
						skip_list_delete del,
						uint32 max_nodes,
						uint32 flags,
						skip_list_malloc malloc,
						skip_list_free free,
						void *malloc_info)
		Creates a new skip list.  The list will be ordered by accending key
		value based on the results of the comparison function cmp(). cmp(a,b)
		must return a value less than zero if the key a should sort before key b,
		zero if key a is equal to key b, and greater than zero if key a should
		sort after key b.  skip_list_delete del() will be called each time an item
		is removed from the list, either as the result of a remove() call or a
		return value from an iteration function which includes B_SKIP_LIST_DELETE_ITEM.
		max_nodes is the maximum number of items expected to be inserted into the
		list.  More that max_nodes items may be inserted, but search performance
		will suffer.  flags currently has only one option: permit or deny duplicate
		entries in the list.  malloc, free, and malloc_info permit the caller to
		provide the memory used to hold items in the list.  malloc() and free()
		are called just like their standard library counterparts, except that
		malloc_info is provided as the first parameter for each call.
		Returns an opaque list identifier, or NULL if the creation failed.

	status_t delete_list(const void *list_id)
		Deletes the specified list, returning all related resources to the
		kernel.  Each remaining item in the list will have the skip_list_delete
		function provided at list creation (if there was one) called for it.
		Returns B_OK if the list was deleted, or B_ERROR if an invalid list_id
		was passed.


	These routines operate on a particular list.

	status_t insert(const void *list_id, void *item)
		Insert an item in the list.  Returns B_ERROR if an invalid list was
		supplied.  Returns B_NOT_ALLOWED if the item was a duplicate and
		duplicates were not allowed at list creation time.  Returns B_NO_MEMORY
		if there was not enough memory to add the item to the list.  Otherwise
		it returns B_OK for successfull insertion.

	status_t remove(const void *list_id, void *item)
		Removes the first item from the list that compares as equal via the
		skip_list_compare function specified at list creation time.  Returns
		B_ERROR if given an invalid list, or if the specified item could not
		be found.  Returns B_OK if a matching item was found and removed.  The
		skip_list_delete function given at list creation time will be called
		on the successfully removed item.

	void * search(const void *list_id, void *item)
		Search the specified list for the first item that compares as equal via
		the skip_list_compare function specified at list creation time.  Returns
		the item pointer if the list was valid and a match found, otherwise it
		returns NULL.

	void iterate(const void *list_id, skip_list_iterator itor, void *args, uint32 flags)
		Iterates (forwards or backwards) through the list of items in the order
		established by the skip_list_compare function specified at list creation.
		Each item in the list will have the skip_list_iterator function called with
		args as its first parameter and the current item as its second.  The
		iterator function returns a logical or of one or more of the these values
		affecting iterate()'s behaviour: B_SKIP_LIST_DELETE_ITEM causes the current
		item to be removed from the list as with remove() above.  B_SKIP_LIST_ABORT
		causes iteration to terminate without processing further items.
		B_SKIP_LIST_CONTINUE allows the iteration process to continue.
		B_SKIP_LIST_CONTINUE and B_SKIP_LIST_ABORT are mutually exclusive options.

	uint32 size(const void *list_id)
		Returns the number of items in the specified list.  Returns zero for
		invalid lists.
*/

#define B_SKIP_LIST_MODULE_NAME "generic/skip_list/v1"

/*
	list creation flags
*/
enum {
	B_SKIP_LIST_ALLOW_DUPLICATES = (1 << 0)
};

/*
	iterate function flags
*/
enum {
	B_SKIP_LIST_FORWARDS = (0 << 0),
	B_SKIP_LIST_BACKWARDS = (1 << 0),
	B_SKIP_LIST_START_KEY = (1 << 1),
	B_SKIP_LIST_START_KEY_MUST_MATCH = (1 << 2)
};

/*
	iterator function result flags
*/
enum {
	B_SKIP_LIST_CONTINUE = 0,
	B_SKIP_LIST_ABORT = (1 << 0),
	B_SKIP_LIST_DELETE_ITEM = (1 << 1)
};
typedef int32 (*skip_list_compare)(void *a, void *b);
typedef void (*skip_list_delete)(void *a);
typedef void * (*skip_list_malloc)(void *cookie, size_t size);
typedef void (*skip_list_free)(void *cookie, void *data);
typedef uint32 (*skip_list_iterator)(void *args, void *item);

typedef struct {
	module_info		minfo;
	const void *	(*create_list)(
						skip_list_compare cmp,
						skip_list_delete del,
						uint32 max_nodes,
						uint32 flags,
						skip_list_malloc malloc,
						skip_list_free free,
						void *malloc_info
					);
	status_t		(*delete_list)(const void *list_id);
	status_t		(*insert)(const void *list_id, void *item);
	status_t		(*remove)(const void *list_id, void *item);
	void *			(*search)(const void *list_id, void *item);
	void			(*iterate)(const void *list_id, skip_list_iterator itor, void *args, uint32 flags, void *start_key);
	uint32			(*size)(const void *list_id);
} skip_list_module_info;

#ifdef __cplusplus
}
#endif

#endif

