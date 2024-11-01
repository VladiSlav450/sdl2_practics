// file: server.cpp

#include "erproc.h"

int Main_Init_Server()
{
    try
    {
        Sock_Addr *serv_addr = new Sock_Addr(8080);
        Sock_Addr *one_client_addr = new Sock_Addr();
        Sock_Addr *two_client_addr = new Sock_Addr();
        
        Serv_Func_Sock_Addr *sock_serv = new Serv_Func_Sock_Addr(serv_addr, SOCK_STREAM);   
        sock_serv->Bind(serv_addr);
        unsigned int size_buffer = 256;
        char *buf = new char[size_buffer];
        int flags = 0;
        
        sock_serv->Listen(serv_addr, 10);
        sock_serv->Accept(serv_addr, one_client_addr); 
        sock_serv->Accept(serv_addr, two_client_addr); 
        
        sock_serv->Serv_Func_Sock_Addr::Recv(one_client_addr, buf, size_buffer);
        printf("Received one client message\nsource IP: %s\n source PORT: %d\nmessage: %s\n", one_client_addr->get_ip(), one_client_addr->get_port(), buf);

        sock_serv->Serv_Func_Sock_Addr::Recv(two_client_addr, buf, size_buffer);
        printf("Received two client message\nsource IP: %s\nsource PORT: %d\nmessage: %s\n", two_client_addr->get_ip(), two_client_addr->get_port(), buf);

        while(one_client_addr || two_client_addr)
        { 
            if(one_client_addr)
            {
                sock_serv->Func_Sock_Addr::Recv(one_client_addr, buf, size_buffer);
                printf("Message from one client: %s\n", buf);
                sock_serv->Func_Sock_Addr::Send(two_client_addr, buf, size_buffer, flags);
                if(strcmp(buf, "exit") == 0)
                {
                    delete one_client_addr;
                    one_client_addr = NULL;
                } 
            }
            
            if(two_client_addr)
            {
                sock_serv->Func_Sock_Addr::Recv(two_client_addr, buf, size_buffer);
                printf("Message from two client: %s\n", buf);
                sock_serv->Func_Sock_Addr::Send(one_client_addr, buf, size_buffer, flags);
                if(strcmp(buf, "exit") == 0)
                {
                    delete two_client_addr;
                    two_client_addr = NULL;
                }
            }
        }
 
        if(one_client_addr)
            delete one_client_addr;
        if(two_client_addr)
            delete two_client_addr;
        delete serv_addr;
        delete sock_serv;
        delete[] buf; 
     }     
    catch (const Sock_Exception &err)
    {
        fprintf(stderr, "Failed initialize: %s: %s\n", err.GetComment_Sock(), strerror(err.GetErrno_Sock()));
        return 1;
    }
    catch(...)
    {
        fprintf(stderr, "Unkown error.\n");
        return 1;
    }
    return 0;
}

