#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_string.h"

namespace xvzd {


const String Object::ToString() const {
  return String(Cstr());
}


}  // namespace xvzd
