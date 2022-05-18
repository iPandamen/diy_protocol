
#include <stdio.h>
#include <string.h>

#include "../src/protocol.h"

#include "../..//cJSON/cJSON.h"

int test_protocol_pack(struct _protocol* _protocol, void *_content) {

  cJSON* json = _content;
  if(json) {
    cJSON_PrintPreallocated(json, (char *)_protocol->_package, PACKAGE_BUF_SIZE, 0);
    _protocol->_package_len = strlen((char *)_protocol->_package);
  }
  return _protocol->_package_len;
}
void *test_protocol_unpack(struct _protocol* _protocol) {
  cJSON* json = NULL;
  if(_protocol) {
    json = cJSON_Parse((char *)_protocol->_package);
  }
  return json;
}

int test_protocol_send(struct _protocol* _protocol, void* _content, void *_to) {

  return 0;
}

void* test_protocol_recv(struct _protocol* _protocol, void *_from) {

  return 0;
}

int test_protocol_print(struct _protocol* _protocol) {
  printf("===> %s, _package: %s\n", __FUNCTION__, _protocol->_package);
  return 0;
}

protocol_ops_t test_protocol_ops = {
  ._send = test_protocol_send,
  ._recv = test_protocol_recv,
  ._pack = test_protocol_pack,
  ._unpack = test_protocol_unpack,
  ._print = test_protocol_print
};



int main(void) {

  cJSON* json = cJSON_CreateObject();
  if(json) {

    cJSON_AddStringToObject(json, "msg", "Hello world");

    protocol_t *_protocol = protocol_new(&test_protocol_ops);
    if(_protocol) {
      printf("packing...\n");
      protocol_pack(_protocol, json);

      printf("printing...\n");
      protocol_print(_protocol);

      protocol_del(_protocol);
    }

    cJSON_Delete(json);
  }
  return 0;
}
