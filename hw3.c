#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void replace_all(const char *pattern, const char *text, const char *replacement) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;

    size_t buffer_size = strlen(text) + 1;
    char *result = malloc(buffer_size);
    if (!result) {
        perror("malloc");
        regfree(&regex);
        return;
    }
    result[0] = '\0';

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t len_before = match.rm_so;
        size_t len_after = strlen(p + match.rm_eo);

        buffer_size += len_before + strlen(replacement) + 1;
        result = realloc(result, buffer_size);
        if (!result) {
            perror("realloc");
            regfree(&regex);
            return;
        }

        strncat(result, p, len_before);
        strcat(result, replacement);
        p += match.rm_eo;
    }

    strcat(result, p);
    printf("%s\n", result);
    free(result);
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regex> <text> <replacement>\n", argv[0]);
        return 1;
    }

    replace_all(argv[1], argv[2], argv[3]);
    return 0;
}
