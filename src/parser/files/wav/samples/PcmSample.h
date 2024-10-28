#pragma once
#include "WavSample.h"

namespace wav
{
    class PcmSample: public WavSample
    {
    protected:
        static const int MIN_SAMPLE_VALUE_8 = -128;
        static const int MAX_SAMPLE_VALUE_8 = 127;
        static const int MIN_SAMPLE_VALUE_16 = -32760;
        static const int MAX_SAMPLE_VALUE_16 = 32760;
        static const int MIN_SAMPLE_VALUE_24 = -1;
        static const int MAX_SAMPLE_VALUE_24 = 1;
        static const int MIN_SAMPLE_VALUE_32 = -1;
        static const int MAX_SAMPLE_VALUE_32 = 1;
    public:
        PcmSample(int8_t value);
        PcmSample(uint8_t value);
        PcmSample(int16_t value);
        PcmSample(uint16_t value);
        PcmSample(int32_t value);
        PcmSample(uint32_t value);
        PcmSample(int64_t value);
        PcmSample(uint64_t value);
        PcmSample(float value);
        PcmSample(double value);
        PcmSample(PcmSample* value);
    
        virtual double normalize(double start, double end) override;
        virtual float normalize(float start, float end) override;
        virtual int64_t normalize(int64_t start, int64_t end) override;
    };
}