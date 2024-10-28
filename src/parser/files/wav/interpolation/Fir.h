#pragma once
#include "Interpolation.h"
#include <vector>
#include "../samples/WavSample.h"
#include "../samples/PcmSample.h"
#include <fstream>

namespace wav
{
    class Fir: public Interpolation
    {
    private:
        std::fstream* filteredFile;
        std::fstream* output;
        std::vector<PcmSample*> buffer; // TODO: Заменить на потоковый файловый инпут
        std::vector<wav::WavSample*> samples;
        int index = 0;
        std::vector<float> coefficients;
        int size = 0;
    protected:
        void interpolateSamples(float fraction);
        void calcCoefficients();
    public:
        Fir(WavFormat* format, int dataSize);
        virtual WavSample* nextSample();
        virtual bool hasNextSample() override;
    };
}