#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Loads the entire content of a file into a dynamically allocated string.
 * The Maximum file size: 2GB
 *
 * [in-out]
 * load_string_from_file(path to the file) -> pointer to the string
 *
 * [return value]
 * NULL: There are some shitty things going on.
 * Not NULL: Have a nice day. Just remember to free later.
 */
char* load_string_from_file(const char* path)
{
	if (!path) {
		fprintf(stderr, "Path is NULL\n");
		return NULL;
	}

	FILE *file = fopen(path, "r");
	if (!file) {
		fprintf(stderr, "Failed to open file: [%s]\n", path);
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0) {
		fprintf(stderr, "Failed to seek end of file: [%s]\n", path);
		fclose(file);
		return NULL;
	}

	long length = ftell(file);
	if (length < 0) {
		fprintf(stderr, "Failed to determine the length of the file: [%s]\n", path);
		fclose(file);
		return NULL;
	}
	rewind(file);

	char* buffer = malloc(length + 1);
	if (!buffer) {
		fprintf(stderr, "Failed to allocate memory for ShaderSrc: [%s]\n", path);
		fclose(file);
		return NULL;
	}

	size_t read_length = fread(buffer, 1, length, file);
	if (read_length != length) {
		fprintf(stderr, "Failed to read the entire file: [%s]\n", path);
		if (ferror(file)) {
	    		fprintf(stderr, "File read error occurred.\n");
		}
		fclose(file);
		free(buffer);
		return NULL;
	}

	fclose(file);
	buffer[length] = '\0';  // Null-terminate the buffer
	return buffer;
}
