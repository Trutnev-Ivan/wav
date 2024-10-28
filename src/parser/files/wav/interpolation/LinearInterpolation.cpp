#include "LinearInterpolation.h"
#include "../formats/WavFormat.h"

wav::LinearInterpolation::LinearInterpolation(WavFormat* format, int dataSize): 
    Interpolation(format, dataSize) 
    {
    }

wav::WavSample* wav::LinearInterpolation::nextSample()
{
    if (this->buffer.size())
    {
        return this->getFirstElementFromBuffer();
    }

    this->fillBuffer();

    if (!this->buffer.size()){
        return nullptr;
    }

    return this->getFirstElementFromBuffer();
}

wav::WavSample* wav::LinearInterpolation::getFirstElementFromBuffer()
{
    wav::WavSample* tmp = this->buffer[0];
    this->buffer.erase(this->buffer.begin());
    return tmp;
}

void wav::LinearInterpolation::fillBuffer()
{
    uint32_t oldSampleRate = this->format->getFmtChunk()->getSampleRate();
    uint32_t newSampleRate = this->format->getInterpolationSampleRate();

    double factor = newSampleRate / static_cast<double>(oldSampleRate);
    this->buffer.clear();

    wav::WavSample* startSample = this->prevSample;
    wav::WavSample* endSample = nullptr;

    if (!this->format->isFileEnd() && startSample == nullptr)
    {
        startSample = this->format->nextSample();

    }
    
    if (!this->format->isFileEnd())
    {
        endSample = this->format->nextSample();
    }

    if (startSample != nullptr && this->prevSample == nullptr)
    {
        this->buffer.push_back(startSample);
    }

    if (endSample != nullptr)
    {
        this->countAppend += factor;
        uint32_t countPoints = static_cast<uint32_t>(this->countAppend) + 1;

        for (int i = 1; i < countPoints; ++i)
        {
            float h = 1.f / (int(this->countAppend)+1);

            wav::WavSample* s = this->getInterpolationSample(i, startSample, endSample);
            this->buffer.push_back(s);
        }
    
        this->buffer.push_back(endSample);    
        this->prevSample = new wav::WavSample(endSample);

        this->countAppend -= countPoints;
    }
}

wav::WavSample* wav::LinearInterpolation::getInterpolationSample(int i, wav::WavSample* start, wav::WavSample* end)
{
    float h = 1.f / (int(this->countAppend)+1);

    wav::WavSample* newSample = nullptr;

    switch (end->getStoreType())
    {
        case wav::WAV_STORE_TYPE::INT8:
        {
            int8_t sample = h * i * (end->getValue<int8_t>() - start->getValue<int8_t>()) + start->getValue<int8_t>();
            newSample = new wav::WavSample(static_cast<int8_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::UINT8:
        {
            uint8_t sample = h * i * (end->getValue<uint8_t>() - start->getValue<uint8_t>()) + start->getValue<uint8_t>();
            newSample = new wav::WavSample(static_cast<uint8_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::INT16:
        {
            int16_t sample = h * i * (end->getValue<int16_t>() - start->getValue<int16_t>()) + start->getValue<int16_t>();
            newSample = new wav::WavSample(static_cast<int16_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::UINT16:
        {
            uint16_t sample = h * i * (end->getValue<uint16_t>() - start->getValue<uint16_t>()) + start->getValue<uint16_t>();
            newSample = new wav::WavSample(static_cast<uint16_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::INT32:
        {
            int32_t sample = h * i * (end->getValue<int32_t>() - start->getValue<int32_t>()) + start->getValue<int32_t>();
            newSample = new wav::WavSample(static_cast<int32_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::UINT32:
        {
            uint32_t sample = h * i * (end->getValue<uint32_t>() - start->getValue<uint32_t>()) + start->getValue<uint32_t>();
            newSample = new wav::WavSample(static_cast<uint32_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::INT64:
        {
            int64_t sample = h * i * (end->getValue<int64_t>() - start->getValue<int64_t>()) + start->getValue<int64_t>();
            newSample = new wav::WavSample(static_cast<int64_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::UINT64:
        {
            uint64_t sample = h * i * (end->getValue<uint64_t>() - start->getValue<uint64_t>()) + start->getValue<uint64_t>();
            newSample = new wav::WavSample(static_cast<uint64_t>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::FLOAT:
        {
            float sample = h * i * (end->getValue<float>() - start->getValue<float>()) + start->getValue<float>();
            newSample = new wav::WavSample(static_cast<float>(sample));
            break;
        }
        case wav::WAV_STORE_TYPE::DOUBLE:
        {
            double sample = h * i * (end->getValue<double>() - start->getValue<double>()) + start->getValue<double>();
            newSample = new wav::WavSample(static_cast<double>(sample));
            break;
        }
    }

    return newSample;
}