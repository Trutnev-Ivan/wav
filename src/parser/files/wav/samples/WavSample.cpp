#include "WavSample.h"

wav::WavSample::WavSample(int8_t value)
{
    this->value = new int8_t(value);
    this->type = WAV_STORE_TYPE::INT8;
}

wav::WavSample::WavSample(uint8_t value)
{
    this->value = new uint8_t(value);
    this->type = WAV_STORE_TYPE::UINT8;
}

wav::WavSample::WavSample(int16_t value)
{
    this->value = new int16_t(value);
    this->type = WAV_STORE_TYPE::INT16;
}

wav::WavSample::WavSample(uint16_t value)
{
    this->value = new uint16_t(value);
    this->type = WAV_STORE_TYPE::UINT16;
}

wav::WavSample::WavSample(int32_t value)
{
    this->value = new int32_t(value);
    this->type = WAV_STORE_TYPE::INT32;
}

wav::WavSample::WavSample(uint32_t value)
{
    this->value = new uint32_t(value);
    this->type = WAV_STORE_TYPE::UINT32;
}

wav::WavSample::WavSample(int64_t value)
{
    this->value = new int64_t(value);
    this->type = WAV_STORE_TYPE::INT64;
}

wav::WavSample::WavSample(uint64_t value)
{
    this->value = new uint64_t(value);
    this->type = WAV_STORE_TYPE::UINT64;
}

wav::WavSample::WavSample(float value)
{
    this->value = new float(value);
    this->type = WAV_STORE_TYPE::FLOAT;
}

wav::WavSample::WavSample(double value)
{
    this->value = new double(value);
    this->type = WAV_STORE_TYPE::DOUBLE;
}

wav::WavSample::WavSample(WavSample* sample)
{
    this->type = sample->type;

    switch (this->type)
    {
        case wav::WAV_STORE_TYPE::DOUBLE:
        {
            double v = *static_cast<double*>(sample->value);
            this->value = new double(v);
            break;
        }
        case wav::WAV_STORE_TYPE::FLOAT:
        {
            float v = *static_cast<float*>(sample->value);
            this->value = new float(v);
            break;
        }
        case wav::WAV_STORE_TYPE::INT8:
        {
            int8_t v = *static_cast<int8_t*>(sample->value);
            this->value = new int8_t(v);
            break;
        }
        case wav::WAV_STORE_TYPE::UINT8:
        {
            uint8_t v = *static_cast<uint8_t*>(sample->value);
            this->value = new uint8_t(v);
            break;
        }
        case wav::WAV_STORE_TYPE::INT16:
        {
            int16_t v = *static_cast<int16_t*>(sample->value);
            this->value = new int16_t(v);
            break;
        }
        case wav::WAV_STORE_TYPE::UINT16:
        {
            uint16_t v = *static_cast<uint16_t*>(sample->value);
            this->value = new uint16_t(v);
            break;
        }
        case wav::WAV_STORE_TYPE::INT32:
        {
            int32_t v = *static_cast<int32_t*>(sample->value);
            this->value = new int32_t(v);
            break;
        }
        case wav::WAV_STORE_TYPE::UINT32:
        {
            uint32_t v = *static_cast<uint32_t*>(sample->value);
            this->value = new uint32_t(v);
            break;
        }
    }
}

wav::WavSample::~WavSample()
{
    switch (this->type)
    {
        case WAV_STORE_TYPE::DOUBLE:
            delete static_cast<double*>(this->value);
            break;
        case WAV_STORE_TYPE::FLOAT:
            delete static_cast<float*>(this->value);
            break;
        case WAV_STORE_TYPE::INT8:
            delete static_cast<int8_t*>(this->value);
            break;
        case WAV_STORE_TYPE::UINT8:
            delete static_cast<uint8_t*>(this->value);
            break;
        case WAV_STORE_TYPE::INT16:
            delete static_cast<int16_t*>(this->value);
            break;
        case WAV_STORE_TYPE::UINT16:
            delete static_cast<uint16_t*>(this->value);
            break;
        case WAV_STORE_TYPE::INT32:
            delete static_cast<int32_t*>(this->value);
            break;
        case WAV_STORE_TYPE::UINT32:
            delete static_cast<uint32_t*>(this->value);
            break;
    }

    this->value = nullptr;
}

wav::WAV_STORE_TYPE wav::WavSample::getStoreType()
{
    return this->type;
}

double wav::WavSample::normalize(double start, double end)
{
    return -1;
}

float wav::WavSample::normalize(float start, float end)
{
    return -1;
}

int64_t wav::WavSample::normalize(int64_t start, int64_t end)
{
    return -1;
}