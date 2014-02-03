#include "calg4.h"

/**
 * C Interface of QuickFindUF
 * 
 * @author Sean Go
 * 
 *  The <tt>QuickFindUF</tt> class represents a union-find data structure.
 *  It supports the <em>union</em> and <em>find</em> operations, along with
 *  methods for determinig whether two objects are in the same component
 *  and the total number of components.
 *  <p>
 *  This implementation uses quick find.
 *  Initializing a data structure with <em>N</em> objects takes linear time.
 *  Afterwards, <em>find</em>, <em>connected</em>, and <em>count</em>
 *  takes constant time but <em>union</em> takes linear time.
 *  <p>
 *  For additional documentation, see <a href="http://algs4.cs.princeton.edu/15uf">Section 1.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
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
 * @brief create QFUF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of QFUF when succeeded othewise return NULL pointer
 */
BOOL qfuf_new(UFSET* ufset, int N)
{
	QFUF* qfuf = 0;
	if (N > 0) {
		qfuf = malloc(sizeof(QFUF));
		if (qfuf) {
			int i = 0;
			qfuf->length = qfuf->count = N;
			qfuf->id     = (int*)malloc(sizeof(int) * N);
			for (; i < N; ++i)
				qfuf->id[i] = i;
		}
	}
	ufset->qfuf = qfuf;
	return (qfuf != NULL);
}

/**
 * @brief free QFUF object
 * @param quf is the instans of QFUF
 */
void qfuf_free(UFSET* ufset)
{
	if (ufset) {
		if (ufset->qfuf->id) free(ufset->qfuf->id);
		free(ufset->qfuf);
		ufset->qfuf = 0;
	}
}

/**
 * Returns the number of components.
 * @param quf is the instans of QFUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
int qfuf_count(const UFSET* ufset)
{
	return ufset->qfuf->count;
}

/**
 * Returns the component identifier for the component containing site <tt>p</tt>.
 * @param quf is the instans of QFUF
 * @param p the integer representing one site
 * @return the component identifier for the component containing site <tt>p</tt>
 */
int qfuf_find(const UFSET* ufset, int p) {
	return ufset->qfuf->id[p];
}

/**
 * Are the two sites <tt>p</tt> and <tt>q/tt> in the same component?
 * @param quf is the instans of QFUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return <tt>true</tt> if the two sites <tt>p</tt> and <tt>q</tt> are in
 *    the same component, and <tt>false</tt> otherwise
 */
BOOL qfuf_connected(const UFSET* ufset, int p, int q) {
	return ufset->qfuf->id[p] == ufset->qfuf->id[q];
}

/**
 * Merges the component containing site<tt>p</tt> with the component
 *        containing site <tt>q</tt>.
 * @param quf is the instans of QFUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
void qfuf_union(UFSET* ufset, int p, int q) {
	if (!qfuf_connected(ufset, p, q)) {
		int pid = ufset->qfuf->id[p];
		int i   = 0;
		for (; i < ufset->qfuf->length; ++i)
			if (ufset->qfuf->id[i] == pid)
				ufset->qfuf->id[i] = ufset->qfuf->id[q]; 
		--ufset->qfuf->count;
	}
}


UF_ALG* new_qfuf_alg(int N)
{
	UF_ALG* uf_alg       = malloc(sizeof(UF_ALG));
	uf_alg->ufset        = malloc(sizeof(UFSET));
	uf_alg->UF_NEW       = qfuf_new;
	uf_alg->UF_FREE      = qfuf_free;
	uf_alg->UF_FIND      = qfuf_find;
	uf_alg->UF_COUNT     = qfuf_count;
	uf_alg->UF_CONNECTED = qfuf_connected;
	uf_alg->UF_UNION     = qfuf_union;
	
	return uf_alg;
}
