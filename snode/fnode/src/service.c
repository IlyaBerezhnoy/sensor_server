#include "service.h"
#include "commands.h"
#include <fcommon/log.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    FSVC_INIT = 0
} fnode_service_state_t;

struct fnode_service
{
    volatile int            ref_counter;
    char                    sn[FSN_LENGTH];
    char                    dev_type[FDEV_TYPE_LENGTH];
    fnode_service_state_t   state;
    uint8_t                 pins;
};

fnode_service_t *fnode_service_create(char const sn[FSN_LENGTH], char const dev_type[FDEV_TYPE_LENGTH])
{
    fnode_service_t *svc = malloc(sizeof(fnode_service_t));
    if (!svc)
    {
        FLOG_ERR("Unable to allocate memory for nodes interlink");
        return 0;
    }
    memset(svc, 0, sizeof *svc);
    
    svc->ref_counter = 1;
    memcpy(svc->sn, sn, FSN_LENGTH);
    memcpy(svc->dev_type, dev_type, FDEV_TYPE_LENGTH);
    svc->state = FSVC_INIT;

    return svc;
}

fnode_service_t *fnode_service_retain(fnode_service_t *svc)
{
    if (svc)
        svc->ref_counter++;
    else
        FLOG_ERR("Invalid interlink");
    return svc;
}

void fnode_service_release(fnode_service_t *svc)
{
    if (svc)
    {
        if (!svc->ref_counter)
            FLOG_ERR("Invalid interlink");
        else if (!--svc->ref_counter)
        {
            memset(svc, 0, sizeof *svc);
            free(svc);
        }
    }
    else
        FLOG_ERR("Invalid interlink");
}

void fnode_service_set_state(fnode_service_t *svc, uint8_t pins)
{
    if (svc)
    {
        if (svc->pins != pins)
        {
            // TODO: notify changes
            svc->pins = pins;
        }
    }
}

void fnode_service_reg_handler(fnode_service_t *svc, fnode_service_cmd_handler_t handler)
{
    // TODO
}

void fnode_service_update(fnode_service_t *svc)
{
    if (svc)
    {
        // TODO
    }
}
