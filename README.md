# cfetch
Simple fetch function using libcurl

## Example
```c
#include "cfetch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

}
```

## Usage
```bash
$make
$./main https://www.w3.org/WAI/ER/tests/xhtml/testfiles/resources/pdf/dummy.pdf teste.pdf
```
