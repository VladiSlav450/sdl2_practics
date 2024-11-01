// file: erproc.h
#ifndef ERPROC_SOCK_H
#define ERPROC_SOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <cerrno>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> 

int Main_Init_Server();

int Main_Init_Client();

class Sock_Exception
{
    int err_code;
    char *comment;
public:
    Sock_Exception(const char *cmt);
    Sock_Exception(const Sock_Exception &other);
    ~Sock_Exception();
    
    const char *GetComment_Sock() const { return comment; }
    int GetErrno_Sock() const { return err_code; }
private:
    static char *strdup_sock(const char *str);

};

class Sock_Addr
{
    int sd;
    struct sockaddr_in *address;
public:
    Sock_Addr();
    Sock_Addr(unsigned int port);
    Sock_Addr(const char *ip, unsigned int port);
    ~Sock_Addr();
    
    void set_ip(const char *ip);
    void set_port(unsigned int port) { address->sin_port = htons(port); }
    void set_sd(const int asd) { sd = asd; }
    
    const int &get_sd() const { return sd; }
    struct sockaddr_in *get_addr() const { return address; }
    char *get_ip() { return inet_ntoa(address->sin_addr); }
    unsigned int get_port() { return ntohs (address->sin_port); }
}; 

class Func_Sock_Addr
{
public:
    Func_Sock_Addr(Sock_Addr *addr, int type);
    Func_Sock_Addr() { }
    ~Func_Sock_Addr();
    virtual void Bind(Sock_Addr *addr);
    virtual void Send(Sock_Addr *dest, const char *data, int len, int flags);
    virtual void Recv(Sock_Addr *dest, char *data, int len); 

};

class Serv_Func_Sock_Addr : public Func_Sock_Addr
{
public:
    Serv_Func_Sock_Addr(Sock_Addr *addr, int tp) : Func_Sock_Addr(addr, tp) {}
    ~Serv_Func_Sock_Addr() { }
    virtual void Listen(Sock_Addr *addr, int backlog);
    void Accept(Sock_Addr *addr, Sock_Addr *dest);
};

class Client_Func_Sock_Addr : public Func_Sock_Addr
{
public:
    Client_Func_Sock_Addr(Sock_Addr *addr, int tp) : Func_Sock_Addr(addr, tp) {}
    void Connect(Sock_Addr *dest);

};

char *gitline();

#endif
