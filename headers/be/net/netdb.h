/*
 * netdb.h
 * Copyright (c) 1995-97 Be, Inc.	All Rights Reserved 
 *
 * BSD network database-like interface
 *
 * Do not expect total BSD compatibility from this interface!
 *
 */
#ifndef _NETDB_H
#define _NETDB_H

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _SOCKET_H
#include <socket.h>
#endif /* _SOCKET_H */

#define MAXHOSTNAMELEN 64

#define HOST_NOT_FOUND 1
#define TRY_AGAIN 2
#define NO_RECOVERY 3
#define NO_DATA 4

#ifndef h_errno
extern int *_h_errnop(void);
#define h_errno (*_h_errnop())
#endif /* h_errno */


struct hostent {
	char *h_name;
	char **h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
};
#define h_addr h_addr_list[0]

struct servent {
	char *s_name;
	char **s_aliases;
	int s_port;
	char *s_proto;
};	

struct hostent *gethostbyname(const char *hostname);
struct hostent *gethostbyaddr(const char *hostname, int len, int type);
struct servent *getservbyname(const char *name, const char *proto);
void herror(const char *);
unsigned long inet_addr(const char *a_addr);
extern char *inet_ntoa(struct in_addr addr);


int gethostname(char *hostname, unsigned hostlen);

/* BE specific, because of lack of UNIX passwd functions */
int getusername(char *username, unsigned userlen);
int getpassword(char *password, unsigned passlen);

#if __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETDB_H */
