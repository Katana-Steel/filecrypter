/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#include "crypt.h"

namespace xcrypter {

	crypt_g1::crypt_g1(const char *key)
	{ 
		this->sx = new box(key); 
	}
	crypt_g1::crypt_g1()
	{ 
		this->sx = 0; 
	}

	crypt_g1::~crypt_g1()
	{
		if(this->sx) delete sx;
	}

	void 
	crypt_g1::set_key(const char *key) 
	{ 
		if(this->sx) delete this->sx; 
		this->sx = new box(key); 
	}

	size_t crypt_g1::enc(std::istream &is, std::ostream &os, unsigned char c)
	{
		long count = 0;
		char g;
		while(is.get(g))
		{
			unsigned char tmp = this->sx->get(g);
    		tmp = tmp ^ this->sx->get(c);
			os << tmp;
			c++;
			count++;
		} 
		return count;
	}

	size_t crypt_g1::dec(std::istream &is, std::ostream &os, unsigned char c)
	{
	    long count = 0;
	    char g;
	    while(is.get(g))
		{
			unsigned char tmp = this->sx->get(c) ^ g;
			tmp = this->sx->getr(tmp);
			os << tmp;
			c++;
			count++;
	    }
		return count;
	}
}
