#ifndef __str_h_include__
#define __str_h_include__

/**
 * head files for utilities functions for string in C
 * @author Sean Go
 */


/**
 ltrim remove space ont the left of s

 ltrim returns a pointer that's not suitable for passing to free. 
 If you use it (or, of course, trim), be sure you hold onto the 
 original pointer -- especially don't try something like s = trim(s);
  without having s stored elsewhere first.
*/
extern char *ltrim(char *s);

/**
 rtrim remove space on the right of s
*/
extern char* rtrim(char *s);


/**
 trim removes space on the left and right of s


 trim returns a pointer that's not suitable for passing to free. 
 If you use it (or, of course, trim), be sure you hold onto the 
 original pointer -- especially don't try something like s = trim(s);
  without having s stored elsewhere first.

*/
extern char *trim(char *s);

#ifndef _HAVE_STRLCPY_
/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t siz);
#endif //_HAVE_STRLCPY_

#ifndef _HAVE_STRLCAT_
/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t strlcat(char *dst, const char *src, size_t siz);

#endif //_HAVE_STRLCAT_


#endif //__str_h_include__
