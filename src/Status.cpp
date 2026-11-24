#include "psbbv/network/Status.hpp"

namespace psbbv::network {

bool is_connected(const ConnectionState state) noexcept {
    return state == ConnectionState::online || state == ConnectionState::limited;
}

bool validate(const Snapshot& snapshot, ValidationError* error) noexcept {
    const auto reject = [error](const ValidationError reason) noexcept {
        if (error != nullptr) {
            *error = reason;
        }
        return false;
    };

    const auto raw_state = static_cast<std::uint8_t>(snapshot.state);
    if (raw_state > static_cast<std::uint8_t>(ConnectionState::limited)) {
        return reject(ValidationError::invalid_state);
    }
    if (snapshot.sequence == 0) {
        return reject(ValidationError::missing_sequence);
    }
    if (snapshot.observed_at_unix_ms == 0) {
        return reject(ValidationError::missing_observation_time);
    }
    if (snapshot.retry_count > kMaxRetryCount) {
        return reject(ValidationError::retry_count_out_of_range);
    }
    if (snapshot.error_code < 0) {
        return reject(ValidationError::negative_error_code);
    }
    if (is_connected(snapshot.state) && snapshot.error_code != 0) {
        return reject(ValidationError::connected_state_has_error_code);
    }

    if (error != nullptr) {
        *error = ValidationError::none;
    }
    return true;
}

std::string_view to_string(const ConnectionState state) noexcept {
    switch (state) {
        case ConnectionState::unknown: return "unknown";
        case ConnectionState::offline: return "offline";
        case ConnectionState::connecting: return "connecting";
        case ConnectionState::online: return "online";
        case ConnectionState::limited: return "limited";
    }
    return "invalid";
}

std::string_view to_string(const ValidationError error) noexcept {
    switch (error) {
        case ValidationError::none: return "none";
        case ValidationError::invalid_state: return "invalid_state";
        case ValidationError::missing_sequence: return "missing_sequence";
        case ValidationError::missing_observation_time: return "missing_observation_time";
        case ValidationError::retry_count_out_of_range: return "retry_count_out_of_range";
        case ValidationError::negative_error_code: return "negative_error_code";
        case ValidationError::connected_state_has_error_code: return "connected_state_has_error_code";
    }
    return "invalid";
}

}  // namespace psbbv::network
