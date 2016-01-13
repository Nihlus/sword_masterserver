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
    tcp_sock sockfd = tcp_host(MASTER_PORT);

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

                while(!fetch.finished())
                {
                    int32_t found_canary = fetch.get<int32_t>();

                    while(found_canary != canary_start && !fetch.finished())
                    {
                        found_canary = fetch.get<int32_t>();
                    }

                    int32_t type = fetch.get<int32_t>();

                    if(type == message::GAMESERVER)
                    {
                        ///the port the server is hosting on, NOT COMMUNICATING WITH ME
                        uint32_t server_port = fetch.get<uint32_t>();

                        int32_t found_end = fetch.get<int32_t>();

                        if(found_end != canary_end)
                            continue;

                        game_server serv = master.server_from_sock(fd, server_port);
                        master.add_server(serv);

                        printf("adding new gameserver\n");

                        sockets.erase(sockets.begin() + i);
                        i--;
                        continue;
                    }

                    if(type == message::CLIENT)
                    {
                        printf("client ping\n");

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
        }

        sf::sleep(sf::milliseconds(1));
    }

    closesocket(sockfd.get());

    for(auto& i : sockets)
        closesocket(i.get());

    return 0;
}
