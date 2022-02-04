#include "base64.h"


const char
base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                 "abcdefghijklmnopqrstuvwxyz"
                 "0123456789+/";


char* base64_encode(const char *str)
{
  size_t len = strlen(str);

  // Re allocated length (include padding + null bytes)
  size_t re_len = PADDING_SIZE((int)((len-1)*BYTE_SIZE/BLOCK_SIZE),
                                sizeof(int)) + 1;
  // Re allocate buffer size (mul of 3)
  size_t buf_size = PADDING_SIZE(len, UNIT_SIZE);

  uint8_t buffer[buf_size];
  uint8_t *result = malloc(re_len);

  assert(result != NULL);

  // Initialize
  memset(buffer, 0, buf_size);
  memset(result, 0, re_len);
  // Copy argument to result variable
  memcpy(buffer, str, len);

  size_t input_bit = len * BYTE_SIZE;

  int i, j;
  int unit = BYTE_SIZE * UNIT_SIZE;
  size_t gap = 0;
  for (i = unit; /* true */; i += unit) {
    if (i >= input_bit) {
      gap = i - input_bit;
      break;
    }
  }
  size_t result_bit_len = input_bit + gap;
  size_t result_len = result_bit_len / BYTE_SIZE;

  uint8_t *buffer_ptr = (uint8_t*) buffer;

#ifdef DEBUG
  printf("buf_size: %zu\n", buf_size);
  printf("re_len: %zu\n", re_len);
#endif
  /*
   * Mask 8bits to 6bit (mask << 6) 4 cycles)
   *
   * 00000000 00000000 00000000 00000000
   *
   * 11111100 00000000 00000000 00000000
   * 00000011 11110000 00000000 00000000
   * 00000000 00001111 11000000 00000000
   * 00000000 00000000 00111111 00000000
   */
  int index  = 0;

  uint8_t mask  = 0;
  uint8_t mask2 = 0;

  for (i = 0; i < re_len-1; i += sizeof(int)) {
    mask  = 0xfc;
    mask2 = 0x00;
    index = (mask & *buffer_ptr) >> (BYTE_SIZE - BLOCK_SIZE);
    result[i] = base64_table[index];

    mask  = 0x03;
    mask2 = 0xf0;
    index = ((mask  & *buffer_ptr)     << (-BYTE_SIZE + BLOCK_SIZE * 2))
          | ((mask2 & *(buffer_ptr+1)) >> (-BYTE_SIZE + BLOCK_SIZE * 2));
    result[i+1] = base64_table[index];

    mask  = 0x0f;
    mask2 = 0xc0;
    index = ((mask  & *(buffer_ptr+1)) << (BYTE_SIZE - BLOCK_SIZE))
          | ((mask2 & *(buffer_ptr+2)) >> BLOCK_SIZE);
    result[i+2] = base64_table[index];

    mask  = 0x00;
    mask2 = 0x3f;
    index = (mask2 & *(buffer_ptr+2));
    result[i+3] = base64_table[index];

#ifdef DEBUG
    printf("%u %u\n", *(buffer_ptr+1), *(buffer_ptr+2));
#endif
    // Padding
    if (!*(buffer_ptr+1)) {
      result[i+2] = PADCHR;
    }
    if (!*(buffer_ptr+2)) {
      result[i+3] = PADCHR;
    }
    buffer_ptr += UNIT_SIZE;
  }
  assert(result[result_len] != '\0');

  return (char*) result;
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage: %s <string>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Text to encode
  char *text = argv[1];

  char *encoded = base64_encode(text);
  printf("%s\n", encoded);

  free(encoded);
  encoded = NULL;

  return EXIT_SUCCESS;
}

