//
// Created by konrad on 18.11.18.
//

#ifndef CPP_PRBG_H
#define CPP_PRBG_H

class PRBG {
public:
    virtual bool getNextBit() = 0;
    virtual ~PRBG() = default;
};

#endif //CPP_PRBG_H
