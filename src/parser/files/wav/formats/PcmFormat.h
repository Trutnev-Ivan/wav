#pragma once
#include "WavFormat.h"
#include "../chunks/PcmFmtChunk.h"
#include "../samples/PcmSample.h"

namespace wav
{
    class PcmFormat: public WavFormat
    {
    public:
        PcmFormat(BitParser* parser);
        ~PcmFormat();
        virtual void parseFmtChunk() override;
        virtual PcmSample* nextSample() override;
    };
}