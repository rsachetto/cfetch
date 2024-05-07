# cfetch
Simple fetch function using curl

## Example
```c

    include "cfetch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *products[1024];
double quant[1024];
char *unit[1024];
double value[1024];

char * trim(char * s) {

    if (s == NULL) return NULL;

    int l = strlen(s);

    if (l == 0) return NULL;

    while(isspace(s[l - 1])) --l;
    while(*s && isspace(*s)) ++s, --l;

    return strndup(s, l);
}

int main(int argc, char **argv) {

    size_t len;
    char *buffer = cfetch(argv[1], &len);
    char *outfile = argv[2];

    /* memory error */
    if(buffer == NULL)
        return 1;

    FILE *f = fopen(outfile, "wb");
    
    fwrite(buffer, 1, len, f);
    fclose(f);


```
