#include "BitParser.h"

BitParser::BitParser(std::ifstream* file, BIT_ORDER order)
{
    this->file = file;
    this->order = order;
}

BitParser::BitParser(std::ifstream* file)
{
    this->file = file;
    this->order = BIT_ORDER::LSB;
}

uint64_t BitParser::getUnsigned(int count)
{
    if (this->order == BIT_ORDER::MSB)
        return this->getBigEndian<uint64_t>(count);
    else
        return this->getLittleEndian<uint64_t>(count);
}

double BitParser::getDouble(int count)
{
    if (this->order == BIT_ORDER::MSB)
        return this->getBigEndian<double>(count);
    else
        return this->getLittleEndian<double>(count);
}

int64_t BitParser::getSigned(int count)
{
if (this->order == BIT_ORDER::MSB)
        return this->getBigEndian<int64_t>(count);
    else
        return this->getLittleEndian<int64_t>(count);
}

std::ifstream* BitParser::getFile()
{
    return this->file;
}

bool BitParser::isFileEnd()
{
    return this->file->eof();
}

std::streampos BitParser::tellg()
{
    return this->file->tellg();
}
