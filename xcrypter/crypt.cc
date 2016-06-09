/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#include "crypt.h"

namespace xcrypter {
long crypt::enc(std::istream &is, std::ostream &os, unsigned char c)
{
    long count = 0;
    char g;
    while(is.get(g))
    {
        unsigned char tmp = sx.get(g);
    	tmp = tmp ^ sx.get(c);
	os << tmp;
	c++;
	count++;
    } 
    return count;
}

long crypt::dec(std::istream &is, std::ostream &os, unsigned char c)
{
    long count = 0;
    char g;
    while(is.get(g))
    {
        unsigned char tmp = sx.get(c) ^ g;
	tmp = sx.getr(tmp);
	os << tmp;
	c++;
	count++;
    }
    return count;
}

}
