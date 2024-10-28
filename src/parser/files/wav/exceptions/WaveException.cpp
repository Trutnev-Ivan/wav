#include "WaveException.h"

const char* wav::WaveException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
     return "Header doesn`t have a WAVE id";
}