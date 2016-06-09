#include "crypt.h"
#include "crypt_g2.h"
#include <vector>

namespace xcrypter {

char *buffer=0;
size_t len;
std::vector<char> filedata;


crypt_g2::crypt_g2(const char *key)
{ 
	this->sx=0; 
	set_key(key); 
}

crypt_g2::crypt_g2()
{ 
	this->sx = 0; 
}

crypt_g2::~crypt_g2()
{
	if(this->sx) delete sx;
	if(filedata.size() > 0) filedata.clear();
	if(buffer) delete[] buffer;
}

void
crypt_g2::set_key(const char *key)
{
  if(this->sx) delete this->sx;
  this->sx = new box(key);
  ::GetSBox(this->sx);
}

size_t
crypt_g2::enc(std::istream &is, std::ostream &os, unsigned char c)
{
  char g;
  // starts to load the IStream into the buffer
  filedata.clear();
  while(is.get(g))
    filedata.push_back(g);

  len = filedata.size();
  buffer = new char[len+4];
  memset(buffer,0,len+4);

  for(int i=0;i<len;i++)
    buffer[i] = filedata.at(i);

  // starting the algorithem
  for(int i=0;i<len;i++) {
	  buffer[i] = ::Encrypt(buffer[i],(c+i)%256);
	::SRotateR(3,buffer,len);
  }
  for(int i=0;i<len;i++)
    os << buffer[i];

  os.flush();
  delete[] buffer;
  buffer=0;
  return len;
}

size_t
crypt_g2::dec(std::istream &is, std::ostream &os, unsigned char c)
{
  char g;
  // starts to load the IStream into the buffer
  filedata.clear();
  while(is.get(g))
    filedata.push_back(g);

  len = filedata.size();
  buffer = new char[len+4];
  memset(buffer,0,len+4);

  for(int i=0;i<len;i++)
    buffer[i] = filedata.at(i);

  // starting the algorithem
  for(int i=len;i>0;i--) {
	::SRotateL(3,buffer,len);
	buffer[i-1] = ::Decrypt(buffer[i-1],((i+c)-1)%256);
  }
  for(int i=0;i<len;i++)
    os << buffer[i];

  os.flush();
  delete[] buffer;
  buffer=0;
  return len;
}

}
