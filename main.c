/*
Copyright (c) 2025 London Sheard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 * /

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(char* filename, char* outputname) {
    FILE* input = fopen(filename, "r");
    FILE* p7zcon = fopen("/usr/lib/7zip/7zCon.sfx", "r");
    if (!input) {
        fprintf(stderr, "Error. Could not open file: %s\nFile not found!\n", filename);
        return NULL;
    }
    if (!p7zcon) {
        fprintf(stderr, "Error. Could not find p7zip sfx config.");
    }
    fclose(input);

    const char* fmt = "cat /usr/lib/7zip/7zCon.sfx '%s' > '%s'";

    size_t needed = snprintf(NULL, 0, fmt, filename, outputname);
    if (needed < 0) {
        fprintf(stderr, "Error. Input too small.\n");
        return NULL;
    }

    char* command = malloc(needed + 1);
    if (!command) {
        fprintf(stderr, "Error. Could not allocate buffer.\n");
        return NULL;
    }

    size_t written = snprintf(command, needed+1, fmt, filename, outputname);
    if (written < 0 || written > needed) {
        fprintf(stderr, "Error. Buffer was either too small or large than expected.\n");
        free(command);
        return NULL;
    }

    return command;

}

int main(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Error. Expected input file and output name.\n--help for help\n");
        return 1;
    } if (strcmp("--help", argv[1]) == 0) {
        fprintf(stdout, "Usage:\n7z2sfx {input file} {output name}\n");
        return 0;
    }
    char* input_file = argv[1];
    char* output_name = argv[2];
    char* command = convert(input_file, output_name);

    system(command);

    free(command);

    return 0;

}
