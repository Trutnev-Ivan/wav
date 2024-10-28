#include "WavFormatFactory.h"

wav::WavFormat* wav::WavFormatFactory::getInstance(BitParser* parser, uint16_t format)
{
    switch (static_cast<WAV_FORMATS>(format))
    {
        case WAV_FORMATS::PCM:
            return new PcmFormat(parser);
        case WAV_FORMATS::UNKNOWN:
        default:
            throw WaveUnknownFormatException();
    }
}