#include <itimer.h>
#include <sys/mman.h>
#include <libgen.h>
#include <getpass.h>
#include <rlimit.h>
#include <io.h>

#ifndef SA_RESETHAND
#define SA_RESETHAND 0
#endif

#ifndef SA_RESTART
#define SA_RESTART 0
#endif

