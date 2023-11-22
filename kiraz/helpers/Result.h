#ifndef KIRAZ_HELPERS_RESULT_H
#define KIRAZ_HELPERS_RESULT_H

#include <utility>

namespace kiraz {
class Error {};

template <typename R, typename E>
struct Result {
    inline static const auto OK = E();

    Result(const R &r) : result(r) {}
    Result(R &&r) : result(std::move(r)) {}

    Result(const E &e) : error(e) {}
    Result(E &&e) : error(std::move(e)) {}

    template <typename T>
    Result(const T &t) : error(t) {}
    template <typename T>
    Result(T &&t) : error(std::move(t)) {}

    bool is_error() const { return error != OK; }

    bool operator==(const Result<R, E> &other) const {
        return error == other.error && result == other.result;
    }
    bool operator!=(const Result<R, E> &other) const {
        return error != other.error || result != other.result;
    }

    bool operator==(const E &other) const { return error == other; }
    bool operator!=(const E &other) const { return error != other; }

    Result &operator=(const Result<R, E> &) = default;
    Result &operator=(const E &v) {
        this->error = v;
        this->result = {};
        return *this;
    }
    Result &operator=(E &&v) {
        this->error = v;
        this->result = {};
        return *this;
    }

    E error = E();
    R result = R();
};
} // namespace kiraz
#endif
