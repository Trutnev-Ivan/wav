#pragma once
#include "Interpolation.h"
#include <vector>
#include "../samples/WavSample.h"
#include "../samples/PcmSample.h"

namespace wav
{
    class Fir: public Interpolation
    {
    private:
        std::vector<PcmSample*> buffer;
        std::vector<wav::WavSample*> samples;
        int index = 0;
        std::vector<float> coefficients;
    protected:
        void interpolateSamples(std::vector<float> samples, float fraction);
        void calcCoefficients();
    public:
        Fir(WavFormat* format, int dataSize);
        virtual WavSample* nextSample();
        virtual bool hasNextSample() override;
    };
}