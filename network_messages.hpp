#ifndef NETWORK_MESSAGES_HPP_INCLUDED
#define NETWORK_MESSAGES_HPP_INCLUDED

#define GAMESERVER_PORT "6950"
#define MASTER_PORT     "6850"

namespace message
{
    enum message : int32_t
    {
        GAMESERVER,
        CLIENT,
        GAMESERVERUPDATE,
        CLIENTRESPONSE,
        CLIENTJOINREQUEST,
        FORWARDING
    };
}

#endif // NETWORK_MESSAGES_HPP_INCLUDED
