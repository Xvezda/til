#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_item.h"
#include "xvzd_array.h"
#include "xvzd_string.h"


using xvzd::Object;
using xvzd::Item;
using xvzd::Array;
using xvzd::String;

template <>
const char* Array<Object*>::Cstr() const {
  size_t total = 0;

  total += std::strlen("[");
  for (size_t i = 0; i < Size(); ++i) {
    total += (std::strlen(At(i)->Cstr()) + \
        (i != Size() - 1 ? std::strlen(", ") : 0));
  }
  total += std::strlen("]");
#ifdef DEBUG
  std::cout << __FILE__ << ':' << __LINE__ << ": "
    << "total: " << total << std::endl;
#endif
  cstr_ptr = new char[total+1];
  cstr_ptr[0] = '\0';

  std::strncat(cstr_ptr, "[", std::strlen("["));
  for (size_t i = 0; i < Size(); ++i) {
    std::strncat(cstr_ptr, At(i)->Cstr(), std::strlen(At(i)->Cstr()));
    const char* sep = (i != Size() - 1 ? ", " : "");
    std::strncat(cstr_ptr, sep, std::strlen(sep));
  }
  std::strncat(cstr_ptr, "]", std::strlen("]"));
  cstr_ptr[total] = '\0';

  return cstr_ptr;
}

