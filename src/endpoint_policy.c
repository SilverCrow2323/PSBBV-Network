#include "psbbv/network/endpoint_policy.h"
#include <stddef.h>
static int is_control_or_space(unsigned char c) { return c<=0x20 || c==0x7f; }
psbbv_endpoint_result psbbv_validate_endpoint(const char *url) {
    const char *host,*end,*p;
    if(!url||!url[0]) return PSBBV_ENDPOINT_EMPTY;
    for(p=url;*p;p++) if(is_control_or_space((unsigned char)*p)) return PSBBV_ENDPOINT_CONTROL_CHARACTER;
    if(url[0]!='h'||url[1]!='t'||url[2]!='t'||url[3]!='p'||url[4]!='s'||url[5]!=':'||url[6]!='/'||url[7]!='/') return PSBBV_ENDPOINT_HTTPS_REQUIRED;
    host=url+8; end=host;
    while(*end&&*end!='/'&&*end!='?'&&*end!='#') end++;
    if(end==host) return PSBBV_ENDPOINT_INVALID_HOST;
    for(p=host;p<end;p++) if(*p=='@') return PSBBV_ENDPOINT_CREDENTIALS_FORBIDDEN;
    if(*host=='.'||end[-1]=='.'||end[-1]==':') return PSBBV_ENDPOINT_INVALID_HOST;
    if(*end=='#') return PSBBV_ENDPOINT_INVALID_HOST;
    return PSBBV_ENDPOINT_OK;
}
