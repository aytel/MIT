#include <expat.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100000

void start_element(void *data, const char *element, const char **attribute) {
    printf("start_element %s", element);
    int i = 0;
    for (i = 0; attribute[i]; i += 2) {
        printf(" %s= %s ", attribute[i], attribute[i + 1]);
    }
    printf("\n");
}

void end_element(void *data, const char *element) {
    char * pch;
    pch = strtok((char *)data, " \n");
    while (pch != NULL) {
	    printf("%s ", pch);
	    pch = strtok(NULL, " \n");
    }
    printf("\n");
    strcpy((char *)data, "");
    printf("end_element %s\n", element);
}

void handle_data(void *data, const char *content, int length) {
    strncat((char *)data, content, length);
    //printf("%s\n", content);
}

int parse_xml(char *buff, size_t buff_size) {
    FILE *fp;
    fp = fopen("pbook.xml", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    char str[256];
    strcpy(str, "");
    XML_SetUserData(parser, (void *)str);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));

            XML_ParserFree(parser);
            fclose(fp);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}

int main(int argc, char **argv) {
    int result;
    char buffer[BUFFER_SIZE];
    result = parse_xml(buffer, BUFFER_SIZE);
    printf("Result is %i\n", result);
    return 0;
}
