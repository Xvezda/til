#include "xvzd/xvzd_common.h"
#include "xvzd/xvzd_object.h"
#include "xvzd/xvzd_item.h"
#include "xvzd/xvzd_array.h"
#include "xvzd/xvzd_string.h"

namespace xvzd {


template <typename T>
const String Array<T>::Join(const String& sep) const {
  String ret("");
  for (size_t i = 0; i < Size(); ++i) {
    ret += String((!i ? "" : sep.Cstr())) + String(At(i));
  }
  return ret;
}
template class Array<String>;


}  // namespace xvzd
