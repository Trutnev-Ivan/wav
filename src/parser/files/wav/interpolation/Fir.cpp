#include "Fir.h"
#include "../formats/WavFormat.h"
#include "../samples/PcmSample.h"
#include "../WavParser.h"
#include <cmath>
#include <iostream>
#include <fstream>

wav::Fir::Fir(WavFormat* format, int dataSize):
    Interpolation(format, dataSize)
{
    this->filteredFile = new std::fstream("file.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    this->output = new std::fstream("out.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    uint32_t oldSampleRate = this->format->getFmtChunk()->getSampleRate();
    uint32_t newSampleRate = this->format->getInterpolationSampleRate();
    float fraction = newSampleRate / (float)oldSampleRate;
 
    float tmp = 0;

    this->calcCoefficients();
    this->size = dataSize / sizeof(uint16_t) + coefficients.size();

    //TODO: change sizeof
    for (int i = 0; i < dataSize / sizeof(uint16_t) + coefficients.size() - 1; ++i)
    {
        this->filteredFile->write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    }

    int i = 0;
    float cur;

    while (this->format->hasNextSample())
    {
        wav::WavSample* sample = this->format->nextSample();

        // TODO: change sizeof type
        for (int j = 0; j < coefficients.size(); ++j){
            this->filteredFile->seekg((i + j) * sizeof(tmp), this->filteredFile->beg);
            this->filteredFile->read(reinterpret_cast<char*>(&cur), sizeof(cur));

            cur += sample->normalize(-32760.0f, 32760.0f) * coefficients[j];
            this->filteredFile->seekg((i + j) * sizeof(tmp), this->filteredFile->beg);
            this->filteredFile->write(reinterpret_cast<char*>(&cur), sizeof(cur));
        }

        ++i;
    }

    this->size = i;

    this->filteredFile->flush();
    this->filteredFile->close();
    std::vector<float> filtered_signal;

    this->interpolateSamples(fraction);
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

void wav::Fir::interpolateSamples(float fraction)
{
    this->filteredFile = new std::fstream("file.bin", std::ios::in | std::ios::binary | std::ios::app);
    int new_length = int(this->size * fraction);

    for (int i = 0; i < new_length; ++i){
        // Находим исходный индекс и его дробную часть
        float orig_index = i / fraction;
        int left_index = int(orig_index);
        int right_index = std::min(left_index + 1, this->size - 1);

        float tmp;

        if (left_index == right_index){
            this->filteredFile->seekg(left_index * sizeof(tmp), this->filteredFile->beg);
            this->filteredFile->read(reinterpret_cast<char*>(&tmp), sizeof(tmp));

            int16_t iTmp = int16_t(tmp);
            this->output->write(reinterpret_cast<char*>(&iTmp), sizeof(iTmp));
        }
        else
        {
            float frac = orig_index - left_index;
            float tmp_right;
            float tmp_left;

            this->filteredFile->seekg(left_index * sizeof(tmp_left), this->filteredFile->beg);
            this->filteredFile->read(reinterpret_cast<char*>(&tmp_left), sizeof(tmp_left));
            this->filteredFile->seekg(right_index * sizeof(tmp_right), this->filteredFile->beg);
            this->filteredFile->read(reinterpret_cast<char*>(&tmp_right), sizeof(tmp_right));

            tmp = (1 - frac) * tmp_left + frac * tmp_right;

            int16_t iTmp = int16_t(tmp);

            this->output->write(reinterpret_cast<char*>(&iTmp), sizeof(iTmp));
        }
    }
    
    this->output->seekg(0, this->output->beg);
}

wav::WavSample* wav::Fir::nextSample()
{
    if (!this->hasNextSample())
        return nullptr;

    int16_t tmp;
    this->output->read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    wav::WavSample* sample = new PcmSample(tmp);

    return sample;
}

bool wav::Fir::hasNextSample()
{
    return !this->output->eof();
}