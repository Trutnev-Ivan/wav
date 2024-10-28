#include "WavParser.h"
#include <iostream>
#include "interpolation/LinearInterpolation.h"
#include "interpolation/Fir.h"

wav::WavParser::WavParser(std::string path)
{    
    if (!std::filesystem::exists(path))
        throw std::ifstream::failure("File " + path + " not exists");

    if (std::filesystem::path(path).extension() != ".wav")
        throw std::ifstream::failure("File extension must be .wav");

    this->file = new std::ifstream(path, std::ios::binary);
    this->bitParser = new BitParser(file, BIT_ORDER::LSB);

    this->parseHeader();
}

/**
 * Парсит заголовок у wav
 */
void wav::WavParser::parseHeader()
{
    if (this->bitParser->getUnsigned(32) != WavParser::RIFF)
        throw RiffException();

    this->fileSize = this->bitParser->getUnsigned(32) + 8;

    if (this->bitParser->getUnsigned(32) != WavParser::WAVE)
        throw WaveException();

    unsigned fmtChunkSeek = this->bitParser->getFile()->cur;

    if (this->bitParser->getUnsigned(32) != WavParser::FORMAT_ID)
        throw FormatChunkException();

    uint32_t formatChunkSize = this->bitParser->getUnsigned(32);

    this->parsingStrategy = WavFormatFactory::getInstance(this->bitParser, this->bitParser->getUnsigned(16));
    this->parsingStrategy->parseFmtChunk();

    this->parsingStrategy->addChunkInfo(WavParser::FORMAT_ID, formatChunkSize, fmtChunkSeek);

    unsigned chunkSeek = this->bitParser->getFile()->cur;
    uint32_t chunkId = this->bitParser->getUnsigned(32);

    //TODO: добавить парсинг др. типов чанков
    if (chunkId == WavParser::DATA_ID)
    {
        this->parsingStrategy->addChunkInfo(WavParser::DATA_ID, this->bitParser->getUnsigned(32), chunkSeek);
    }
}

// TODO: добавить возможность менять интерполяцию
void wav::WavParser::setInterpolation(wav::Interpolation* interpolation)
{
    this->parsingStrategy->setInterpolation(new wav::Fir(this->parsingStrategy, this->parsingStrategy->getChunkInfo(WavParser::DATA_ID).size));
}

wav::WavParser::~WavParser()
{
    this->file->close();
    
    delete this->file;
    delete this->bitParser;
    delete this->parsingStrategy;

    this->file = nullptr;
    this->bitParser = nullptr;
    this->parsingStrategy = nullptr;
}

wav::FmtChunk* wav::WavParser::getHeader()
{
    if (this->parsingStrategy)
        return this->parsingStrategy->getFmtChunk();

    return nullptr;
}

/**
 * Возвращает 1 сэмпл
 */
wav::WavSample* wav::WavParser::getSample()
{
    if (this->parsingStrategy->hasNextSample())
        return this->parsingStrategy->getSample();
    
    return nullptr;
}

/**
 * Возвращает count сэмплов
 */
std::vector<wav::WavSample*> wav::WavParser::getSamples(int count)
{
    std::vector<WavSample*> vector;

    for (int i = 0; i < count; ++i)
    {
        WavSample* sample = this->getSample();

        if (sample == nullptr)
            break;

        vector.push_back(sample);
    }

    return vector;
}

/*
Если нужно передескретизировать файл
*/
void wav::WavParser::changeSampleRate(uint32_t sampleRate)
{
    this->recalculateSampleRate = sampleRate;
    if (this->parsingStrategy != nullptr)
        this->parsingStrategy->changeSampleRate(sampleRate);
}