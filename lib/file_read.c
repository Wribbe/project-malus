#include "utils.h"

char *
file_read(const char * filename, size_t * p_size_data)
{
  FILE * fh = fopen(filename, "r");
  if (fh == NULL) {
    fprintf(stderr, "Could not open %s\n", filename);
    return NULL;
  }
  fseek(fh, 0, SEEK_END);
  size_t size_data = ftell(fh);
  rewind(fh);
  char * data = malloc(size_data);

  if (data == NULL) {
    fprintf(stderr, "Could not allocate memory for file-data.\n");
    return NULL;
  }

  size_t size_read = 0;

  for(;;) {
    size_read += fread(data+size_read, 1, size_data-size_read, fh);
    fprintf(stderr, "read: %zu\n", size_read);
    if (size_read == size_data) {
      break;
    }
  }

  if (p_size_data != NULL) {
    *p_size_data = size_data;
  }

  fclose(fh);
  return data;
}
