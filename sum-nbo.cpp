#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "syntax : %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }
 
    uint32_t sum = 0;
 
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            fprintf(stderr, "Error: cannot open file: %s\n", argv[i]);
            return 1;
        }
 
        uint32_t net_value;
        if (fread(&net_value, sizeof(net_value), 1, fp) != 1) {
            fprintf(stderr, "Error: file too small: %s\n", argv[i]);
            fclose(fp);
            return 1;
        }
        fclose(fp);
 
        uint32_t value = ntohl(net_value);
        sum += value;

         if (i > 1) {
        printf(" + ");
         }
        printf("%u(0x%08x)", value, value);
    }
 
    printf(" = %u(0x%08x)\n", sum, sum);
    return 0;
}
 
