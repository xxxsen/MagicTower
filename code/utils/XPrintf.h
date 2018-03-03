//
// Created by sen on 16-11-27.
//

#ifndef XXXLIB_PRINTF_H
#define XXXLIB_PRINTF_H

#include <string.h>
#include <sstream>
#include <string>
#include <iostream>

namespace sen
{
    namespace utils
    {

        std::ostream &xprintf(std::ostream &os, const char *fmt);

        template<typename T>
        std::ostream &xprintf(std::ostream &os, const char *fmt, const T &val)
        {
            const char *ptr = strstr(fmt, "{}");
            if(ptr)
            {
                os << std::string(fmt, ptr - fmt);
                os << val;
                xprintf(os, ptr + 2);
            }
            else
            {
                xprintf(os, fmt);
            }
            return os;
        }

        template<typename T, typename ...Args>
        std::ostream &xprintf(std::ostream &os, const char *fmt, const T &val, const Args &...args)
        {
            const char *ptr = strstr(fmt, "{}");
            if(ptr)
            {
                os << std::string(fmt, ptr - fmt);
                os << val;
                xprintf(os, ptr + 2, args...);
            }
            else
            {
                xprintf(os, fmt);
            }
            return os;
        }

        template<typename ...Args>
        std::string xsprintf(const char *fmt, const Args &...args)
        {
            std::ostringstream os;
            xprintf(os, fmt, args...);
            return os.str();
        }

        template<typename ...Args>
        void xprintf(const char *fmt, const Args &...args)
        {
            xprintf(std::cout, fmt, args...);
        }

        template<typename ...Args>
        int32_t xfprintf(FILE *fp, const char *fmt, const Args &...args)
        {
            return fprintf(fp, "%s", xsprintf(fmt, args...).c_str());
        }
    }
}

#endif //XXXLIB_PRINTF_H
