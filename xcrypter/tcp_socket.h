#ifndef __tcp_sock
#define __tcp_sock 1

#include "crypt.h"
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef uint16
typedef unsigned short uint16;
#endif

namespace xnet {

class TCP {
    std::stringstream ss;
    int sd;
    xcrypter::crypt *key;
	unsigned char keypos;
    const char *kname;
    sockaddr_in conn;
    unsigned char sin_len;
public:
    TCP(const char* keyname, bool g2);
    ~TCP();
    void listen(uint16 port);
    TCP* accept(bool);
    void connect(const char *ip4addr, uint16 port);
    bool valid();
    int write(std::string out);
    std::string read(int bytes);
    int cwrite(std::string out);
    std::string cread(int bytes);
    bool setKey(const char *keyname);
    void setKeyPos(unsigned char kp);
};

}
#endif
