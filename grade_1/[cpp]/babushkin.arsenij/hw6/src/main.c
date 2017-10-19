#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phonebook.h"
#include <time.h>

int comp(const void * p1, const void * p2) {
    return strcmp(((human_t *)p1)->family_name, ((human_t *)p2)->family_name);
}

int main(int argc, char **argv) {
    phonebook_t book;
    init(&book);
    if (load_phonebook_xml(argv[1], &book))
        return 1;
    qsort(book.humans, book.size, sizeof(human_t), comp);
    print_phonebook(&book);
    srand(time(NULL));
    gen_phonebook(&book, book.capacity);
    if (save_phonebook_xml(argv[2], &book))
        return 1;
    free(book.humans);
    return 0;
}
