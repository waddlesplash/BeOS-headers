/*
 * socket.h
 * Copyright (c) 1995-96 Be, Inc.	All Rights Reserved 
 *
 * BSD socket-like interface
 *
 * Do not expect total BSD compatibility from this interface!
 */
#ifndef _SOCKET_H
#define _SOCKET_H

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

#define AF_INET 1

#define SOL_SOCKET 1

#define SO_DEBUG 1
#define SO_REUSEADDR 2

#define MSG_OOB 0x1

#define SOCK_DGRAM 1
#define SOCK_STREAM 2

#define IPPROTO_UDP 1
#define IPPROTO_TCP 2
#define IPPROTO_ICMP 3

/* 
 * Be extension
 */
#define B_UDP_MAX_SIZE (8192 + 64) /* enough for 8K data plus header */

struct sockaddr {
	unsigned short sa_family;
	char sa_data[10];
};

struct in_addr {
	unsigned long s_addr;
};

struct sockaddr_in {
	unsigned short sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	char sin_zero[4];
};

struct timeval {
	unsigned long tv_sec;
	unsigned long tv_usec;
};

/*
 * If you depend on timezones, you are in trouble because we don't
 * support them!  Everything is currently in local time and there is
 * no concept of GMT.
 */
struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

#define ntohs(x) x
#define htons(x) x
#define htonl(x) x
#define ntohl(x) x

typedef struct fd_set {
	unsigned long mask;
} fd_set;

#define FD_ZERO(setp) (setp)->mask = 0
#define FD_SET(fd, setp) ((setp)->mask |= (1 << (fd)))
#define FD_CLR(fd, setp) ((setp)->mask &= ~(1 << (fd)))
#define FD_ISSET(fd, setp) ((setp)->mask & (1 << (fd)))


int socket(int family, int type, int proto);
int bind(int fd, struct sockaddr *addr, int size);
int getsockname(int fd, struct sockaddr *addr, int *size);
int recvfrom(int fd, char *buf, int size, int flags,
			 struct sockaddr *from, int *fromlen);
int sendto(int fd, const char *buf, int size, int flags,
		   struct sockaddr *to, int tolen);

int send(int fd, const char *buf, int size, int flags);
int recv(int fd, char *buf, int size, int flags);


int connect(int fd, struct sockaddr *addr, int size);
int accept(int fd, struct sockaddr *addr, int *size);


int listen(int fd, int backlog);
int closesocket(int fd);
int setsockopt(int sd, int prot, int opt, char *data, unsigned datasize);

int select(int nbits, 
		   struct fd_set *rbits, 
		   struct fd_set *wbits, 
		   struct fd_set *ebits, 
		   struct timeval *timeout);


#if __cplusplus
}
#endif /* __cplusplus */

#endif /* _SOCKET_H */
