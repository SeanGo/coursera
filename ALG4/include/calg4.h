#ifndef __calg4_h_include__
#define __calg4_h_include__

#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>

#ifndef BOOL
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif //BOOL

#ifndef MAX_PATH
#define MAX_PATH 260
#endif //MAX_PATH

#define MALLOC(type, n) ((type*)malloc((n) * sizeof(type)))

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


/**
  struct UF for Union and Find
  */
typedef struct UF {
    int  length; ///number of entires
    int   count; ///number of components
    int*     id; ///elements
    char*  rank; ///ranks
} UF;


/**
 * @brief new_uf create UF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of UF when succeeded othewise return NULL pointer
 */
extern UF* uf_new(int N);
/**
 * @brief free_uf will free UF object
 * @param uf is the instans of UF
 */
extern void uf_free(UF* uf);

/**
 * @brief generate_uf generate and initial a UF object
 * @param N is the amout number of elements
 * @return the new instans of UF when succeeded othewise return NULL pointer
 */
extern UF* uf_generate(int N);
/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object, if could not find return -1
 * @return the component identifier for the component containing site <tt>p</tt>
 */
extern int uf_find(const UF* uf, int p);
/**
 * Returns the number of components.
 * @param uf is the instans of UF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
extern int uf_count(const UF* uf);
/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
extern BOOL uf_connected(const UF* uf, int p, int q);
/**
 * Merges the component containing site <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if succeeded; false otherwise
 */
extern BOOL uf_union(UF* uf, int p, int q);

#endif //__calg4_h_include__
