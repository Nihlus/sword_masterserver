#include "server.hpp"
#include "network_messages.hpp"

void master_server::cull_dead()
{
    for(int i=0; i<servers.size(); i++)
    {
        for(int i=0; i<servers.size(); i++)
        {
            tcp_sock fd = servers[i].sock;

            if(sock_readable(fd))
            {
                auto data = tcp_recv(fd);

                if(fd.invalid())
                {
                    servers[i].sock.close();
                }
            }
        }

        if(!servers[i].sock.valid())
        {
            printf("gameserver died\n");

            servers[i].sock.close();

            servers.erase(servers.begin() + i);
            i--;
        }
    }
}

void master_server::tick_all()
{
    for(int i=0; i<servers.size(); i++)
    {
        printf("test tick %i\n", i);
    }
}

game_server master_server::server_from_sock(tcp_sock& sock)
{
    std::string ip = sock.get_peer_ip();

    printf("Ip %s joined\n", ip.c_str());

    ///I need a constructor!
    game_server serv;
    serv.sock = sock;
    serv.address = ip;

    return serv;
}

void master_server::add_server(const game_server& serv)
{
    servers.push_back(serv);
}

std::vector<char> master_server::get_client_response()
{
    byte_vector vec;

    vec.push_back(canary_start);
    vec.push_back(message::CLIENTRESPONSE);

    int32_t server_nums = servers.size();

    vec.push_back(server_nums);

    for(int i=0; i<server_nums; i++)
    {
        std::string ip = servers[i].address;
        int32_t len = ip.length();

        vec.push_back(len);
        vec.push_back<std::string>(ip, len);
    }

    vec.push_back(canary_end);

    return vec.ptr;
}
