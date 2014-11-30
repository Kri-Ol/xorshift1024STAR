// -*- C++ -*-

#include "xorshift1024star.hpp"

namespace OTI
{
    void xorshift1024star::skip(uint64_t ns) const
    {
        while (ns)
        {
            sample();
            --ns;
        }
    }
}
