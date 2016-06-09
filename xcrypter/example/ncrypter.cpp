// ncrypter.cpp : Defines the entry point for the console application.
//
#include "crypt.h"
#include <fstream>

void usage(void);

// using xcrypter::crypt;

int main(int argc, char* argv[])
{
    try {
	if((argc > 1) && (6 > argc)) {
		xcrypter::crypt *lib=0;
		std::ifstream I;
		std::ofstream O;
		if(argv[1][0] == '-') {
			switch(argv[1][1]) {
				case 'c':
					lib = new xcrypter::crypt_g2(argv[2]);
					break;
				case 'e':
					if(argv[1][2] != 0)
						if(argv[1][2] == '1') 
							lib = new xcrypter::crypt_g1(argv[2]);
						else
							lib = new xcrypter::crypt_g2(argv[2]);
					else
						lib = new xcrypter::crypt_g2(argv[2]);
					I.open(argv[3],std::ios::binary);
					O.open(argv[4],std::ios::binary);
					lib->enc(I,O,0);
					O.close();
					I.close();
					break;
				case 'd':
					if(argv[1][2] != 0)
						if(argv[1][2] == '1') 
							lib = new xcrypter::crypt_g1(argv[2]);
						else
							lib = new xcrypter::crypt_g2(argv[2]);
					else
						lib = new xcrypter::crypt_g2(argv[2]);
					I.open(argv[3],std::ios::binary);
					O.open(argv[4],std::ios::binary);
					lib->dec(I,O,0);
					O.close();
					I.close();
					break;
				default:
					usage();
					break;
			}
			if(lib) delete lib;
			return 0;
		}
	}
	usage();
    }
    catch(const std::exception &)
    {
	usage();
    }
	return 0;
}

