#pragma once
#include <cstdint>
#include <fstream>
#include <cassert>

enum BIT_ORDER {LSB, MSB};

/**
 * https://habr.com/ru/articles/359122/
*/
class BitParser
{
protected:
    uint64_t buffer = 0;
    int length = 0;
    BIT_ORDER order;
    std::ifstream* file = nullptr;

    template<class T>
    T getBigEndian(int count)
    {
        assert(count >= 0 && count <= 57);

        while (this->length < count)
        {
            this->buffer |= static_cast<uint64_t>(this->file->get()) << (56 - this->length);
            this->length += 8;
        }

        T result = (this->buffer >> 1) >> (63 - count);

        this->buffer << count;
        this->length -= count;

        return result;
    }

    template<class T>
    T getLittleEndian(int count)
    {
        assert(count >= 0 && count <= 57);

        while (this->length < count) 
        {
            this->buffer |= static_cast<uint64_t>(this->file->get()) << this->length;
            this->length += 8;
        }

        T result = this->buffer & ((1ull << count) - 1);

        this->buffer >>= count;
        this->length -= count;

        return result;
    }
public:
    BitParser(std::ifstream* file, BIT_ORDER order);
    BitParser(std::ifstream* file);
    uint64_t getUnsigned(int count);
    double getDouble(int count);
    int64_t getSigned(int count);
    std::ifstream* getFile();
    bool isFileEnd();
    std::streampos tellg();

    template<class T>
    T get(int count)
    {
        if (this->order == BIT_ORDER::MSB)
            return this->getBigEndian<T>(count);
        else
            return this->getLittleEndian<T>(count);
    }
};