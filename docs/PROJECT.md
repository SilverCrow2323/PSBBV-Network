# Project: PSBBV Network

## Purpose
Own shared connectivity status, diagnostics and narrowly scoped request adapters. It does not replace the Vita network stack or own global navigation, credentials for unrelated services, or a competing authentication authority.

## Users and use cases
- PlayStation Vita owners using the PSBBV native shell.
- Maintainers integrating a built-in node against the versioned PSBBV Core API.
- Testers validating metadata, failure states and device behavior independently.

## Scope and boundaries
This repository owns the network capability domain. PSBBV Core owns global navigation, focus, lifecycle, permissions, node registration and compatibility policy. No node may silently claim an unimplemented feature or expose unrestricted shell/filesystem access.

## Target and architecture
- Native PS Vita / PS TV, VitaSDK and the PSBBV built-in-node model.
- Portable domain contracts and host-side tests first; platform operations remain behind guarded adapters.
- Manifest: psbbv-node.json. Pinned contract schema: schemas/psbbv-node-manifest.schema.json.
- Tests: schema/manifest checks, domain contract tests, VitaSDK build and physical device qualification when implemented.

## Dependencies and integration
The node consumes the versioned Node API and manifest contract from https://github.com/SilverCrow2323/PSBBV. The local schema is a pinned compatibility copy and must be reconciled with Core changes. No Python runtime or dynamic third-party loader is assumed on Vita.

## Safety, accessibility and localization
Validate metadata and paths, bound reads and allocations, keep operations cancellable, and require explicit confirmation for destructive actions. Keep UI controller-accessible and readable on the Vita display. Technical documentation and UI strings are English.

## Verified baseline
The node manifest is present and declares availability=planned. The current repository status is bootstrap/contract work; future features must not be presented as working until implementation and tests land. The staged delivery plan is in docs/ROADMAP.md.
