#include "PcmFormat.h"

wav::PcmFormat::PcmFormat(BitParser* parser):
    WavFormat(parser)
    {}

wav::PcmFormat::~PcmFormat()
{
    delete this->fmtChunk;
    this->fmtChunk = nullptr;
}

void wav::PcmFormat::parseFmtChunk()
{
    this->fmtChunk = new PcmFmtChunk;

    this->fmtChunk->setChannels(this->parser->get<uint16_t>(16));
    this->fmtChunk->setSampleRate(this->parser->get<uint32_t>(32));
    this->fmtChunk->setByteRate(this->parser->get<uint32_t>(32));
    this->fmtChunk->setBlockAlign(this->parser->get<uint16_t>(16));
    this->fmtChunk->setBitsPerSample(this->parser->get<uint16_t>(16));
}

wav::PcmSample* wav::PcmFormat::nextSample()
{
    switch (this->getFmtChunk()->getBitsPerSample())
    {
        case 8:
            return new PcmSample(this->parser->get<int8_t>(8));
        case 16:
            return new PcmSample(this->parser->get<int16_t>(16));
        case 24:
            return new PcmSample(this->parser->get<float>(24));
        case 32:
            return new PcmSample(this->parser->get<float>(32));
        default:
            return nullptr;
    }
}