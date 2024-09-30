#include "Fir.h"
#include "../formats/WavFormat.h"
#include "../samples/PcmSample.h"
#include <cmath>

wav::Fir::Fir(WavFormat* format, int dataSize):
    Interpolation(format, dataSize)
{
    uint32_t oldSampleRate = this->format->getFmtChunk()->getSampleRate();
    uint32_t newSampleRate = this->format->getInterpolationSampleRate();
    float fraction = newSampleRate / (float)oldSampleRate;
 
    while (this->format->hasNextSample(this->dataSize - this->format->tellg()))
    {
        samples.push_back(this->format->nextSample());
    }

    //for (int i = 0; i < this->dataSize; ++i){
    //    samples.push_back(this->format->nextSample());
    //}

    this->calcCoefficients();

    std::vector<float> filtered_signal;

    for (int i = 0; i < samples.size() + coefficients.size() - 1; ++i)
    {
        filtered_signal.push_back(0);
    }

    for (int i = 0; i < samples.size(); ++i){
        for (int j = 0; j < coefficients.size(); ++j){
            filtered_signal[i + j] += samples[i]->normalize(-32760.0f, 32760.0f) * coefficients[j];
        }
    }

    this->interpolateSamples(std::vector<float>(filtered_signal.begin(), filtered_signal.begin() + samples.size()), fraction);
}

void wav::Fir::calcCoefficients()
{
    int numtaps = 3;
    int M = numtaps - 1; // Порядок фильтра
    float cutoff = 0.8;

    // Расчет идеальной импульсной характеристики (периодический фильтр)
    for (int n = 0; n < numtaps; ++n)
    {
        if (n == M / 2)
            this->coefficients.push_back(2 * cutoff); // Дельта-функция
        else
            this->coefficients.push_back(sin(2 * 3.14159 * cutoff * (n - M / 2)) / (3.14159 * (n - M / 2)));
    }
    
    //TODO: добавить др. функции
    // Применение оконной функции (прямоугольное окно)
    // В других реализациях вы можете использовать другие окна, такие как Хан или Хамминг
    for (int n = 0; n < numtaps; ++n){
        this->coefficients[n] *= 1.0; // Прямоугольное окно (все равны 1)
    }
}

void wav::Fir::interpolateSamples(std::vector<float> samples, float fraction)
{
    int new_length = int(samples.size() * fraction);

    for (int i = 0; i < new_length; ++i)
    {
        this->buffer.push_back(0);
    }

    for (int i = 0; i < new_length; ++i){
        // Находим исходный индекс и его дробную часть
        float orig_index = i / fraction;
        int left_index = int(orig_index);
        int right_index = std::min(left_index + 1, (int)samples.size() - 1);

        if (left_index == right_index){
            this->buffer[i] = new PcmSample((int16_t)samples[left_index]);
        }
        else
        {
            float frac = orig_index - left_index;

            this->buffer[i] = new PcmSample(static_cast<int16_t>((1 - frac) * samples[left_index] + frac * samples[right_index]));
        }
    }

}

wav::WavSample* wav::Fir::nextSample()
{
    if (!this->hasNextSample())
        return nullptr;

    wav::WavSample* sample = this->buffer[this->index++];

    return sample;
}

bool wav::Fir::hasNextSample()
{
    //std::cout << this->buffer.size() << " - " << this->index << std::endl;

    return this->index != this->buffer.size();
}