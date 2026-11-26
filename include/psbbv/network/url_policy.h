#ifndef PSBBV_NETWORK_URL_POLICY_H
#define PSBBV_NETWORK_URL_POLICY_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
#define PSBBV_NETWORK_URL_MAX 2048u
typedef enum {
    PSBBV_URL_OK = 0, PSBBV_URL_INVALID_ARGUMENT, PSBBV_URL_TOO_LONG,
    PSBBV_URL_REQUIRES_HTTPS, PSBBV_URL_INVALID_AUTHORITY, PSBBV_URL_INVALID_HOST,
    PSBBV_URL_INVALID_PORT, PSBBV_URL_UNSAFE_CHARACTER
} psbbv_url_result;
/* Syntax gate only; DNS, TLS and certificate validation belong to the network adapter. */
psbbv_url_result psbbv_network_validate_https_url(const char *url);
#ifdef __cplusplus
}
#endif
#endif
