
#include "protocol.h"

struct _protocol* protocol_new(struct _protocol_ops *_ops) {

  struct _protocol* _protocol = malloc(sizeof(struct _protocol));
  if(_protocol) {
    _protocol->_package_len = 0;
    memset(_protocol->_package, 0x00, PACKAGE_BUF_SIZE);
    _protocol->_ops = _ops;
  }
  return _protocol;
}

void protocol_del(struct _protocol* _protocol) {
  if(_protocol) {
    free(_protocol);
  }
}

int protocol_send(struct _protocol* _protocol, void *_to) {

  if(_protocol && _protocol->_ops && _protocol->_ops->_send) {
    return _protocol->_ops->_send(_protocol, _to);
  }
  return 0;
}

int protocol_recv(struct _protocol* _protocol, void *_from) {

  int rc = -1;
  if(_protocol && _protocol->_ops && _protocol->_ops->_recv) {
    rc = _protocol->_ops->_recv(_protocol, _from);
  }
  return rc;
}

int protocol_pack(struct _protocol* _protocol, void *_content) {
  int rc = -1;
  if(_protocol && _protocol->_ops && _protocol->_ops->_pack) {
    rc = _protocol->_ops->_pack(_protocol, _content);
  }
  return rc;
}

void * protocol_unpack(struct _protocol* _protocol) {

  void *content = NULL;
  if(_protocol && _protocol->_ops && _protocol->_ops->_unpack) {
    content = _protocol->_ops->_unpack(_protocol);
  }
  return content;
}

int protocol_print(struct _protocol* _protocol) {
  int ret = -1;
  if(_protocol && _protocol->_ops && _protocol->_ops->_print) {
    ret = _protocol->_ops->_print(_protocol);
  }
  return ret;
}


