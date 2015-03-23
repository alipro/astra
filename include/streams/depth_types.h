#ifndef DEPTH_TYPES_H
#define DEPTH_TYPES_H

#include "../sensekit_types.h"

typedef struct _sensekit_depthframe {
    sensekit_frame_t* sk_frame;
    uint32_t frameIndex;
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    int16_t* data;
} sensekit_depthframe_t;

typedef struct _sensekit_depthframe_wrapper {
    sensekit_depthframe_t frame;
    void* data_addr;
} sensekit_depthframe_wrapper_t;

typedef struct _sensekit_depthstream sensekit_depthstream_t;

#endif // DEPTH_TYPES_H