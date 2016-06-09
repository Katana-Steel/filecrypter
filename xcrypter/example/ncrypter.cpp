// ncrypter.cpp : Defines the entry point for the console application.
//
#include "crypt.h"
#include <fstream>

void usage(void);


int main(int argc, char* argv[])
{
	if((argc > 1) && (6 > argc)) {
		xcrypter::crypt *lib;
		std::ifstream I;
		std::ofstream O;
		if(argv[1][0] == '-') {
			switch(argv[1][1]) {
				case 'c':
					lib = new xcrypter::crypt(argv[2]);
					break;
				case 'e':
					lib = new xcrypter::crypt(argv[2]);
					I.open(argv[3],std::ios::binary);
					O.open(argv[4],std::ios::binary);
					lib->enc(I,O,0);
					O.close();
					I.close();
					break;
				case 'd':
					lib = new xcrypter::crypt(argv[2]);
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
	return 0;
}

