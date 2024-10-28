#pragma once
#include "WavException.h"

namespace wav
{
    class WaveUnknownFormatException: public WavException
    {
    public:
        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };
}