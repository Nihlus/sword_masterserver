#ifndef NETWORK_MESSAGES_HPP_INCLUDED
#define NETWORK_MESSAGES_HPP_INCLUDED

namespace message
{
    enum message : int32_t
    {
        GAMESERVER,
        CLIENT,
        GAMESERVERUPDATE,
        CLIENTRESPONSE
    };
}

#endif // NETWORK_MESSAGES_HPP_INCLUDED
