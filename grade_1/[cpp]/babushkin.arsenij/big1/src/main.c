#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"

int main(int argc, char **argv) {
    FILE *in, *out;
    assert(in = fopen(argv[2], "rb"));
    assert(out = fopen(argv[3], "wb"));

    int l, d, w, h, r, u;
    assert(sscanf(argv[4], "%d", &l));
    assert(sscanf(argv[5], "%d", &d));
    assert(sscanf(argv[6], "%d", &w));
    assert(sscanf(argv[7], "%d", &h));
    r = l + w;
    u = d + h;

    BMPIMAGE input;
    assert(!load_bmp(&input, in));

    BMPIMAGE cropped;
    assert(!crop_bmp(&cropped, &input, l, r, d, u));

    BMPIMAGE turned;
    assert(!turn_bmp(&turned, &cropped));
    save_bmp(&turned, out);

    delete_bmp(&input);
    delete_bmp(&cropped);
    delete_bmp(&turned);

    fclose(in);
    fclose(out);
    return 0;
}
