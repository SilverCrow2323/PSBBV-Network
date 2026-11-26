#ifndef PSBBV_NETWORK_ENDPOINT_POLICY_H
#define PSBBV_NETWORK_ENDPOINT_POLICY_H
#ifdef __cplusplus
extern "C" {
#endif
typedef enum { PSBBV_ENDPOINT_OK=0, PSBBV_ENDPOINT_EMPTY, PSBBV_ENDPOINT_HTTPS_REQUIRED, PSBBV_ENDPOINT_INVALID_HOST, PSBBV_ENDPOINT_CREDENTIALS_FORBIDDEN, PSBBV_ENDPOINT_CONTROL_CHARACTER } psbbv_endpoint_result;
/* Policy validation only; TLS certificate and hostname verification remain mandatory at transport time. */
psbbv_endpoint_result psbbv_validate_endpoint(const char *url);
#ifdef __cplusplus
}
#endif
#endif
