#include "psbbv/network/url_policy.h"
#include <string.h>
static int is_alpha(unsigned char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
static int is_digit(unsigned char c) { return c >= '0' && c <= '9'; }
static int is_alnum(unsigned char c) { return is_alpha(c) || is_digit(c); }
static size_t bounded_length(const char *s, size_t limit) {
    size_t n = 0;
    while (n < limit && s[n] != '\0') ++n;
    return n;
}
psbbv_url_result psbbv_network_validate_https_url(const char *url) {
    size_t length, authority_end, host_end, i, label_start;
    unsigned long port = 0;
    int has_dot = 0;
    if (url == NULL || url[0] == '\0') return PSBBV_URL_INVALID_ARGUMENT;
    length = bounded_length(url, PSBBV_NETWORK_URL_MAX + 1u);
    if (length > PSBBV_NETWORK_URL_MAX) return PSBBV_URL_TOO_LONG;
    if (length < 9 || memcmp(url, "https://", 8) != 0) return PSBBV_URL_REQUIRES_HTTPS;
    for (i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)url[i];
        if (c <= 0x20 || c == 0x7f || c == '\\' || c == '#')
            return PSBBV_URL_UNSAFE_CHARACTER;
    }
    authority_end = 8;
    while (authority_end < length && url[authority_end] != '/' && url[authority_end] != '?')
        ++authority_end;
    if (authority_end == 8) return PSBBV_URL_INVALID_AUTHORITY;
    for (i = 8; i < authority_end; ++i)
        if (url[i] == '@' || url[i] == '%' || url[i] == '[' || url[i] == ']')
            return PSBBV_URL_INVALID_AUTHORITY;
    host_end = authority_end;
    for (i = 8; i < authority_end; ++i) {
        if (url[i] == ':') {
            if (host_end != authority_end) return PSBBV_URL_INVALID_PORT;
            host_end = i;
        }
    }
    if (host_end == 8) return PSBBV_URL_INVALID_HOST;
    label_start = 8;
    for (i = 8; i <= host_end; ++i) {
        if (i == host_end || url[i] == '.') {
            size_t label_length = i - label_start;
            if (label_length == 0 || url[label_start] == '-' || url[i - 1] == '-')
                return PSBBV_URL_INVALID_HOST;
            if (i < host_end) has_dot = 1;
            label_start = i + 1;
        } else if (!is_alnum((unsigned char)url[i]) && url[i] != '-') {
            return PSBBV_URL_INVALID_HOST;
        }
    }
    if (!has_dot) return PSBBV_URL_INVALID_HOST;
    if (host_end < authority_end) {
        if (host_end + 1 == authority_end) return PSBBV_URL_INVALID_PORT;
        for (i = host_end + 1; i < authority_end; ++i) {
            if (!is_digit((unsigned char)url[i])) return PSBBV_URL_INVALID_PORT;
            port = port * 10u + (unsigned long)(url[i] - '0');
            if (port > 65535u) return PSBBV_URL_INVALID_PORT;
        }
        if (port == 0) return PSBBV_URL_INVALID_PORT;
    }
    return PSBBV_URL_OK;
}
