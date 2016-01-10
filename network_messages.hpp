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
        FORWARDING,
        REPORT, ///client has something to report to the server
        TEAMASSIGNMENT,
        GAMEMODEUPDATE, ///periodic broadcast of the relevant stats
        RESPAWNREQUEST,
        RESPAWNRESPONSE,
        RESPAWNINFO
    };
}

///canary_start
///message::REPORT
///TYPE
///PLAYERID ///optional?
///LEN
///DATA
///canary_end

namespace report
{
    enum report : int32_t
    {
        DEATH,
        COUNT
    };
}

typedef report::report report_t;

#endif // NETWORK_MESSAGES_HPP_INCLUDED
