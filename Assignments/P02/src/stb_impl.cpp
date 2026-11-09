// stb_impl.cpp — provided. Do not modify.
//
// stb_image and stb_image_write are "single-header" libraries: the .h
// file holds both the declarations AND the function bodies. The bodies
// are only compiled when the IMPLEMENTATION macro is defined first.
//
// C++'s One Definition Rule says each function may be defined only once
// in the whole program. So the macros go in exactly ONE .cpp (this one),
// and every other file includes the headers WITHOUT the macros, which
// gives them the declarations only.
//
// If you see "duplicate symbol stbi_load" at link time, some other .cpp
// defined these macros too.

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
