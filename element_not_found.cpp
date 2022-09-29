#include "element_not_found.h"

element_not_found::element_not_found(const std::string &mex) : std::logic_error(mex) {}