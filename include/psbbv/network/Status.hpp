#pragma once

#include <cstdint>
#include <string_view>

namespace psbbv::network {

enum class ConnectionState : std::uint8_t {
    unknown = 0,
    offline = 1,
    connecting = 2,
    online = 3,
    limited = 4,
};

enum class ValidationError : std::uint8_t {
    none = 0,
    invalid_state,
    missing_sequence,
    missing_observation_time,
    retry_count_out_of_range,
    negative_error_code,
    connected_state_has_error_code,
};

struct Snapshot {
    ConnectionState state{ConnectionState::unknown};
    std::uint64_t sequence{0};
    std::uint64_t observed_at_unix_ms{0};
    std::uint32_t retry_count{0};
    std::int32_t error_code{0};
};

inline constexpr std::uint32_t kMaxRetryCount = 1'000'000U;

[[nodiscard]] bool is_connected(ConnectionState state) noexcept;
[[nodiscard]] bool validate(
    const Snapshot& snapshot,
    ValidationError* error = nullptr
) noexcept;
[[nodiscard]] std::string_view to_string(ConnectionState state) noexcept;
[[nodiscard]] std::string_view to_string(ValidationError error) noexcept;

}  // namespace psbbv::network
