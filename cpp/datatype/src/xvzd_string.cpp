#include "xvzd/xvzd_array.h"
#include "xvzd/xvzd_string.h"


namespace xvzd {


const Array<String> String::Split(String token) const {
  Array<String> ret;
  String cpy(*this);

  int offset = 0;
  for (;;) {
    offset = cpy.Find(token);
    if (offset == -1) {
      if (cpy.Length()) {
        ret.Push(cpy);
      }
      break;
    }
    ret.Push(cpy.Slice(0, offset));
    cpy = cpy.Slice(offset + token.Length());
  }
  return ret;
}


}  // namespace xvzd
