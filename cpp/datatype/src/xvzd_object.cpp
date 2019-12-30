#include "xvzd/xvzd_common.h"
#include "xvzd/xvzd_object.h"
#include "xvzd/xvzd_string.h"

namespace xvzd {


const String Object::ToString() const {
  return String(Cstr());
}


}  // namespace xvzd
