#pragma once
#include <fstream>
#include <bit/BitParser.h>
#include <map>
#include "../chunks/FmtChunk.h"
#include "../samples/WavSample.h"
#include "../interpolation/Interpolation.h"

namespace wav
{
    struct ChunkInfo {
        unsigned size;
        unsigned seek;
    };

    class WavFormat
    {
    protected:

        BitParser* parser = nullptr;
        FmtChunk* fmtChunk = nullptr;
        uint32_t recalculateSampleRate = 0;
        Interpolation* interpolationStrategy = nullptr;
        std::map<unsigned, ChunkInfo> mapChunk;
    public:
        WavFormat(BitParser* parser);
        ~WavFormat();
        virtual void parseFmtChunk() = 0;
        FmtChunk* getFmtChunk();
        virtual WavSample* getSample();
        void changeSampleRate(uint32_t sampleRate);
        void setInterpolation(Interpolation* interpolation);
        uint32_t getInterpolationSampleRate();
        bool isFileEnd();
        virtual WavSample* nextSample() = 0; // Sample from file
        bool hasNextSample();
        void addChunkInfo(unsigned chunk, unsigned size, unsigned seek);
        ChunkInfo getChunkInfo(unsigned chunk);
    };
}
