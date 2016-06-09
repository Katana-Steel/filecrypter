/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#ifndef _crypt_h
#define _crypt_h 1

#include <iostream>
#include "s-box.h"
namespace xcrypter {

	class crypt
	{
	public:
		virtual ~crypt() {};
		virtual void set_key(const char *key)=0;

		virtual size_t enc(std::istream &is, std::ostream &os, unsigned char c)=0;
		virtual size_t dec(std::istream &is, std::ostream &os, unsigned char c)=0;
	};

	class crypt_g1 : public crypt
	{
		box *sx;
	public:
		crypt_g1(const char *key);
		crypt_g1();
		~crypt_g1();
		void set_key(const char *key);

		size_t enc(std::istream &is, std::ostream &os, unsigned char c);
		size_t dec(std::istream &is, std::ostream &os, unsigned char c);
	};

	class crypt_g2 : public crypt
	{
		box *sx;
	public:
		crypt_g2(const char *key);
	    crypt_g2();
		~crypt_g2();
		void set_key(const char *key);

	    size_t enc(std::istream &is, std::ostream &os, unsigned char c);
		size_t dec(std::istream &is, std::ostream &os, unsigned char c);
	};
}
#endif
