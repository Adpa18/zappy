//
// Created by gaspar_q on 6/6/16.
//

#ifndef SRC_CLIENT_AI_ISTREAM_HPP
#define SRC_CLIENT_AI_ISTREAM_HPP

#include <string>

class INetStream
{
public:
    virtual ~INetStream(){}

public:
    virtual std::string Read(int flags) const = 0;
    virtual void Write(std::string const &towrite, int flags) const = 0;
};

#endif //SRC_CLIENT_AI_ISTREAM_HPP
