#include "erproc.h"

int Main_Init_Client()
{
    try
    {
        Sock_Addr *client_addr = new Sock_Addr(8080);
        Sock_Addr *dest_addr = new Sock_Addr();

        Client_Func_Sock_Addr *sock_client = new Client_Func_Sock_Addr(client_addr, SOCK_STREAM); 
        
        unsigned int buffer_size = 256;
        char *buf = new char[buffer_size];
        sock_client->Connect(client_addr);        
        sock_client->Send(client_addr, buf, strlen(buf) + 1, 0);

        while(1)
        {
            printf("Your message: ");
            buf = gitline();     
            sock_client->Send(client_addr, buf, strlen(buf) + 1, 0);

            sock_client->Func_Sock_Addr::Recv(client_addr, buf, buffer_size);
            printf("From: %s\n", buf);
            if(strcmp(buf, "exit") == 0)
            {
                break;
            }
        }
            
        delete client_addr;
        delete sock_client;
        delete[] buf;
    }
    catch(const Sock_Exception &err)
    {
        fprintf(stderr, "Failed initialize: %s: %s\n", err.GetComment_Sock(), strerror(err.GetErrno_Sock()));
        return 1;
    } 
    catch(...)
    {
        fprintf(stderr, "Error xyi ego znaet(\n");
        return 1;
    }
    return 0;
}
