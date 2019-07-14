#ifndef LOODB_CODEC_H
#define LOODB_CODEC_H

#include <memory>

template<typename Object, typename Serial>
class Codec {

public:

    virtual Serial encode(const Object&) const = 0;
    virtual Object decode(const Serial&) const = 0;
};

#endif //LOODB_CODEC_H