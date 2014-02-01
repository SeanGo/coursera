#include "calg4.h"

/****************************************************************************
 *  Compilation:  make uf
 *  Execution:    ./uf ../data/input.txt
 *  Data files:   http://algs4.cs.princeton.edu/15uf/tinyUF.txt
 *                http://algs4.cs.princeton.edu/15uf/mediumUF.txt
 *                http://algs4.cs.princeton.edu/15uf/largeUF.txt
 *
 *  Weighted quick-union by rank with path compression by halving.
 *
 *  % ./uf ../data/tinyUF.txt
 *  4 3
 *  3 8
 *  6 5
 *  9 4
 *  2 1
 *  5 0
 *  7 2
 *  6 1
 *  2 components
 *
 ****************************************************************************/


/**
 *  @author Sean Go
 */

/**
 *  The <tt>UF</tt> class represents a <em>union-find data type</em>
 *  (also known as the <em>disjoint-sets data type</em>).
 *  It supports the <em>union</em> and <em>find</em> operations,
 *  along with a <em>connected</em> operation for determinig whether
 *  two sites in the same component and a <em>count</em> operation that
 *  returns the total number of components.
 *  <p>
 *  The union-find data type models connectivity among a set of <em>N</em>
 *  sites, named 0 through <em>N</em> &ndash; 1.
 *  The <em>is-connected-to</em> relation must be an 
 *  <em>equivalence relation</em>:
 *  <ul>
 *  <p><li> <em>Reflexive</em>: <em>p</em> is connected to <em>p</em>.
 *  <p><li> <em>Symmetric</em>: If <em>p</em> is connected to <em>q</em>,
 *          <em>q</em> is connected to <em>p</em>.
 *  <p><li> <em>Transitive</em>: If <em>p</em> is connected to <em>q</em>
 *          and <em>q</em> is connected to <em>r</em>, then
 *          <em>p</em> is connected to <em>r</em>.
 *  </ul>
 *  An equivalence relation partitions the sites into
 *  <em>equivalence classes</em> (or <em>components</em>). In this case,
 *  two sites are in the same component if and only if they are connected.
 *  Both sites and components are identified with integers between 0 and
 *  <em>N</em> &ndash; 1. 
 *  Initially, there are <em>N</em> components, with each site in its
 *  own component.  The <em>component identifier</em> of a component
 *  (also known as the <em>root</em>, <em>canonical element</em>, <em>leader</em>,
 *  or <em>set representative</em>) is one of the sites in the component:
 *  two sites have the same component identifier if and only if they are
 *  in the same component.
 *  <ul>
 *  <p><li><em>union</em>(<em>p</em>, <em>q</em>) adds a
 *         connection between the two sites <em>p</em> and <em>q</em>.
 *         If <em>p</em> and <em>q</em> are in different components,
 *         then it replaces
 *         these two components with a new component that is the union of
 *         the two.
 *  <p><li><em>find</em>(<em>p</em>) returns the component
 *         identifier of the component containing <em>p</em>.
 *  <p><li><em>connected</em>(<em>p</em>, <em>q</em>)
 *         returns true if both <em>p</em> and <em>q</em>
 *         are in the same component, and false otherwise.
 *  <p><li><em>count</em>() returns the number of components.
 *  </ul>
 *  The component identifier of a component can change
 *  only when the component itself changes during a call to
 *  <em>union</em>&mdash;it cannot change during a call
 *  to <em>find</em>, <em>connected</em>, or <em>count</em>.
 *  <p>
 *  This implementation uses weighted quick union by rank with path compression
 *  by halving.
 *  Initializing a data structure with <em>N</em> sites takes linear time.
 *  Afterwards, the <em>union</em>, <em>find</em>, and <em>connected</em> 
 *  operations take logarithmic time (in the worst case) and the
 *  <em>count</em> operation takes constant time.
 *  Moreover, the amortized time per <em>union</em>, <em>find</em>,
 *  and <em>connected</em> operation has inverse Ackermann complexity.
 *  For alternate implementations of the same API, see
 *  {@link QuickUnionUF}, {@link QuickFindUF}, and {@link WeightedQuickUnionUF}.
 *
 *  <p>
 *  For additional documentation, see <a href="http://algs4.cs.princeton.edu/15uf">Section 1.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick, Kevin Wayne
 */

/**
 * @brief new_uf create UF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of UF when succeeded othewise return NULL pointer
 */
UF* uf_new(int N)
{
	UF* uf = 0;
	if (N < 0) return (0);

	uf = malloc(sizeof(UF));
	if (uf) {
        uf->length = N;
        uf->id     = (int*)malloc(sizeof(int) * N);
        uf->rank   = (char*)malloc(sizeof(char) * N);
        uf->count  = 0;
	}

	return uf;
}

/**
 * @brief free_uf will free UF object
 * @param uf is the instans of UF
 */
void uf_free(UF* uf)
{
	if (uf) {
		free(uf->id);
		free(uf->rank);
	}
	free(uf);
}

/**
 * @brief generate_uf generate and initial a UF object
 * @param N is the amout number of elements
 * @return the new instans of UF when succeeded othewise return NULL pointer
 */
UF* uf_generate(int N)
{
    //create new instans
    UF* uf = uf_new(N);

    //initial value
	if (uf) {
		int i = 0;
		for (; i < N; ++i)
			uf->id[i] = i,
			uf->rank[i] = 0;
        uf->count = N;
	}
	return uf;
}


/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object, if could not find return -1
 * @return the component identifier for the component containing site <tt>p</tt>
 */
int uf_find(const UF* uf, int p) {
    //verify param
    if (!uf || p < 0 || p >= uf->length)
        return (-1);

    //find the root element
    while (p != uf->id[p]) {
        uf->id[p] = uf->id[uf->id[p]];    // path compression by halving
        p = uf->id[p];
    }
    return p;
}

/**
 * Returns the number of components.
 * @param uf is the instans of UF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
int uf_count(const UF* uf) {
    return uf->count;
}

/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
BOOL uf_connected(const UF* uf, int p, int q) {
    int ip = uf_find(uf, p);
    int iq = uf_find(uf, q);
    if (ip != -1 && iq != -1)
        return (ip == iq);
    else
        return FALSE;
}


/**
 * Merges the component containing site <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
BOOL uf_union(UF* uf, int p, int q) {
    int i = uf_find(uf, p);
    int j = uf_find(uf, q);
    if (-1 == i || -1 == j)
        return FALSE;

    if (i == j) return TRUE;

    // make root of smaller rank point to root of larger rank
    if (uf->rank[i] < uf->rank[j])
        uf->id[i] = j;
    else if (uf->rank[i] > uf->rank[j])
        uf->id[j] = i;
    else {
        uf->id[j] = i;
        uf->rank[i]++;
    }
    uf->count--;

    return TRUE;
}

