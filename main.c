#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

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

char** generate_donut(char* contents, int radius, int inner_radius, size_t* nlines)
{
    int width = radius * 4;
    int height = radius * 2 + 1;

    char** lines = malloc(sizeof(char*) * height);
    *nlines = height;

    size_t curr_idx = 0;

    for (int y = 0; y < height; ++y)
    {
        lines[y] = malloc(sizeof(char) * (width + 1));
        memset(lines[y], ' ', sizeof(char) * width);
        lines[y][width] = '\0';

        for (int x = 0; x < width; ++x)
        {
            int dx = ((width / 2) - x) / 2;
            int dy = (height / 2) - y;

            int dist = sqrt(dx * dx + dy * dy);

            if (dist < radius && dist > inner_radius)
            {
                if (curr_idx + 1 < strlen(contents))
                    lines[y][x] = contents[curr_idx++];
            }
        }
    }

    return lines;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "No file specified\n");
        return -1;
    }

    char* contents = read_file(argv[1]);

    size_t nlines;
    char** lines = generate_donut(contents, 20, 5, &nlines);

    for (size_t i = 0; i < nlines; ++i)
    {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }

    free(contents);
    free(lines);

    return 0;
}

