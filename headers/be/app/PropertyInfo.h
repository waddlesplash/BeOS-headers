/*******************************************************************************
/
/	File:			PropertyInfo.h
/
/	Description:	Utility class for maintain scripting information
/
/	Copyright 1997-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/

#ifndef _PROPERTY_INFO_H
#define _PROPERTY_INFO_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <Flattenable.h>

/*----------------------------------------------------------------*/
/*----- the property_info structure ------------------------------*/

struct property_info {
	char	*name;
	uint32	commands[10];
	uint32	specifiers[10];
	char	*usage;
	uint32	extra_data;
};

#define B_PROPERTY_INFO_TYPE 'SCTD'

/*----------------------------------------------------------------*/
/*----- BPropertyInfo class --------------------------------------*/

class BPropertyInfo : public BFlattenable {
public:
						BPropertyInfo(property_info *p = NULL,
										bool free_on_delete = false);
virtual					~BPropertyInfo();

virtual	int32			FindMatch(BMessage *msg,
									int32 index,
									BMessage *spec,
									int32 form,
									const char *prop,
									void *data = NULL) const;

virtual	bool			IsFixedSize() const;
virtual	type_code		TypeCode() const;
virtual	ssize_t			FlattenedSize() const;
virtual	status_t		Flatten(void *buffer, ssize_t size) const;
virtual	bool			AllowsTypeCode(type_code code) const;
virtual	status_t		Unflatten(type_code c, const void *buf, ssize_t size);

		void			PrintToStream() const;

/*----- Private or reserved -----------------------------------------*/
protected:
static	bool			MatchCommand(uint32 what, int32 i, property_info *pi);
static	bool			MatchSpecifier(uint32 form, property_info *pi);

private:
virtual	void			_ReservedPropertyInfo1();
virtual	void			_ReservedPropertyInfo2();
virtual	void			_ReservedPropertyInfo3();
virtual	void			_ReservedPropertyInfo4();

						BPropertyInfo(const BPropertyInfo &);
		BPropertyInfo	&operator=(const BPropertyInfo &);
		void			FreeMem();

		property_info	*fPropInfo;
		int32			fCount;
		bool			fInHeap;
		uint32			_reserved[4];
};

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _PROPERTY_INFO_H */
