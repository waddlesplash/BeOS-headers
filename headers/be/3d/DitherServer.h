#ifndef _DITHER_SERVER_H
#define _DITHER_SERVER_H

#include <InterfaceDefs.h>

extern ulong   *B3dGetDitherTable(uchar *map ,rgb_color *color_list);
extern void    B3dReleaseDitherTable(ulong *table);

#endif















