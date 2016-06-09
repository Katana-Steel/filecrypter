/****************************************************************
 *   All Rights reserved by René Kjellerup (R)
 *   Compile at own risk for Software as well as Hardware.
 *   You may modify the contens to fit you needs as long as you
 *   include this Licence, along with the original unmodified
 *   source code.
 ****************************************************************/
#include "s-box.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace xcrypter {
using std::ifstream;
using std::ofstream;
using std::ios;

bool not_full(const bool contain[16][16]); // check the sbox's control array where it has been filled or not
bool is_there(const bool contain[16][16],const unsigned char charater[16][16],const unsigned char value); // check the filled fields for a value

box::box(const char *filename)
{
    ifstream I(filename, ios::binary);
    if(I) 
    {
	for(int i = 0; i < 16; i++)
	    for(int j = 0; j < 16; j++)
		sbox[i][j] = I.get();
	
	I.close();
    } else {
	bool bbox[16][16];
	unsigned char val, num1, num2;
	std::srand(std::time(NULL));
	for(int i = 0;i < 16;i++)
	    for(int j = 0;j < 16;j++)
		bbox[i][j] = false;

	while (not_full(bbox))
	{
	    num1 = rand() % 16;
	    num2 = rand() % 16;
	    if(bbox[num1][num2]) continue;
	    do {
		val = rand() % 256;
	    } while (is_there(bbox,sbox,val)); 
	    
	    bbox[num1][num2] = true;
	    sbox[num1][num2] = val;
	}
	ofstream O(filename, ios::binary);
	
	for(int i=0;i<16;i++)
	    for(int j=0;j<16;j++)
		O << sbox[i][j];

	O.close();
    }
}

bool not_full(const bool contain[16][16])
{
  bool full = true;
  for(int i = 0;i < 16;i++)
    {
      for(int j = 0;j < 16;j++)
	{
	  if(!(contain[i][j])) full = false;
	  if(!full) break;
	}
      if(!full) break;
    }
  return !full;
}

bool is_there(const bool contain[16][16], const unsigned char charater[16][16], const unsigned char value)
{
  bool there = false;
  for(int i = 0;i < 16;i++)
    {
      for(int j = 0;j < 16;j++)
	{
	  if(contain[i][j]) 
	    if(charater[i][j] == value) there = true;
	  if(there) break;
	}
      if(there) break;
    }
  return there;
}

unsigned char box::get(unsigned char val)
{
    if((val/16) < 16)
        return sbox[val/16][val%16];
    else
	return sbox[rand()%16][rand()%16];; // this is for the case where you some how fail to provide the function with and appropriat vaiue
}

unsigned char box::getr(unsigned char val)
{
    for(int i = 0; i < 16; i++)
	for(int j = 0; j < 16; j++)
	    if(val == sbox[i][j]) return (unsigned char)((i*16)+j);
    
    return sbox[rand()%16][rand()%16]; // this is for the case where you some how fail to provide the function with and appropriat vaiue
}
}
