#include "psbbv/network/Status.hpp"

#include <cstdint>
#include <iostream>

using psbbv::network::ConnectionState;
using psbbv::network::Snapshot;
using psbbv::network::ValidationError;
using psbbv::network::is_connected;
using psbbv::network::to_string;
using psbbv::network::validate;

namespace {

int failures = 0;

void expect(const bool condition, const char* label) {
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

Snapshot valid_snapshot(const ConnectionState state = ConnectionState::online) {
    return Snapshot{state, 1, 1'795'500'000'000ULL, 0, 0};
}

void expect_error(Snapshot snapshot, const ValidationError expected, const char* label) {
    ValidationError actual = ValidationError::none;
    expect(!validate(snapshot, &actual), label);
    expect(actual == expected, "validator returns the expected error code");
}

}  // namespace

int main() {
    for (const auto state : {
             ConnectionState::unknown,
             ConnectionState::offline,
             ConnectionState::connecting,
             ConnectionState::online,
             ConnectionState::limited,
         }) {
        expect(validate(valid_snapshot(state)), "all documented states accept a complete snapshot");
    }

    expect(is_connected(ConnectionState::online), "online is connected");
    expect(is_connected(ConnectionState::limited), "limited is connected");
    expect(!is_connected(ConnectionState::offline), "offline is not connected");
    expect(!is_connected(ConnectionState::connecting), "connecting is not connected");
    expect(to_string(ConnectionState::limited) == "limited", "state names are stable");

    auto snapshot = valid_snapshot();
    snapshot.state = static_cast<ConnectionState>(255);
    expect_error(snapshot, ValidationError::invalid_state, "unknown enum values are rejected");

    snapshot = valid_snapshot();
    snapshot.sequence = 0;
    expect_error(snapshot, ValidationError::missing_sequence, "unpublished sequence is rejected");

    snapshot = valid_snapshot();
    snapshot.observed_at_unix_ms = 0;
    expect_error(snapshot, ValidationError::missing_observation_time, "missing observation time is rejected");

    snapshot = valid_snapshot();
    snapshot.retry_count = psbbv::network::kMaxRetryCount + 1U;
    expect_error(snapshot, ValidationError::retry_count_out_of_range, "retry count is bounded");

    snapshot = valid_snapshot();
    snapshot.error_code = -1;
    expect_error(snapshot, ValidationError::negative_error_code, "negative provider error codes are rejected");

    snapshot = valid_snapshot(ConnectionState::online);
    snapshot.error_code = 7;
    expect_error(snapshot, ValidationError::connected_state_has_error_code,
                 "connected snapshots cannot carry a current failure code");

    ValidationError success_error = ValidationError::invalid_state;
    expect(validate(valid_snapshot(), &success_error), "valid snapshot is accepted");
    expect(success_error == ValidationError::none, "success clears the validation error");
    expect(validate(valid_snapshot(), nullptr), "validation accepts an omitted error output");

    if (failures != 0) {
        std::cerr << failures << " network status contract check(s) failed\n";
        return 1;
    }
    std::cout << "PSBBV Network status contract: all checks passed\n";
    return 0;
}
