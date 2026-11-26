#include "psbbv/network/url_policy.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void) {
    assert(psbbv_network_validate_https_url("https://example.org") == PSBBV_URL_OK);
    assert(psbbv_network_validate_https_url("https://example.org/catalog/index.json") == PSBBV_URL_OK);
    assert(psbbv_network_validate_https_url("https://updates.example.org:443/releases?v=2") == PSBBV_URL_OK);
    assert(psbbv_network_validate_https_url("http://example.org") == PSBBV_URL_REQUIRES_HTTPS);
    assert(psbbv_network_validate_https_url("https://") == PSBBV_URL_INVALID_AUTHORITY);
    assert(psbbv_network_validate_https_url("https://user:pass@example.org") == PSBBV_URL_INVALID_AUTHORITY);
    assert(psbbv_network_validate_https_url("https://example..org") == PSBBV_URL_INVALID_HOST);
    assert(psbbv_network_validate_https_url("https://-bad.example") == PSBBV_URL_INVALID_HOST);
    assert(psbbv_network_validate_https_url("https://example.org:0") == PSBBV_URL_INVALID_PORT);
    assert(psbbv_network_validate_https_url("https://example.org:65536") == PSBBV_URL_INVALID_PORT);
    assert(psbbv_network_validate_https_url("https://example.org/path#fragment") == PSBBV_URL_UNSAFE_CHARACTER);
    assert(psbbv_network_validate_https_url("https://example.org\\@evil.test") == PSBBV_URL_UNSAFE_CHARACTER);
    assert(psbbv_network_validate_https_url(NULL) == PSBBV_URL_INVALID_ARGUMENT);
    {
        char longUrl[PSBBV_NETWORK_URL_MAX + 2u];
        memset(longUrl, 'a', sizeof(longUrl));
        memcpy(longUrl, "https://", 8);
        longUrl[sizeof(longUrl) - 1] = '\0';
        assert(psbbv_network_validate_https_url(longUrl) == PSBBV_URL_TOO_LONG);
    }
    puts("PSBBV Network URL policy tests passed");
    return 0;
}
