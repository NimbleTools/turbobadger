cmake_minimum_required(VERSION 2.8)

set(LOCAL_SRCS "")
aux_source_directory(. LOCAL_SRCS)
aux_source_directory(image LOCAL_SRCS)
aux_source_directory(animation LOCAL_SRCS)
aux_source_directory(parser LOCAL_SRCS)
aux_source_directory(renderers LOCAL_SRCS)
aux_source_directory(tests LOCAL_SRCS)
aux_source_directory(utf8 LOCAL_SRCS)

set(LOCAL_HEADERS "")
file(GLOB LOCAL_HEADERS "*.h" GLOB_RECURSE)

add_library(TurboBadgerLib ${LOCAL_SRCS} ${LOCAL_HEADERS})

if(TB_FONT_RENDERER_FREETYPE)
    target_link_libraries(TurboBadgerLib ${FREETYPE_LIBRARY})
    include_directories(${FREETYPE_INCLUDE_DIRS})
endif()

target_link_libraries(TurboBadgerLib -lGL)

install(TARGETS TurboBadgerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    