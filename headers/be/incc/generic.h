/*
 *   generic.h
 *
 *   Macros to approximate generic class declarations.
 *
 *           Copyright (c) 1991, MetaWare Incorporated
 */

#ifndef __GENERIC_H
#define __GENERIC_H 1
#pragma push_align_members(64);


/*
 *   Token-pasting macros.
 *
 *   Two levels of indirection are required to expand arguments that
 *   are themselves macros.
 */

#define name2(tok1,tok2)      _PASTE2(tok1,tok2)
#define _PASTE2(tok1,tok2)      tok1##tok2
#define name3(tok1,tok2,tok3)    _PASTE3(tok1,tok2,tok3)
#define _PASTE3(tok1,tok2,tok3)    tok1##tok2##tok3
#define name4(tok1,tok2,tok3,tok4)  _PASTE4(tok1,tok2,tok3,tok4)
#define _PASTE4(tok1,tok2,tok3,tok4)  tok1##tok2##tok3##tok4



/*
 *   Declaration and implementation macros.
 */

#define declare(generic,type) name2(generic,declare)(type)
#define implement(generic,type) name2(generic,implement)(type)
#define declare2(generic,type1,type2) name2(generic,declare2)(type1,type2)
#define implement2(generic,type1,type2) name2(generic,implement2)(type1,type2)



/*
 *   Error-handling functions.
 *
 *   The function genericerror is not implemented because its 
 *   functionality is unclear and documentation is insufficient.
 *   The declaration is provided for AT&T compatibility only.
 */

extern genericerror(int,char*);
typedef int (*GPT)(int,char*);
#define set_handler(generic,type,x) name4(set_,type,generic,_handler)(x)
#define errorhandler(generic,type) name3(type,generic,handler)
#define callerror(generic,type,a,b) (*errorhandler(generic,type))(a,b)


#pragma pop_align_members();
#endif	// __GENERIC_H


/**          Copyright (c) 1991, MetaWare Incorporated             **/
