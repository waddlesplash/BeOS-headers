/*
  -----------------------------------------------------------------------------
  
  File: NetworkAddon.cpp
  
  Description: This is a part of Networkconfiguration
               This is the main construct for every 
               NWC Addon. 
  
  Copyright 2003, 2004, yellowTAB GmbH, All rights reserved.
  
  Developer: Benzler Andreas 
  
  -----------------------------------------------------------------------------
*/

#ifndef NETWORK_ADDON_H
#define NETWORK_ADDON_H

class BList;
class BView;
class BRect;

class NetworkAddon 
{
	public:
								NetworkAddon();
		virtual					~NetworkAddon();
		
		virtual			BView*	CreateView(BRect& bounds);	// Create a Tabview in the container 
		virtual			void	Revert();					// Forward Revert to the container
		virtual			void	New();						// What todo for new profile
		virtual			void	Startup();					// What todo on startup  (change profile)
		virtual			void	Shutdown();					// What todo on shutdown (change profile)
		virtual 		bool	Save();						// Forward Save to the AddOn
	
		virtual	const	char*	Name();						// Name of the container
		virtual const	char*	Section();					// section name (for network.conf)??? -- throw away
		virtual const	char*	Description();				// description of section - throw away
		virtual const	BList*	FileList();					// list of files used for configuration
		virtual			int		Importance();				// sort order in tab list.
	
						bool	CheckIP(const char *, unsigned char);
						bool	CheckHostName(const char *);	
};

#endif // NETWORK_ADDON_H

