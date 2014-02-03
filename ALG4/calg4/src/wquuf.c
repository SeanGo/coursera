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
 * @brief create WQUUF object and alloc memory space
 *        Initializes an empty union-find data structure with N isolated components 0 through N-1.
 * @param N is the amount number of elements
 * @return the new instans of WQUUF when succeeded othewise return NULL pointer
 */
BOOL wquuf_new(UFSET* ufset, int N)
{
	WQUUF* wquuf = 0;
	if (N > 0) {
		wquuf = malloc(sizeof(WQUUF));
		if (wquuf) {
			int i = 0;
			wquuf->length = wquuf->count = N;
			wquuf->id     = (int*)malloc(sizeof(int) * N);
			wquuf->sz     = (int*)malloc(sizeof(int) * N);
			for (; i < N; ++i)
				wquuf->id[i] = i, wquuf->sz[i] = 1;
		}
	}
	ufset->wquuf = wquuf;
	return (wquuf != NULL);
}

/**
 * @brief free WQUUF object
 * @param ufset is the instans of WQUUF
 */
void wquuf_free(UFSET* ufset)
{
	if (ufset) {
		if (ufset->wquuf->id) free(ufset->wquuf->id);
		if (ufset->wquuf->sz) free(ufset->wquuf->sz);
		free(ufset->wquuf);
		ufset->wquuf = 0;
	}
}

/**
 * Returns the number of components.
 * @param ufset is the instans of WQUUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
int wquuf_count(const UFSET* ufset)
{
	return ufset->wquuf->count;
}

/**
 * Returns the component identifier for the component containing site <tt>p</tt>.
 * @param ufset is the instans of WQUUF
 * @param p the integer representing one site
 * @return the component identifier for the component containing site <tt>p</tt>
 */
int wquuf_find(const UFSET* ufset, int p) {
	while (p != ufset->wquuf->id[p])
		p = ufset->wquuf->id[p];
	return p;
}

/**
 * Are the two sites <tt>p</tt> and <tt>q/tt> in the same component?
 * @param ufset is the instans of WQUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return <tt>true</tt> if the two sites <tt>p</tt> and <tt>q</tt> are in
 *    the same component, and <tt>false</tt> otherwise
 */
BOOL wquuf_connected(const UFSET* ufset, int p, int q) {
	return wquuf_find(ufset, p) == wquuf_find(ufset, q);
}

/**
 * Merges the component containing site<tt>p</tt> with the component
 *        containing site <tt>q</tt>.
 * @param ufset is the instans of WQUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
void wquuf_union(UFSET* ufset, int p, int q) {
	int i = wquuf_find(ufset, p);
	int j = wquuf_find(ufset, q);
	if (i != j) {
        // make smaller root point to larger one
        if (ufset->wquuf->sz[i] < ufset->wquuf->sz[j])
			ufset->wquuf->id[i] = j,
			ufset->wquuf->sz[j] += ufset->wquuf->sz[i];
        else
			ufset->wquuf->id[j] = i,
			ufset->wquuf->sz[i] += ufset->wquuf->sz[j];

        --ufset->wquuf->count;
	}
}


UF_ALG* new_wquuf_alg(int N)
{
	UF_ALG* uf_alg       = malloc(sizeof(UF_ALG));
	uf_alg->ufset        = malloc(sizeof(UFSET));
	uf_alg->UF_NEW       = wquuf_new;
	uf_alg->UF_FREE      = wquuf_free;
	uf_alg->UF_FIND      = wquuf_find;
	uf_alg->UF_COUNT     = wquuf_count;
	uf_alg->UF_CONNECTED = wquuf_connected;
	uf_alg->UF_UNION     = wquuf_union;
	
	return uf_alg;
}
