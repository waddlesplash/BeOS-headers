/* Open a C header file with this. */
/* This is used for including /usr/include files on UNIX systems that
 * do not have C++ support in the header files.
 */
#ifdef __CPLUSPLUS__
extern "C" {
#pragma off(empty_is_void);	// () means any number of parms can be given.
#pragma off(som_bindings);	// No SOM bindings for structs found below.
#endif
