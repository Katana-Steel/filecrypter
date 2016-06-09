#include "tcp_socket.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>

#define SA sockaddr

namespace xnet {

TCP::TCP(const char *keyname, bool g2)
    : keypos(0)
{
    kname = keyname;
	key = 0;
	if(g2) key = new xcrypter::crypt_g2(kname);
	else   key = new xcrypter::crypt_g1(kname);
    sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sin_len = sizeof(sockaddr_in);
    conn.sin_family = AF_INET;
    fcntl(sd,F_SETFL,O_NONBLOCK);
}

TCP::~TCP()
{
	if(sd>0) close(sd);
	if(key) delete key;
}

void 
TCP::listen(uint16 port)
{
    conn.sin_addr.s_addr = INADDR_ANY;
    conn.sin_port = htons(port);
    bind(sd,(const SA*) &conn, sin_len);
    ::listen(sd, 8);
}

TCP *
TCP::accept(bool g2)
{
    TCP *ret = new TCP(this->kname,g2);
    do {
    ret->sd = ::accept(this->sd,(SA*)&ret->conn,(socklen_t*)&ret->sin_len);
    } while( ret->sd < 0 && errno == EAGAIN);
    return ret;
}

bool
TCP::valid()
{
    return (sd < 0);
}

void
TCP::connect(const char *ip4addr, uint16 port)
{
    conn.sin_port = htons(port);
    inet_aton(ip4addr,&conn.sin_addr);
    if(::connect(sd,(const SA*)&conn,sin_len) != 0)
    { close(sd); sd = -1; } 
}

int 
TCP::write(std::string out)
{
    ss.clear();
    std::stringstream in;
    in << out;
    key->enc(in, ss, keypos);
    return ::send(sd,ss.str().c_str(),ss.str().size(),MSG_NOSIGNAL);
}

std::string
TCP::read(int bytes)
{
    char *cbuff = new char[bytes];
    int left=bytes,r;
    while(left != 0) {
	memset(cbuff,0,bytes);
	r = ::read(sd,cbuff,left);
	if(r == 0) break;
	if(r < 0) {
	    if(errno != EINTR && left != bytes) break;
	}
	ss << cbuff;
	left -= r;
    }
    delete []cbuff;
    std::stringstream out;
    key->dec(ss,out,keypos);
    return out.str();
}

int
TCP::cwrite(std::string out)
{
    return ::send(sd,out.c_str(),out.size(),MSG_NOSIGNAL);
}

std::string
TCP::cread(int bytes)
{
    char *cbuff = new char[bytes];
    int left=bytes,r;
    while(left != 0) {
        memset(cbuff,0,bytes);
        r = ::read(sd,cbuff,left);
	if(r == 0) break;
	if(r < 0) {
	    if(errno != EINTR && left != bytes) break;
	}
        ss << cbuff;
        left -= r;
    }
    delete []cbuff;
    return ss.str();
}

bool
TCP::setKey(const char *keyname)
{
    std::ifstream I(keyname);
    if(I) {
	I.close();
	key->set_key(keyname);
	return true;
    } else {
	return false;
    }
}

void
TCP::setKeyPos(unsigned char kp)
{
    keypos = kp;
}

}
