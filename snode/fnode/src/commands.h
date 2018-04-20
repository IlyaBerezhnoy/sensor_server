#ifndef FNODE_COMMANDS_H
#define FNODE_COMMANDS_H

#define FCMD(a, b, c, d) a | (b << 8) | (c << 16) | (d << 24)
enum
{
    FCMD_HELO = FCMD('H', 'E', 'L', 'O'),
    FCMD_PING = FCMD('P', 'I', 'N', 'G'),
    FCMD_PONG = FCMD('P', 'O', 'N', 'G'),
    FCMD_DATA = FCMD('D', 'A', 'T', 'A')
};

/*
    Device              Controller
    HELO     ->
        SN[8]
        DEV_TYPE[4]
             <-         HELO
                            KEEPALIVE[4]     (mSec)
                            MAX_RESP_FREQ[4] (mSec)

    PING     ->
             <-         PONG

    DATA     ->
        BANK[1]
        VAL[8]
 
    DATA     ->
        BANK[1]
        VAL[8]
             <-         DATA
                            BANK[1]
                            VAL[1024]
 */
#endif
