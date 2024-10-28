#pragma once
#include <cstdint>
#include <string>

namespace wav
{
    class FmtChunk
    {
    protected:
        uint16_t channels = 0;
        uint32_t sampleRate = 0;
        uint32_t byteRate = 0;
        uint16_t blockAlign = 0;
        uint16_t bitsPerSample = 0;
    public:
        uint16_t getChannels();
        uint32_t getSampleRate();
        uint32_t getByteRate();
        uint16_t getBlockAlign();
        uint16_t getBitsPerSample();
    
        void setChannels(uint16_t channels);
        void setSampleRate(uint32_t sampleRate);
        void setByteRate(uint32_t byteRate);
        void setBlockAlign(uint16_t blockAlign);
        void setBitsPerSample(uint16_t bitsPerSample);

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& out, const FmtChunk& chunk);
        friend std::ostream& operator<<(std::ostream& out, const FmtChunk* chunk);
    };
}
