#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char* path)
{
    FILE* fp = fopen(path, "r");

    if (!fp)
    {
        fprintf(stderr, "File '%s' does not exist\n", path);
        return 0;
    }

    char* contents = malloc(sizeof(char));
    contents[0] = '\0';

    char* line = 0;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        unsigned long prev_len = strlen(contents);
        contents = realloc(contents, (strlen(contents) + read) * sizeof(char));

        memcpy(&contents[prev_len], line, (read - 1) * sizeof(char));
        contents[prev_len + read - 1] = '\0';
    }

    free(line);
    fclose(fp);

    return contents;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "No file specified\n");
        return -1;
    }

    char* contents = read_file(argv[1]);

    return 0;
}

