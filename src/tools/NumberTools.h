#pragma once

class NumberTools
{
public:
    /** 
     * Переводит значение из одного диапазона в другой 
     * 
     * value -- текущее значение
     * fromStart -- нижнее значение исходного диапазона
     * fromEnd -- верхнее значение исходного диапазона
     * toStart -- нижнее значение конечного диапазона
     * toEnd -- верхнее значение конечного диапазона
     * 
     * ------------
     * convertDiapason(0, -1, 1, 100, 300) -> 200
     * */
    template<class T>
    static T convertDiapason(T value, T fromStart, T fromEnd, T toStart, T toEnd)
    {
        T fromLength = fromEnd - fromStart;
        T toLength = toEnd - toStart;
        T k = toLength / fromLength;
        T xd = value - fromStart;
        T yd = xd * k;
        return yd + toStart;
    }
};