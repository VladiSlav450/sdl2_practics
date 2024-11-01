// file: fu_errorpoc.cpp

#include "erproc.h"

/* Creating the class that outputs errors */

Sock_Exception::Sock_Exception(const char *cmt)
{
    err_code = errno;
    comment = strdup_sock(cmt);
}

Sock_Exception::Sock_Exception(const Sock_Exception &other)
{
    err_code = other.err_code;
    comment = strdup_sock(other.comment);
}

Sock_Exception::~Sock_Exception()
{
    delete[] comment;
}
    
char* Sock_Exception::strdup_sock(const char *str)
{
    char *res = new char[strlen(str) + 1];
    strcpy(res, str);
    return res;
}


/* Creat and Filling in the struct sockaddr_in */

Sock_Addr::Sock_Addr()
{
    address = new struct sockaddr_in;
    address->sin_family = AF_INET;   
}
    
Sock_Addr::Sock_Addr(unsigned int port)
{
    address = new struct sockaddr_in;
    address->sin_port = htons(port);
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
}

Sock_Addr::Sock_Addr(const char *ip, unsigned int port)
{
    address = new struct sockaddr_in;
    address->sin_port = htons(port);
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = inet_addr(ip);
    if(address->sin_addr.s_addr == INADDR_NONE)
    {
        // delete address;                                 // Possible error, incrompatible with the destructor
        throw Sock_Exception("Socket_Address - the provide IP address seems to be invalid");  
    }
}

Sock_Addr::~Sock_Addr()
{
    delete address;
    close(sd);
}

void Sock_Addr::set_ip(const char *ip)
{
    address->sin_addr.s_addr = inet_addr(ip); 
    if(address->sin_addr.s_addr == INADDR_NONE)
    {
        throw Sock_Exception("Socket_Address - the provide IP address seems to be invalid");  
    }
}

/* Creat Socket and method him */

Func_Sock_Addr::Func_Sock_Addr(Sock_Addr *addr, int type)
{
    int error = socket(AF_INET, type, 0);
    if(error < 0)
    {
        throw Sock_Exception("Error! Could not creat the socket!");
    }
    else
        addr->set_sd(error);
}

Func_Sock_Addr::~Func_Sock_Addr()
{

}

void Func_Sock_Addr::Bind(Sock_Addr *addr)
{
    int error = bind(addr->get_sd(), reinterpret_cast<struct sockaddr *>(addr->get_addr()), sizeof (struct sockaddr_in));
    if(error == -1)
    {   
        throw Sock_Exception("Error! Bind could not socket to a provided name"); 
    }
}

void Func_Sock_Addr::Send(Sock_Addr *dest, const char *data, int len, int flags)
{
    if(dest == NULL || data == NULL)
    {
        throw Sock_Exception("Error! Null pointer passed to Send");
    }
    int error = sendto(dest->get_sd(), data, len, flags, reinterpret_cast<struct sockaddr *>(dest->get_addr()), sizeof(struct sockaddr_in));
    if(error == -1)
    {
        throw Sock_Exception("Error! Sendto could not send data");
    } 
}

void Func_Sock_Addr::Recv(Sock_Addr *dest, char *data, int len)
{
    if(dest == NULL || data == NULL)
    {
        throw Sock_Exception("Error! Null pointer passed to Recv");
    }
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int error = recvfrom(dest->get_sd(), data, len, 0, reinterpret_cast<struct sockaddr *>(dest->get_addr()), &addrlen);

    if(error == -1)
    {
        throw Sock_Exception("Error! Recvfrom could not receive data");
    }
}


/*  Methods of the descendants of the class Func_Sock_Addr */ 

void Serv_Func_Sock_Addr::Listen(Sock_Addr *addr, int backlog)
{
    int error = listen(addr->get_sd(), backlog);
    if(error == -1)
    {
        throw Sock_Exception("Error! Listen could not socket"); 
    }
}

void Serv_Func_Sock_Addr::Accept(Sock_Addr *addr, Sock_Addr *dest)
{
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int error = accept(addr->get_sd(), reinterpret_cast<struct sockaddr *>(dest->get_addr()), &addr_len);
    if(error == -1)
    {
        throw Sock_Exception("Error! Accept create could not socket descriptor");
    }
    dest->set_sd(error);
}



/* Client */


void Client_Func_Sock_Addr::Connect(Sock_Addr *dest)
{
    int error = connect(dest->get_sd(), reinterpret_cast<struct sockaddr *>(dest->get_addr()), sizeof(struct sockaddr_in));
    if(error == -1)
    {
        throw Sock_Exception("Error! Connect could not socket to a client.");        
    }
    
}


char *gitline()
{
    unsigned int buffer_size = 256;
    char *buffer = new char[buffer_size];
    size_t index = 0;
    
    while(true)
    {
        char ch = getchar();
        if(ch == '\n')
        {
            break;
        }
        if(index >= buffer_size - 1)
        {
            buffer_size = buffer_size * 2;
            char *new_buffer = new char[buffer_size];
            strcpy(new_buffer, buffer);
            delete[] buffer;
            buffer = new_buffer;            
        }
        
        buffer[index++] = ch;
    } 
    buffer[index] = '\0';
    return buffer;
} 
