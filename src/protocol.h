#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PACKAGE_BUF_SIZE 1024

struct _protocol_ops;
struct _protocol;

typedef struct _protocol_ops{

  // struct _protocol* (*_new)(struct _protocol_ops *_ops);
  // void (*_del)(struct _protocol* _protocol);

  int (*_pack)(struct _protocol* _protocol, void *_content);
  void *(*_unpack)(struct _protocol* _protocol);

  int (*_send)(struct _protocol* _protocol, void* _content, void *_to);
  void* (*_recv)(struct _protocol* _protocol, void *_from);

  int (*_print)(struct _protocol* _protocol);

}protocol_ops_t;

typedef struct _protocol{

  int _package_len;
  uint8_t _package[PACKAGE_BUF_SIZE];
  
  protocol_ops_t *_ops;
}protocol_t;

extern struct _protocol* protocol_new(struct _protocol_ops* _ops);
extern void protocol_del(struct _protocol* _protocol);

extern int protocol_pack(struct _protocol* _protocol, void *_content);
extern void* protocol_unpack(struct _protocol* _protocol);

extern int protocol_send(struct _protocol* _protocol, void* _content, void* _to);
extern void* protocol_recv(struct _protocol* _protocol, void* _from);

extern int protocol_print(struct _protocol* _protocol);

#endif /* __PROTOCOL_H__ */

