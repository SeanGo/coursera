#ifndef __uf_set_h_include__
#define __uf_set_h_include__

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
  struct QUUF for Quick Find UNION-FIND
  */
typedef struct QFUF {
    int  length; ///number of entires
    int   count; ///number of components
    int*     id; ///elements
} QFUF;
/**
  struct QUUF for Quick Find UNION-FIND, its same with QFUF
  */
typedef struct QUUF {
    int  length; ///number of entires
    int   count; ///number of components
    int*     id; ///elements
} QUUF;

/**
 * struct WQUUF for WeightedQuickUnionUF
 */
typedef struct WQUUF {
    int  length; ///number of entires
    int   count; ///number of components
    int*     id; ///elements, id[i] = parent of i
    int*     sz; ///sz[i] = number of objects in subtree rooted at i   
}WQUUF;

/**
 * struct UFSET is union type of UF, QFUF and QUUF
 */
typedef struct  {
	union {
		UF*       uf;
		QFUF*   qfuf;
		QUUF*   quuf;
		WQUUF* wquuf;
	};
} UFSET;

/**
 * define the UF ALGORITHM object and the operatoion functions
 */
typedef struct UF_ALG {
	UFSET*                 ufset;
	BOOL   (*UF_NEW  )     (      UFSET* ufset, int N);
	void   (*UF_FREE )     (      UFSET* ufset);
	int    (*UF_FIND )     (const UFSET* ufset, int p);
	int    (*UF_COUNT)     (const UFSET* ufset);
	BOOL   (*UF_CONNECTED) (const UFSET* ufset, int p, int q);
	void   (*UF_UNION)     (      UFSET* ufset, int p, int q);
} UF_ALG;


/*--------Functions for UF --------------------------------------*/
/**
 * @brief create UF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of UF when succeeded othewise return NULL pointer
 */
extern BOOL ufset_new(UFSET* ufset, int N);
/**
 * @brief free UF object
 * @param ufset is the instans of UF
 */
extern void ufset_free(UFSET* ufset);

/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object, if could not find return -1
 * @return the component identifier for the component containing site <tt>p</tt>
 */
extern int ufset_find(const UFSET* ufset, int p);
/**
 * Returns the number of components.
 * @param ufset is the instans of UF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
extern int ufset_count(const UFSET* ufset);
/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
extern BOOL ufset_connected(const UFSET* ufset, int p, int q);
/**
 * Merges the component containing site <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if succeeded; false otherwise
 */
extern void ufset_union(UFSET* ufset, int p, int q);



/*--------Functions for QFUF --------------------------------------*/
/**
 * @brief create QFUF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of QFUF when succeeded othewise return NULL pointer
 */
extern BOOL qfuf_new(UFSET* ufset, int N);
/**
 * @brief free QFUF object
 * @param quf is the instans of QFUF
 */
extern void qfuf_free(UFSET* ufset);

/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object
 * @return the component identifier for the component containing site <tt>p</tt>
 */
extern int qfuf_find(const UFSET* ufset, int p);
/**
 * Returns the number of components.
 * @param quf is the instans of QFUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
extern int qfuf_count(const UFSET* ufset);
/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param quf is the instans of QFUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
extern BOOL qfuf_connected(const UFSET* ufset, int p, int q);
/**
 * Merges the component containing site <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param quf is the instans of QFUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
extern void qfuf_union(UFSET* ufset, int p, int q);


/*--------Functions for QUUF --------------------------------------*/
/**
 * @brief create QUUF object and alloc memory space
 * @param N is the amount number of elements
 * @return the new instans of QUUF when succeeded othewise return NULL pointer
 */
extern BOOL quuf_new(UFSET* ufset, int N);
/**
 * @brief free QUUF object
 * @param quf is the instans of QUUF
 */
extern void quuf_free(UFSET* ufset);

/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object
 * @return the component identifier for the component containing site <tt>p</tt>
 */
extern int quuf_find(const UFSET* ufset, int p);
/**
 * Returns the number of components.
 * @param quf is the instans of QUUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
extern int quuf_count(const UFSET* ufset);
/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param quf is the instans of QUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
extern BOOL quuf_connected(const UFSET* ufset, int p, int q);
/**
 * Merges the component containing siuf_alg->ufset = te <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param quf is the instans of QUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
extern void quuf_union(UFSET* ufset, int p, int q);




/*--------Functions for WQUUF --------------------------------------*/
/**
 * @brief create WQUUF object and alloc memory space
 *        Initializes an empty union-find data structure with N isolated components 0 through N-1.
 * @param N is the amount number of elements
 * @return the new instans of WQUUF when succeeded othewise return NULL pointer
 */
extern BOOL wquuf_new(UFSET* ufset, int N);
/**
 * @brief free WQUUF object
 * @param quf is the instans of WQUUF
 */
extern void wquuf_free(UFSET* ufset);

/**
 * @brief Returns the component identifier for the component containing site <tt>p</tt>.
 * @param p the integer representing one object
 * @return the component identifier for the component containing site <tt>p</tt>
 */
extern int wquuf_find(const UFSET* ufset, int p);
/**
 * Returns the number of components.
 * @param quf is the instans of WQUUF object
 * @return the number of components (between <tt>1</tt> and <tt>N</tt>)
 */
extern int wquuf_count(const UFSET* ufset);
/**
 * Are the two sites <tt>p</tt> and <tt>q</tt> in the same component?
 * @param quf is the instans of WQUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 * @return true if the two sites <tt>p</tt> and <tt>q</tt> are in the same component; false otherwise
 */
extern BOOL wquuf_connected(const UFSET* ufset, int p, int q);
/**
 * Merges the component containing siuf_alg->ufset = te <tt>p</tt> with the
 * the component containing site <tt>q</tt>.
 * @param quf is the instans of WQUUF
 * @param p the integer representing one site
 * @param q the integer representing the other site
 */
extern void wquuf_union(UFSET* ufset, int p, int q);


/**
 * generate a UF_ALG for uf algrithm
 * @param N is the size of uf
 */
extern UF_ALG* new_uf_alg  ();
/**
 * generate a UF_ALG for qfuf algrithm
 * @param N is the size of qfuf
 */
extern UF_ALG* new_qfuf_alg();
/**
 * generate a UF_ALG for quuf algrithm
 * @param N is the size of quuf
 */
extern UF_ALG* new_quuf_alg();

/**
 * generate a UF_ALG for wquuf algrithm
 * @param N is the size of wquuf
 */
extern UF_ALG* new_wquuf_alg();

/**
 * release the UF_ALG object
 * @param uf_alg is the instance of UF_ALG
 */
extern void free_uf_alg(UF_ALG* uf_alg);


#endif //__uf_set_h_include__
