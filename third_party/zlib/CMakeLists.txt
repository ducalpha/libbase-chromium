# extract from BUILD.gn

project (zlib)

set (SRC_FILES 
    "adler32.c",
    "compress.c",
    "crc32.c",
    "crc32.h",
    "deflate.c",
    "deflate.h",
    "gzclose.c",
    "gzguts.h",
    "gzlib.c",
    "gzread.c",
    "gzwrite.c",
    "infback.c",
    "inffast.c",
    "inffast.h",
    "inffixed.h",
    "inflate.c",
    "inflate.h",
    "inftrees.c",
    "inftrees.h",
    "mozzconf.h",
    "trees.c",
    "trees.h",
    "uncompr.c",
    "x86.h",
    "zconf.h",
    "zlib.h",
    "zutil.c",
    "zutil.h")

add_library (chrome_zlib, ${SRC_FILES})
