#pragma once
#include "WavHeaderException.h"

namespace wav
{
    class RiffException: WavHeaderException
    {
    public:
        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };
}