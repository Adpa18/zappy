//
// Created by gaspar_q on 6/6/16.
//

#ifndef SRC_CLIENT_AI_ISTREAM_HPP
#define SRC_CLIENT_AI_ISTREAM_HPP

#include <bits/stringfwd.h>

class IStream
{
public:
    virtual ~IStream(){}

public:
    virtual std::string Read(void) const = 0;
    virtual void Write(std::string const &towrite) const = 0;
};

#endif //SRC_CLIENT_AI_ISTREAM_HPP
