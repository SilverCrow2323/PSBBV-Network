# Network status contract

The first implementation milestone is a portable, read-only status model. It deliberately does not probe the Vita network stack or open sockets; those responsibilities belong to a later adapter built against documented VitaSDK APIs.

## State model

| State | Meaning |
|---|---|
| \`unknown\` | No trustworthy observation is available yet |
| \`offline\` | The provider has observed no usable network connection |
| \`connecting\` | A connection attempt is in progress |
| \`online\` | The provider reports a usable connection |
| \`limited\` | A link exists, but the provider reports restricted upstream reachability |

A snapshot carries a non-zero sequence number, a non-zero UTC observation timestamp in Unix milliseconds, a bounded retry count and a normalized non-negative provider error code. Connected states (\`online\` and \`limited\`) must not carry a current failure code. Unknown enum values and incomplete snapshots fail validation.

## Privacy boundary

The portable contract contains no SSID, IP address, MAC address, account, password, token, raw exception text or device serial. Those values are not needed for the shared connection state and must not be smuggled into the error code. A future diagnostics surface must request any additional data through a separate, explicitly authorized capability and redact it before export.

The model does not perform DNS, TLS, captive-portal, timeout or retry operations. It provides bounded state vocabulary for those adapters to report; it is not evidence that any network operation has succeeded.

## Build and test

The host contract is C++17 and has no VitaSDK or third-party runtime dependency:

\`\`\`sh
cmake -S . -B build -DPSBBV_NETWORK_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
\`\`\`

CI compiles with warnings treated as errors and runs the deterministic state/validation tests. This does not certify VitaSDK integration or physical Vita Wi-Fi behavior.

## Next gate

Implement a cancellable provider adapter using documented Vita networking APIs, then add deterministic URL/TLS policy, timeout, retry and offline fixtures. Only after a VitaSDK build and device checks for DNS, TLS, captive portals, disconnect/reconnect and suspend/resume should the manifest move from \`planned\` to \`ready\`.
