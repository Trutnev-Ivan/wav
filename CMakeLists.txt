cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME our-free-sequencer)
project(${PROJECT_NAME}
        VERSION 1.0
        LANGUAGES CXX)

option(TEST "Build test cases" OFF)
set(INCLUDE_CORE_DIRECTORY "src/" CACHE INTERNAL "Include header files of core" FORCE)

add_library(tools
            "${INCLUDE_CORE_DIRECTORY}tools/NumberTools.h")
set_target_properties(tools PROPERTIES LINKER_LANGUAGE CXX)

add_library(bit
            "${INCLUDE_CORE_DIRECTORY}parser/bit/BitParser.h"
            "${INCLUDE_CORE_DIRECTORY}parser/bit/BitParser.cpp")
            
add_library(wav
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/WavParser.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/WavParser.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/samples/WavSample.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/samples/WavSample.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/samples/PcmSample.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/samples/PcmSample.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/WavFormatFactory.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/WavFormatFactory.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/formats/WavFormat.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/formats/WavFormat.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/formats/PcmFormat.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/formats/PcmFormat.cpp"

            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/Interpolation.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/Interpolation.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/LinearInterpolation.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/LinearInterpolation.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/Fir.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/interpolation/Fir.cpp"

            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/chunks/FmtChunk.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/chunks/FmtChunk.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/chunks/PcmFmtChunk.h"

            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WavException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WavHeaderException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/RiffException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/RiffException.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WaveException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WaveException.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/FormatChunkException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/FormatChunkException.cpp"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WaveUnknownFormatException.h"
            "${INCLUDE_CORE_DIRECTORY}parser/files/wav/exceptions/WaveUnknownFormatException.cpp")
target_link_libraries(wav PRIVATE bit)
target_link_libraries(wav PRIVATE tools)
target_include_directories(wav PRIVATE 
                            ${INCLUDE_CORE_DIRECTORY}
                            "${INCLUDE_CORE_DIRECTORY}parser/")

include("cmake/findPortAudio.cmake")

if(TEST)
    add_executable(test "tests/main.cpp")
    target_compile_features(test PUBLIC cxx_std_20)
    target_link_libraries(test PRIVATE wav)

    if (${PORTAUDIO_FOUND})
        target_include_directories(test PRIVATE ${PORTAUDIO_INCLUDE_DIRS})
        target_link_libraries(test PRIVATE ${PORTAUDIO_LIBRARY})
    endif()
    
    target_include_directories(test
        PRIVATE
        ${INCLUDE_CORE_DIRECTORY}
        "${INCLUDE_CORE_DIRECTORY}parser/"
        "${INCLUDE_CORE_DIRECTORY}parser/files/"
        )
endif()
