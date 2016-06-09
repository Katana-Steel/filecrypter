/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#ifndef _s_box_h
#define _s_box_h

namespace xcrypter {
class box 
{
    unsigned char sbox[16][16];
public:
    box(const char *);
    unsigned char get(unsigned char);
    unsigned char getr(unsigned char);
};    

}
#endif
