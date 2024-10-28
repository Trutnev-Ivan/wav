#include "PcmSample.h"
#include <tools/NumberTools.h>

wav::PcmSample::PcmSample(int8_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(uint8_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(int16_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(uint16_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(int32_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(uint32_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(int64_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(uint64_t value):
    WavSample(value){}
wav::PcmSample::PcmSample(float value):
    WavSample(value){}
wav::PcmSample::PcmSample(double value):
    WavSample(value){}
wav::PcmSample::PcmSample(wav::PcmSample* value):
    WavSample(value){}

double wav::PcmSample::normalize(double start, double end)
{
    double value = 0;
    double fromStart = 0;
    double fromEnd = 0;

    switch (this->type)
    {
        case wav::WAV_STORE_TYPE::INT8:
            value = *static_cast<int8_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_8;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_8;
            break;
        case wav::WAV_STORE_TYPE::INT16:
            value = *static_cast<int16_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_16;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_16;
            break;
        case wav::WAV_STORE_TYPE::FLOAT:
        case wav::WAV_STORE_TYPE::DOUBLE:
            value = *static_cast<double*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_32;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_32;
            break;
    }

    return NumberTools::convertDiapason<double>(
                        value,
                        fromStart,
                        fromEnd, 
                        start,
                        end);
}

float wav::PcmSample::normalize(float start, float end)
{
    float value = 0;
    float fromStart = 0;
    float fromEnd = 0;

    switch (this->type)
    {
        case wav::WAV_STORE_TYPE::INT8:
            value = *static_cast<int8_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_8;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_8;
            break;
        case wav::WAV_STORE_TYPE::INT16:
            value = *static_cast<int16_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_16;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_16;
            break;
        case wav::WAV_STORE_TYPE::FLOAT:
        case wav::WAV_STORE_TYPE::DOUBLE:
            value = *static_cast<double*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_32;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_32;
            break;
    }

    return NumberTools::convertDiapason<float>(
                        value,
                        fromStart,
                        fromEnd, 
                        start,
                        end);
}

int64_t wav::PcmSample::normalize(int64_t start, int64_t end)
{
    int64_t value = 0;
    int64_t fromStart = 0;
    int64_t fromEnd = 0;

    switch (this->type)
    {
        case wav::WAV_STORE_TYPE::INT8:
            value = *static_cast<int8_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_8;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_8;
            break;
        case wav::WAV_STORE_TYPE::INT16:
            value = *static_cast<int16_t*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_16;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_16;
            break;
        case wav::WAV_STORE_TYPE::FLOAT:
        case wav::WAV_STORE_TYPE::DOUBLE:
            value = *static_cast<double*>(this->value);
            fromStart = PcmSample::MIN_SAMPLE_VALUE_32;
            fromEnd = PcmSample::MAX_SAMPLE_VALUE_32;
    }

    return NumberTools::convertDiapason<int64_t>(
                        value,
                        fromStart,
                        fromEnd, 
                        start,
                        end);
}