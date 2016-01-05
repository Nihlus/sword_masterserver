#include <iostream>
#include <net/shared.hpp>

#include <vector>
#include "server.hpp"
#include "network_messages.hpp"

using namespace std;

std::vector<tcp_sock> sockets;

void cleanup()
{
    for(auto& i : sockets)
        closesocket(i.get());
}


int main()
{
    tcp_sock sockfd = tcp_host();

    ///incase of an unclean exit.
    atexit(cleanup);

    master_server master;

    while(1)
    {
        tcp_sock new_fd = conditional_accept(sockfd);

        ///really... we want to wait for something
        ///to identify as a server, or client
        if(new_fd.valid())
        {
            //game_server serv = master.server_from_sock(new_fd);
            //master.add_server(serv);

            //printf("Yay, new client!\n");

            sockets.push_back(new_fd);
        }

        master.cull_dead();

        //master.tick_all();

        for(int i=0; i<sockets.size(); i++)
        {
            tcp_sock fd = sockets[i];

            if(sock_readable(fd))
            {
                auto data = tcp_recv(fd);

                //if(data.size() == 0 || fd.invalid())
                if(fd.invalid())
                {
                    printf("boo, a client disconnected!\n");

                    sockets.erase(sockets.begin() + i);
                    i--;
                    continue;
                }

                byte_fetch fetch;
                fetch.ptr.swap(data);

                int32_t found_canary = fetch.get<int32_t>();

                if(found_canary != canary_start)
                    continue;

                int32_t type = fetch.get<int32_t>();

                if(type == message::GAMESERVER)
                {
                    int32_t found_end = fetch.get<int32_t>();

                    if(found_end != canary_end)
                        continue;

                    game_server serv = master.server_from_sock(fd);
                    master.add_server(serv);

                    printf("adding new gameserver\n");

                    sockets.erase(sockets.begin() + i);
                    i--;
                    continue;
                }

                if(type == message::CLIENT)
                {
                    int32_t found_end = fetch.get<int32_t>();

                    if(found_end != canary_end)
                        continue;

                    tcp_send(fd, master.get_client_response());

                    fd.close();

                    sockets.erase(sockets.begin() + i);
                    i--;
                    continue;
                }
            }
        }

        /*for(int i=0; i<sockets.size(); i++)
        {
            tcp_sock fd = sockets[i];

            if(sock_readable(fd))
            {
                auto data = tcp_recv(fd);

                if(data.size() == 0 || fd.invalid())
                {
                    printf("boo, a client disconnected!\n");

                    sockets.erase(sockets.begin() + i);
                    i--;
                    continue;
                }

                for(auto& their_fd : sockets)
                {
                    ///do not pipe my data back to me
                    if(fd == their_fd)
                        continue;

                    tcp_send(their_fd, data);
                }
            }
        }*/

        //sf::sleep(sf::milliseconds(1));
    }

    closesocket(sockfd.get());

    for(auto& i : sockets)
        closesocket(i.get());

    return 0;
}
