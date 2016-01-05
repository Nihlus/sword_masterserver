#ifndef NETWORK_MESSAGES_HPP_INCLUDED
#define NETWORK_MESSAGES_HPP_INCLUDED

#define GAMESERVER_PORT "6950"
#define MASTER_PORT     "6850"

#define MASTER_IP "127.0.0.1"

#include <stdint.h>

namespace message
{
    enum message : int32_t
    {
        DUMMY,
        GAMESERVER,
        CLIENT,
        GAMESERVERUPDATE,
        CLIENTRESPONSE,
        CLIENTJOINREQUEST,
        CLIENTJOINACK,
        FORWARDING
    };
}

#endif // NETWORK_MESSAGES_HPP_INCLUDED
