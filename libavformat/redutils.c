#include <stdlib.h>
#include "url.h"
#include "avformat.h"


#define RED_FF_PROTOCOL(x)                                                                          \
extern URLProtocol ff_##x##_protocol;                                                               \
int redav_register_##x##_protocol(URLProtocol *protocol, int protocol_size);                        \
int redav_register_##x##_protocol(URLProtocol *protocol, int protocol_size)                         \
{                                                                                                   \
    if (protocol_size != sizeof(URLProtocol)) {                                                     \
        return -1;                                                                                  \
    }                                                                                               \
    memcpy(&ff_##x##_protocol, protocol, protocol_size);                                            \
    return 0;                                                                                       \
}

#define RED_DUMMY_PROTOCOL(x)                                       \
RED_FF_PROTOCOL(x);                                                 \
static const AVClass red_##x##_context_class = {                    \
    .class_name = #x,                                               \
    .item_name  = av_default_item_name,                             \
    .version    = LIBAVUTIL_VERSION_INT,                            \
    };                                                              \
                                                                    \
URLProtocol ff_##x##_protocol = {                                   \
    .name                = #x,                                      \
    .url_open2           = reddummy_open,                           \
    .priv_data_size      = 1,                                       \
    .priv_data_class     = &red_##x##_context_class,                \
};

static int reddummy_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    return -1;
}

RED_DUMMY_PROTOCOL(reddownload_adapter);

