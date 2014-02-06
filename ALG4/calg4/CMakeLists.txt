project(calg4)

include_directories(include)
set(LIBRARYS m)



set(LIBS_SRC_FILES src/str.c src/stats.c)
set(UF_SRC_FILES src/uf.c src/qfuf.c src/quuf.c src/wquuf.c)
set(TESTUF_FILES test/test_uf.c)

set(TESTUF_SRC_FILES ${TESTUF_FILES} ${UF_SRC_FILES} ${LIBS_SRC_FILES})
add_executable(test_uf ${TESTUF_SRC_FILES})
target_link_libraries(test_uf ${LIBRARYS})

