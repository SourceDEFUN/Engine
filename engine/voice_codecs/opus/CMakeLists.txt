cmake_minimum_required(VERSION 4.0)
project(opus)
add_library(vaudio_opus SHARED
        voiceencoder_opus.cpp
        ../frame_encoder/voice_codec_frame.cpp
        ../../../tier1/interface.cpp
        ../../../public/tier0/memoverride.cpp
)

add_dependencies(vaudio_opus tier0 tier1 vstdlib)
target_link_libraries(vaudio_opus PUBLIC tier0 tier1 vstdlib, opus)

target_include_directories(vaudio_opus PUBLIC ./ ../../../public/tier1 ../../../public ../frame_encoder ../../ ../../../common ../../../public/engine/audio celt)
target_compile_definitions(vaudio_opus PUBLIC OPUS_EXPORTS=1)

install(TARGETS vaudio_opus DESTINATION bin)