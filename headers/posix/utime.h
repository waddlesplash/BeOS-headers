/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

#if macintosh && !defined(__dest_os)               /*MW-mm 960927a*/
  #define __dest_os __mac_os                       /*MW-mm 960927a*/
#endif                                             /*MW-mm 960927a*/

#if __dest_os == __mac_os

#include <utime.mac.h>

#elif __dest_os == __win32_os

#include <utime.win32.h>

#elif __dest_os == __powertv_os

#include <utime.powertv.h>

#elif __dest_os == __be_os               /* mm 970708 */

#include <utime.be.h>                    /* mm 970708 */

#endif
/*     Change record
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mm 970708  Inserted Be changes
 */
