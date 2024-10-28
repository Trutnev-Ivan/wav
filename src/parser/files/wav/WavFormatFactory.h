#pragma once
#include <fstream>
#include <cstdint>
#include "formats/WavFormat.h"
#include "formats/PcmFormat.h"
#include "exceptions/WaveUnknownFormatException.h"
#include <bit/BitParser.h>

namespace wav
{
    enum class WAV_FORMATS {
        UNKNOWN = 0x0000,
        PCM = 0x0001
    };
    
    class WavFormatFactory
    {
    public:
        static WavFormat* getInstance(BitParser* parser, uint16_t format);
    };
}