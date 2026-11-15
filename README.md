# PSBBV Network

**SPDW Factory · Connected, without losing control.**

PSBBV Network owns network status, connection workflows and integrations used by PSBBV nodes. It does not replace the Vita system network stack and does not own global shell navigation.

## Scope

- Display Wi-Fi connection state and available system-provided diagnostics.
- Expose a consistent network-status service to Media, Downloads and other nodes.
- Provide reviewed adapters for remote catalogues, transfer endpoints and approved services.
- Surface connection failures, timeouts, retry state and offline availability.
- Centralise endpoint validation and credential handling policy.
- Document integration boundaries with external services such as SPDW Hub where applicable.

## Architecture rules

- Follow the versioned Node API and manifest contract in [PSBBV Core](https://github.com/SilverCrow2323/PSBBV).
- Use documented Vita networking APIs; no assumptions about privileged system access.
- Require TLS certificate and hostname validation for HTTPS. No silent downgrade, insecure certificate bypass or untrusted redirects.
- Store the minimum credentials possible; never write tokens or passwords to logs.
- Bound requests, responses, retries and timeouts. Make network work cancellable and report offline state honestly.
- Do not create a competing service registry or duplicate another project's authentication authority.

## Delivery order

1. Inventory documented Vita networking capabilities and limitations.
2. Define a small typed network-status and request-adapter interface.
3. Add deterministic tests for URL validation, timeout, retry and offline behavior.
4. Integrate Wi-Fi status and shared connectivity state.
5. Add narrowly scoped service adapters only when their security and ownership are clear.
6. Verify DNS, TLS, captive portal, disconnect/reconnect and sleep/resume behavior on hardware.

## Quality gates

Host tests, TLS/URL policy tests, secret-redaction checks, bounded-response tests, VitaSDK build and physical Vita network validation. A successful HTTP request on a desktop does not prove Vita compatibility.

## Status

Repository bootstrap and product boundary only. Planned features are not yet implemented. English UI/docs and SPDW Factory identity are required.
