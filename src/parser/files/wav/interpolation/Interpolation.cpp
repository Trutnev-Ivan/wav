#include "Interpolation.h"

wav::Interpolation::Interpolation(wav::WavFormat* format, int dataSize)
{
    this->format = format;
    this->dataSize = dataSize;
}

bool wav::Interpolation::hasNextSample()
{
    return false;
}