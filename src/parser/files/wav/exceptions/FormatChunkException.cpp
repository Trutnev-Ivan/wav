#include "FormatChunkException.h"

const char* wav::FormatChunkException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return "Can`t find fmt chunk";
}