cmake_minimum_required(VERSION 4.0)
project(tier1)
add_library(tier1 STATIC
        ../utils/lzma/C/LzmaDec.c
		bitbuf.cpp
		byteswap.cpp
		characterset.cpp
		checksum_crc.cpp
		checksum_md5.cpp
		checksum_sha1.cpp
		commandbuffer.cpp
		convar.cpp
		datamanager.cpp
		diff.cpp
		generichash.cpp
		ilocalize.cpp
		interface.cpp
		KeyValues.cpp
		keyvaluesjson.cpp
		kvpacker.cpp
		lzmaDecoder.cpp
		lzss.cpp # [!$SOURCESDK]
		mempool.cpp
		memstack.cpp
		NetAdr.cpp
		newbitbuf.cpp
		rangecheckedvar.cpp
		reliabletimer.cpp
		snappy-sinksource.cpp
		snappy-stubs-internal.cpp
		snappy.cpp
		sparsematrix.cpp
		splitstring.cpp
		stringpool.cpp
		strtools.cpp
		strtools_unicode.cpp
		tier1.cpp
		tokenreader.cpp
		uniqueid.cpp
		utlbinaryblock.cpp
		utlbuffer.cpp
		utlbufferutil.cpp
		utlstring.cpp
		utlsymbol.cpp
)

target_compile_definitions(tier1 PUBLIC TIER1_STATIC_LIB=1)

if(WIN32)
    target_sources(tier1 PUBLIC processor_detect.cpp)
else()
    target_sources(tier1 PUBLIC processor_detect_linux.cpp qsort_s.cpp)
endif()

if(APPLE)
    target_link_libraries(tier1 PUBLIC iconv)
endif()