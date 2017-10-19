#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "phonebook.h"
#include <stdlib.h>
#include "names.h"

#define BUFFER_SIZE 100000

typedef struct Data {
    FILE * file;
    phonebook_t * book;
    human_t * human;
    char str[256];
} Data_t;

void init(phonebook_t * book) {
    book->size = 0;
    book->capacity = 1;
    book->humans = (human_t *)malloc(sizeof(human_t));
}

void push_back_human(phonebook_t * book, const char * line) {
    char * str = malloc(sizeof(line));
    strcpy(str, line);
    char * pch = strtok(str, " \n");
    human_t * human = (human_t *)malloc(sizeof(human_t));
    strcpy(human->name, pch);
    pch = strtok(NULL, " \n");
    strcpy(human->middle_name, pch);
    pch = strtok(NULL, " \n");
    strcpy(human->family_name, pch);
    for (int i = 0; i < 10; i++)
        strcpy(human->phones[i], "");
    if (book->size == book->capacity) {
        human_t * temp = realloc(book->humans, book->capacity * 2 * sizeof(human_t));
	if (temp == NULL) {
            free(str);
	    free(human);
	    free(book->humans);
	    exit(1);
	}
        book->humans = temp;
	book->capacity *= 2;
    }
    book->humans[book->size++] = *human;
    free(str);
    free(human);
    return;
}

void push_back_phone(human_t * human, char * phone) {
    int ptr = 0;
    while (strcmp(human->phones[ptr], ""))
        ptr++;
    strcpy(human->phones[ptr], phone);
    return;
}

void start_element(void *data, const char *element, const char **attribute) {
    if (!strcmp(element, "phonebook"))
        return;
    if (!strcmp(element, "human")) {
        push_back_human(((Data_t *)data)->book, attribute[1]);
	((Data_t *)data)->human = ((Data_t *)data)->book->humans + ((Data_t *)data)->book->size - 1;
	return;
    }
    if (!strcmp(element, "phone"))
        return;
    return;
}

void end_element(void *data, const char *element) {
    if (!strcmp(element, "phonebook"))
        return;
    if (!strcmp(element, "human"))
        return;
    if (!strcmp(element, "phone")) {
        char * pch;
        pch = strtok(((Data_t *)data)->str, " \n");
        while (pch != NULL) {
	        push_back_phone(((Data_t *)data)->human, pch);
	        pch = strtok(NULL, " \n");
        }
        strcpy(((Data_t *)data)->str, "");
    }
}

void handle_data(void *data, const char *content, int length) {
    strncat(((Data_t *)data)->str, content, length);
}

int parse_xml(Data_t * data, char *buff, size_t buff_size) {
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, (void *)data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, data->file);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));

            XML_ParserFree(parser);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);

    return 0;
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE * file = fopen(filename, "r");
    if (!file)
        return 1;
    Data_t data;
    data.file = file, data.book = book, data.human = NULL, strcpy(data.str, "");
    int result;
    char buffer[BUFFER_SIZE];
    result = parse_xml(&data, buffer, BUFFER_SIZE);
    fclose(file);
    return result;
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE * file = fopen(filename, "w");
    if (file == NULL)
        return 1;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<phonebook>\n");
    for (int i = 0; i < book->size; i++) {
        fprintf(file, "    <human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
	for (int j = 0; strcmp(book->humans[i].phones[j], "") && j < 10; j++)
            fprintf(file, "        <phone>%s</phone>\n", book->humans[i].phones[j]);
	fprintf(file, "    </human>\n");
    }
    fprintf(file, "</phonebook>");
    fclose(file);
    return 0;
}

void gen_phonebook(phonebook_t * book, size_t size) {
    for (int i = 0; i < size; i++) {
        strcpy(book->humans[i].name, kNames[rand() % NAMES_CNT]);
        strcpy(book->humans[i].middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(book->humans[i].family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
	for (int j = 0; j < 10; j++) {
            int len = rand() % 11 + 10;
	    strcpy(book->humans[i].phones[j], "");
	    for (int k = 0; k < len; k++)
                book->humans[i].phones[j][k] = (k ? 0 : 1) + rand() % (k ? 10 : 9) + '0';
	    book->humans[i].phones[j][len] = '\0';
	}
    }
}

void print_phonebook(phonebook_t * book) {
    printf("%d\n", book->size);
    for (int i = 0; i < book->size; i++) {
        printf("name: %s\nmiddle name: %s\nfamily name: %s\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
	for (int j = 0; strcmp(book->humans[i].phones[j], "") && j < 10; j++)
            printf("phone: %s\n", book->humans[i].phones[j]);
	if (i + 1 != book->size)
            printf("\n");
    }
}
