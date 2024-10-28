#include "WavFormat.h"
#include "../WavParser.h"

wav::WavFormat::WavFormat(BitParser* parser)
{
    this->parser = parser;
}

wav::FmtChunk* wav::WavFormat::getFmtChunk()
{
    return this->fmtChunk;
}

wav::WavFormat::~WavFormat()
{
    delete this->fmtChunk;
    delete this->interpolationStrategy;
    this->fmtChunk = nullptr;
    this->interpolationStrategy = nullptr;
}

void wav::WavFormat::changeSampleRate(uint32_t sampleRate)
{
    this->recalculateSampleRate = sampleRate;
}

wav::WavSample* wav::WavFormat::getSample()
{
    if (this->recalculateSampleRate != 0 && this->interpolationStrategy != nullptr)
    {
        return this->interpolationStrategy->nextSample();
    }

    return this->nextSample();
}

void wav::WavFormat::setInterpolation(wav::Interpolation* interpolation)
{
    this->interpolationStrategy = interpolation;
}

uint32_t wav::WavFormat::getInterpolationSampleRate()
{
    return this->recalculateSampleRate;
}

bool wav::WavFormat::isFileEnd()
{
    return this->parser->isFileEnd();
}

bool wav::WavFormat::hasNextSample()
{
    wav::ChunkInfo chunkInfo = this->getChunkInfo(WavParser::DATA_ID);
    return !this->isFileEnd() && this->parser->getFile()->cur < chunkInfo.seek + chunkInfo.size || this->interpolationStrategy && this->interpolationStrategy->hasNextSample();
}

void wav::WavFormat::addChunkInfo(unsigned chunk, unsigned size, unsigned seek)
{
    wav::ChunkInfo chunkInfo;
    chunkInfo.size = size;
    chunkInfo.seek = seek;
    this->mapChunk.insert(std::make_pair(chunk, chunkInfo));
}

wav::ChunkInfo wav::WavFormat::getChunkInfo(unsigned chunk)
{
    return this->mapChunk[chunk];
}
