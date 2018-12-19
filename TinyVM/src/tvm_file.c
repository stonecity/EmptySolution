#include "tvm_file.h"

FILE *tvm_fopen(const char *filename, const char *extension, const char *mode)
{
	FILE *pFile = NULL;
	size_t fname_chars = strlen(filename) + strlen(extension) + 1;
	char *fname = calloc(fname_chars, sizeof(char));
	int i;

	strcpy_s(fname, fname_chars * sizeof(char), filename);

	for(i = 0; i < 2 && !pFile; i++)
	{
		if(i > 0) strcat(fname, extension);
		pFile = fopen(fname, mode);
	}

	free(fname);
	return pFile;
}

int tvm_fcopy(char *dest, size_t size, FILE* src)
{
	size_t i;
	long pos = ftell(src);

	for(i = 0; i < size && !feof(src); i++) dest[i] = fgetc(src);
	dest[i - 1] = 0;

	fseek(src, pos, SEEK_SET);

	return 0;
}

int tvm_flength(FILE *f)
{
	int length;
	long pos = ftell(f);

	for(length = 0; !feof(f); length++) fgetc(f);
	fseek(f, pos, SEEK_SET);

	return length;
}
