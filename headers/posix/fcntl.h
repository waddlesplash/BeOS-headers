/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

#ifndef _FCNTL_H
#define _FCNTL_H

#ifndef __ansi_parms__								/*MW-jcm 971114 */
#include <ansi_parms.h>								/*MW-jcm 971114 */
#endif												/*MW-jcm 971114 */

#if __dest_os == __mac_os
#	include <fcntl.mac.h>
#elif __dest_os == __win32_os
#	include <fcntl.win32.h>
#elif __dest_os == __powertv_os
#	include <fcntl.powertv.h>
#elif __dest_os == __be_os                         /* mm 970708 */
#	include <fcntl.be.h>                           /* mm 970708 */
#endif
/*     Change record
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mm 970708  Inserted Be changes
 * jcm 971114	wrapped the #include <ansi_parms.h>
 * jcm 971114	killed the macintosh defined && !defined (_dest_os) since it is in ansi_parms.h
 */

#endif /* _FCNTL_H */
