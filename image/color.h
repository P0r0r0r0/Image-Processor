#pragma once

#include <cstdint>

const double NORM_COEF = 255.0;
const double ROUND_COEF = 0.5;

class Color {
public:
    enum class ErrorCode { Ok, InvalidValue };

public:
    Color() : r_{0.0}, g_{0.0}, b_{0.0} {
    }

    Color(double r, double g, double b, ErrorCode& status) {
        status = Normalize(r, g, b);
    }

    Color(uint8_t r, uint8_t g, uint8_t b) {
        SetFromBytes(r, g, b);
    }

public:
    double GetR() const {
        return r_;
    }

    double GetG() const {
        return g_;
    }

    double GetB() const {
        return b_;
    }

    uint8_t GetRByte() const {
        return static_cast<uint8_t>(r_ * NORM_COEF + ROUND_COEF);  // + 0.5 для верного округления
    }

    uint8_t GetGByte() const {
        return static_cast<uint8_t>(g_ * NORM_COEF + ROUND_COEF);
    }

    uint8_t GetBByte() const {
        return static_cast<uint8_t>(b_ * NORM_COEF + ROUND_COEF);
    }

    ErrorCode SetR(double r) {
        if (r < 0.0 || r > 1.0) {
            return ErrorCode::InvalidValue;
        }
        r_ = r;
        return ErrorCode::Ok;
    }

    ErrorCode SetG(double g) {
        if (g < 0.0 || g > 1.0) {
            return ErrorCode::InvalidValue;
        }
        g_ = g;
        return ErrorCode::Ok;
    }

    ErrorCode SetB(double b) {
        if (b < 0.0 || b > 1.0) {
            return ErrorCode::InvalidValue;
        }
        b_ = b;
        return ErrorCode::Ok;
    }

public:
    ErrorCode Normalize(double r, double g, double b);
    void SetFromBytes(uint8_t r, uint8_t g, uint8_t b);

private:
    double r_;
    double g_;
    double b_;
};
