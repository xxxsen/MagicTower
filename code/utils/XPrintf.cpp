#include "XPrintf.h"

namespace sen
{
    namespace utils
    {
        std::ostream &xprintf(std::ostream &os, const char *fmt)
        { 
            os << fmt;
            return os;
        }
    }	    
}
