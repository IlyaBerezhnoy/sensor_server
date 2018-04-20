#ifndef NODE_SERVICE_H
#define NODE_SERVICE_H
#include <fcommon/limits.h>
#include <stdint.h>

typedef struct fnode_service fnode_service_t;

typedef void (*fnode_service_cmd_handler_t)(uint32_t, char const *);

fnode_service_t *fnode_service_create(char const sn[FSN_LENGTH], char const dev_type[FDEV_TYPE_LENGTH]);
fnode_service_t *fnode_service_retain(fnode_service_t *);
void             fnode_service_release(fnode_service_t *);
void             fnode_service_set_state(fnode_service_t *, uint8_t pins);
void             fnode_service_reg_handler(fnode_service_t *, fnode_service_cmd_handler_t);
void             fnode_service_update(fnode_service_t *);

#endif
