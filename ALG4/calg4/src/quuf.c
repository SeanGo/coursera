#include "calg4.h"

/**
 * C Interface of QuickUnionUF
 * 
 * @author Sean Go
 * 
 *  The <tt>QuickUnionUF</tt> class represents a union-find data structure.
 *  It supports the <em>union</em> and <em>find</em> operations, along with
 *  methods for determinig whether two objects are in the same component
 *  and the total number of components.
 *  <p>
 *  This implementation uses quick union.
 *  Initializing a data structure with <em>N</em> objects takes linear time.
 *  Afterwards, <em>union</em>, <em>find</em>, and <em>connected</em> take
 *  time linear time (in the worst case) and <em>count</em> takes constant
 *  time.
 *  <p>
 *  For additional documentation, see <a href="http://algs4.cs.princeton.edu/15uf">Section 1.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *     
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */


/**
 * @brief create QUUF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of QUUF when succeeded othewise return NULL pointer
 */
BOOL quuf_new(UFSET* ufset, int N)
{
	QUUF* quuf = 0;
	if (N > 0) {
		quuf = malloc(sizeof(QUUF));
		if (quuf) {
			int i = 0;
			quuf->length = quuf->count = N;
			quuf->id     = (int*)malloc(sizeof(int) * N);
			for (; i < N; ++i)
				quuf->id[i] = i;
		}
	}
	ufset->quuf = quuf;
	return (quuf != NULL);
}

/**
 * @brief free QUUF object
 * @param quf is the instans of QUUF
 */
void quuf_free(UFSET* ufset)
{
	if (ufset) {
		if (ufset->quuf->id) free(ufset->quuf->id);
		free(ufset->quuf);
		ufset->quuf = 0;
	}
}

/**
 * Returns the number of components.
 * @param quf is the instans of QUUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
int quuf_count(const UFSET* ufset)
{
	return ufset->quuf->count;
}

/**
 * Returns the component identifier for the component containing site <tt>p</tt>.
 * @param quf is the instans of QUUF
 * @param p the integer representing one site
 * @return the component identifier for the component containing site <tt>p</tt>
 */
int quuf_find(const UFSET* ufset, int p) {
	while (p != ufset->quuf->id[p])
		p = ufset->quuf->id[p];
	return p;
}

/**
 * Are the two sites <tt>p</tt> and <tt>q/tt> in the same component?
 * @param quf is the instans of QUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return <tt>true</tt> if the two sites <tt>p</tt> and <tt>q</tt> are in
 *    the same component, and <tt>false</tt> otherwise
 */
BOOL quuf_connected(const UFSET* ufset, int p, int q) {
	return quuf_find(ufset, p) == quuf_find(ufset, q);
}

/**
 * Merges the component containing site<tt>p</tt> with the component
 *        containing site <tt>q</tt>.
 * @param quf is the instans of QUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
void quuf_union(UFSET* ufset, int p, int q) {
	int i = quuf_find(ufset, p);
	int j = quuf_find(ufset, q);
	if (i != j) {
		ufset->quuf->id[i] = j; 
		--ufset->quuf->count;
	}
}


UF_ALG* new_quuf_alg(int N)
{
	UF_ALG* uf_alg       = malloc(sizeof(UF_ALG));
	uf_alg->ufset        = malloc(sizeof(UFSET));
	uf_alg->UF_NEW       = quuf_new;
	uf_alg->UF_FREE      = quuf_free;
	uf_alg->UF_FIND      = quuf_find;
	uf_alg->UF_COUNT     = quuf_count;
	uf_alg->UF_CONNECTED = quuf_connected;
	uf_alg->UF_UNION     = quuf_union;
	
	return uf_alg;
}
