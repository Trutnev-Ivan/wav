#pragma once
#include "../samples/WavSample.h"

namespace wav
{
    class WavFormat;

    class Interpolation {
    protected:
        WavFormat* format = nullptr;
        int dataSize = 0;
    public:
        Interpolation(WavFormat* format, int dataSize);
        virtual WavSample* nextSample() = 0;
        virtual bool hasNextSample();
    };
}