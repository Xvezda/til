#ifndef BASE64_H_
#define BASE64_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>


#define BYTE_SIZE  8  /* Default bits per byte */
#define BLOCK_SIZE 6  /* Number of bits in base64 block */

/* Number of bytes for encode base64 */
#define UNIT_SIZE  (BLOCK_SIZE * sizeof(int) / BYTE_SIZE)

#define PADDING_SIZE(orig, base) \
  ((orig) + ((base) - ((orig) % (base))))
#define PADCHR '='


#endif  // BASE64_H_

