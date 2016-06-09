/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#ifndef _crypt_h
#define _crypt_h

#include <iostream>
#include "s-box.h"
namespace xcrypter {
class crypt
{
    box sx;
public:
    crypt(const char *key) : sx(key) {};

    long enc(std::istream &is, std::ostream &os, unsigned char c=0);
    long dec(std::istream &is, std::ostream &os, unsigned char c=0);
};

}
#endif 
