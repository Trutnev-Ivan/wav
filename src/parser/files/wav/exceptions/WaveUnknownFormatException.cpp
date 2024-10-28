#include "WaveUnknownFormatException.h"

const char* wav::WaveUnknownFormatException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return "Unknown audio format in wave file";
}