#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"

int main(int argc, char **argv) {
    if (!strcmp(argv[1], "crop-rotate")) {
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
    }
    if (!strcmp(argv[1], "insert")) {
        FILE *in, *out, *key, *msg;
        assert(in = fopen(argv[2], "rb"));
        assert(out = fopen(argv[3], "wb"));
        assert(key = fopen(argv[4], "r"));
        assert(msg = fopen(argv[5], "r"));

        BMPIMAGE input;
        assert(!load_bmp(&input, in));

        BMPIMAGE output;
        assert(!insert_msg(&output, &input, key, msg));
        save_bmp(&output, out);

        delete_bmp(&input);
        delete_bmp(&output);

        fclose(in);
        fclose(out);
        fclose(key);
        fclose(msg);
    }
    if (!strcmp(argv[1], "extract")) {
        FILE *in, *key, *msg;
        assert(in = fopen(argv[2], "rb"));
        assert(key = fopen(argv[3], "r"));
        assert(msg = fopen(argv[4], "w"));

        BMPIMAGE input;
        assert(!load_bmp(&input, in));

        extract_msg(&input, key, msg);

        delete_bmp(&input);

        fclose(in);
        fclose(key);
        fclose(msg);
    }
    return 0;
}