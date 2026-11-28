# Roadmap — PSBBV Network

## M0 — Contract foundation
- [x] Define the node's domain and its boundary with PSBBV Core.
- [x] Add a versioned node manifest and pinned schema copy.
- [x] Validate the manifest and reject malformed contract fixtures.
- [x] Add identity/readiness regression tests.

## M1 — Portable domain model
- [ ] Define typed records and explicit error/state contracts for network.
- [ ] Add fixture-driven parsers/validators and bounded-input tests.
- [ ] Keep all platform-specific calls behind small adapter interfaces.

## M2 — Vita integration
- [ ] Implement the built-in node against the current Core Node API.
- [ ] Add VitaSDK cross-build and VPK inspection gates.
- [ ] Keep unsupported operations visibly unavailable and fail closed.

## M3 — Hardware qualification
- [ ] Test controller focus, memory use, suspend/resume and error recovery on physical Vita hardware.
- [ ] Test interrupted operations and low-storage/network cases where applicable.
- [ ] Promote manifest availability from planned only after acceptance evidence exists.

## Acceptance
Manifest identity and schema checks pass; capabilities and permissions match the node's domain; host tests cover malformed input and failure states; VitaSDK builds; physical behavior is recorded separately from CI. No commercial content, credentials or unsupported privileged operations are shipped.

## Release target
Remain at the current 0.1.0 / planned baseline until the first portable domain model and Vita integration are both implemented and qualified.
