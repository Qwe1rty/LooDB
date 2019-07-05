#ifndef LOODB_CODEC_H
#define LOODB_CODEC_H

template<typename Object, typename Serial>
class Codec {

public:

    virtual Serial encode(Object) const = 0;
    virtual Object decode(Serial) const = 0;
};

#endif //LOODB_CODEC_H