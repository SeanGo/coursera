#include "calg4.h"

static char datapath[MAX_PATH];

int test_one_uf_file(const char* filepath)
{
    FILE* fp = fopen(filepath, "rt");
    char tmp[1024];
    //first line is the number of elements
    UF* uf = 0;

    if (fp && fgets(tmp, 1024, fp)) {
        int N = atoi(tmp);
        uf = uf_generate(N);
    }

    if (uf && fp) {
        int i = 0;
        while(fgets(tmp, 1024, fp)) {
            ++i;
            char* buf = trim(tmp);
            int p, q;
            sscanf(buf, "%d%d", &p, &q);
            if (!uf_connected(uf,  p, q))
            {
                uf_union(uf, p, q);
                //printf("%d + %d\n", p, q);
            }
            //printf("%d |", i);
        }
    }
    if (uf)
       uf_free(uf);

    if (fp)
        fclose(fp);

    printf("%d components\n", uf_count(uf));
    return (0);
}

int test_uf(void)
{
    char* file[] = {
        "tinyUF.txt",
        "mediumUF.txt",
        "largeUF.txt",
    };
    int n = 3, i;
    char filepath[MAX_PATH];

    for (i = 0; i < n; ++i) {
        snprintf(filepath, MAX_PATH, "%s/%s", datapath, file[i]);
        printf("%s:\n", file[i]);
        test_one_uf_file(filepath);
    }


    return (0);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: test <data path>\n");
        return (0);
    }

    strlcpy(datapath, argv[1], MAX_PATH);
    test_uf();

    return (0);
}


