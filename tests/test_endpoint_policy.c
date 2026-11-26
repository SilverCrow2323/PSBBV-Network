#include "psbbv/network/endpoint_policy.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    assert(psbbv_validate_endpoint(NULL)==PSBBV_ENDPOINT_EMPTY);
    assert(psbbv_validate_endpoint("")==PSBBV_ENDPOINT_EMPTY);
    assert(psbbv_validate_endpoint("h")==PSBBV_ENDPOINT_HTTPS_REQUIRED);
    assert(psbbv_validate_endpoint("https:/")==PSBBV_ENDPOINT_HTTPS_REQUIRED);
    assert(psbbv_validate_endpoint("http://example.org")==PSBBV_ENDPOINT_HTTPS_REQUIRED);
    assert(psbbv_validate_endpoint("file:///etc/passwd")==PSBBV_ENDPOINT_HTTPS_REQUIRED);
    assert(psbbv_validate_endpoint("https://")==PSBBV_ENDPOINT_INVALID_HOST);
    assert(psbbv_validate_endpoint("https://user:pass@example.org")==PSBBV_ENDPOINT_CREDENTIALS_FORBIDDEN);
    assert(psbbv_validate_endpoint("https://example.org/catalog")==PSBBV_ENDPOINT_OK);
    assert(psbbv_validate_endpoint("https://example.org:8443/api?v=1")==PSBBV_ENDPOINT_OK);
    assert(psbbv_validate_endpoint("https://example.org/#frag")==PSBBV_ENDPOINT_INVALID_HOST);
    assert(psbbv_validate_endpoint("https://example.org/a b")==PSBBV_ENDPOINT_CONTROL_CHARACTER);
    puts("PSBBV endpoint policy tests passed"); return 0;
}
