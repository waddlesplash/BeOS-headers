/*
  -----------------------------------------------------------------------------

        File: IPathHandler.cpp

        Date: 07.09.05

        Description:	Two functions that provide a simple way to add and read
        				an install path to a file (e.g. a zipfile)
	
		implementation: Marcus Koerner

        Copyright 2005, yellowTAB GmbH, All rights reserved.


  -----------------------------------------------------------------------------
*/ 

#include <storage/Entry.h>
#include <support/String.h>

namespace Z
{
	namespace Support
	{
		// Appends an install path to the an archive
		status_t	SetArchiveInstallPath( const entry_ref& _ref, const BString& _path );
		
		// Delivers back the install path of an archive
		BString		GetArchiveInstallPath( const entry_ref& _ref );		
			
	}
}
