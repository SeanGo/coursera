#include "calg4.h"

/**
 * test all 4 kind of UF algorithm
 * @author Sean Go
 */

static char datapath[MAX_PATH];
static char* uf_data_file[] = {"tinyUF.txt", "mediumUF.txt", "largeUF.txt"};

/**
 * Read all data from file
 * @param filepath is the file
 * @param N is a pointer will return the size of UFset
 * @param data_len is the amount number of testing data
 * return the data array
 */
static int* read_data(const char* filepath, int* N, size_t *data_len)
{
    FILE* fp = fopen(filepath, "rt");
	int* node = 0;  //all data
	char tmp[1024];
    *data_len = 0;
	
	//first line is the number of elements
	if (fp && fgets(tmp, 1024, fp))
		*N = atoi(tmp);
	
	//N must be large than zero
	if (fp && *N > 0) {	
		//get the lines number
		while(fgets(tmp, 1024, fp))
			++(*data_len);
		
		*data_len *= 2;
		//return to the begin of file
		fseek(fp, SEEK_SET, 0);
		//jump first line
		if (fgets(tmp, 1024, fp)) {
			//read all data into memory	
			int i = 0;
			node = malloc(sizeof(int) * *data_len);
			while(fgets(tmp, 1024, fp)) {
				sscanf(tmp, "%d%d", node + i, node + i + 1);
				i += 2;
			}
			printf("has %d nodes, %u datas\n", *N, *data_len);
		}
	}
	
	if (fp)
		fclose(fp);
	
	return node;
}

static int test_one_uf_file(const char* filepath, UF_ALG* uf_alg)
{
    int N = 0, data_len = 0;
	int* node = read_data(filepath, &N, &data_len);

	if (node && uf_alg->UF_NEW(uf_alg->ufset, N)) {
		struct timeval tv1, tv2;
		struct timezone tz;	
		int i = 0;

		gettimeofday(&tv1, &tz);
		for (; i < data_len; i += 2) {
			if (!uf_alg->UF_CONNECTED(uf_alg->ufset,  node[i], node[i + 1]))
				uf_alg->UF_UNION(uf_alg->ufset, node[i], node[i + 1]);
			//printf("%d\n", ++i);
		}
		gettimeofday(&tv2, &tz);
		printf("%d Components, time usage %ld ms\n",
				uf_alg->UF_COUNT(uf_alg->ufset),
				(tv2.tv_sec * 1000 + tv2.tv_usec / 1000) - (tv1.tv_sec * 1000 + tv1.tv_usec / 1000));
    }
    
    //release memrory
    uf_alg->UF_FREE(uf_alg->ufset);
	if (node) free(node);
	
    return (0);
}

static void test_uf_files(UF_ALG* uf_alg, int n_files)
{
    char filepath[MAX_PATH];
    int i;

    for (i = 0; i < n_files; ++i) {
		printf("File %s ", uf_data_file[i]);
        snprintf(filepath, MAX_PATH, "%s/%s", datapath, uf_data_file[i]);
		test_one_uf_file(filepath, uf_alg);
    }
    
    if (n_files < 3) {
		printf("I don not want to try %s, it will take very long time\n", uf_data_file[2]);
	}
}

static int test_uf(void)
{
	printf("test for uf\n");
	UF_ALG* uf_alg = new_uf_alg();
	test_uf_files(uf_alg, 3);
	free_uf_alg(uf_alg);

	printf("\ntest for qfuf\n");
	uf_alg = new_qfuf_alg();
	//i do not want run 3rd file for qfuf
	test_uf_files(uf_alg, 2);
	free_uf_alg(uf_alg);

	printf("\ntest for quuf\n");
	uf_alg = new_quuf_alg();
	//i do not want run 3rd file for quuf
	test_uf_files(uf_alg, 2);
	free_uf_alg(uf_alg);

	printf("\ntest for wquuf\n");
	uf_alg = new_wquuf_alg();
	test_uf_files(uf_alg, 3);
	free_uf_alg(uf_alg);

	return (0);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: test_uf <data path>\n");
        return (0);
    }

    strlcpy(datapath, argv[1], MAX_PATH);
    test_uf();

    return (0);
}


