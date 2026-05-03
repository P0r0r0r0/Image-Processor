#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

template <typename T>
class Matrix {
public:
    using ValueType = T;
    using SizeType = size_t;
    using Reference = T&;
    using ConstReference = const T&;
    using Pointer = T*;

public:
    Matrix() : ptr_{nullptr}, row_amount_{0}, col_amount_{0} {
    }

    Matrix(size_t row_num, size_t col_num) : Matrix() {
        if (row_num == 0 && col_num == 0) {
            return;
        }
        if (row_num == 0 || col_num == 0) {
            throw std::invalid_argument("Either col or row is null, but not both.");
        }
        ptr_ = new T[row_num * col_num];
        row_amount_ = row_num;
        col_amount_ = col_num;
    }

    Matrix(size_t row_num, size_t col_num, const T& def) : Matrix(row_num, col_num) {
        if (ptr_ == nullptr) {
            return;
        }

        for (size_t i = 0; i < row_num * col_num; ++i) {
            ptr_[i] = def;
        }
    }

    Matrix(const Matrix& other)
        : ptr_(other.ptr_ ? new T[other.row_amount_ * other.col_amount_] : nullptr),
          row_amount_(other.row_amount_),
          col_amount_(other.col_amount_) {
        if (row_amount_ == 0) {
            return;
        }

        for (size_t i = 0; i < row_amount_ * col_amount_; ++i) {
            ptr_[i] = other.ptr_[i];
        }
    }

    ~Matrix() {
        delete[] ptr_;
    }

    Matrix& operator=(const Matrix& rhv) {
        if (this == &rhv) {
            return *this;
        }

        Matrix temp{rhv};
        Swap(temp, *this);

        return *this;
    }

    class Iterator {
    public:
        Iterator() : owner_{nullptr}, pos_{0} {
        }
        Iterator(Matrix* owner, size_t pos) : owner_{owner}, pos_{pos} {
        }

        Reference operator*() {
            return owner_->ptr_[pos_];
        }

        Iterator& operator++() {
            ++pos_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++pos_;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return this->owner_ == other.owner_ && this->pos_ == other.pos_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        Iterator& operator=(const Iterator& other) {
            owner_ = other.owner_;
            pos_ = other.pos_;
            return *this;
        }

    private:
        Matrix* owner_;
        size_t pos_;
    };

    class ConstIterator {
    public:
        ConstIterator() : owner_{nullptr}, pos_{0} {
        }
        ConstIterator(const Matrix* owner, size_t pos) : owner_{owner}, pos_{pos} {
        }

        ConstReference operator*() {
            return owner_->ptr_[pos_];
        }

        ConstIterator& operator++() {
            ++pos_;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++pos_;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return *this == other;
        }

        bool operator!=(const Iterator& other) const {
            return *this != other;
        }

    private:
        const Matrix* owner_;
        size_t pos_;
    };

    Iterator Begin() {
        return Iterator(this, 0);
    }

    Iterator End() {
        return Iterator(this, row_amount_ * col_amount_);
    }

    ConstIterator Begin() const {
        return ConstIterator(this, 0);
    }

    ConstIterator End() const {
        return ConstIterator(this, row_amount_ * col_amount_);
    }

    SizeType Size() const {
        return row_amount_ * col_amount_;
    }

public:
    class Row {
        friend class Matrix;

    public:
        Reference operator[](size_t col) {
            return owner_->GetEl(num_, col);
        }

        ConstReference operator[](size_t col) const {
            return owner_->GetEl(num_, col);
        }

        size_t GetSize() const {
            return owner_->col_amount_;
        }

        size_t GetRowNum() const {
            return num_;
        }

    protected:
        Row(Matrix* owner, size_t num) : owner_{owner}, num_{num} {
        }

    protected:
        Matrix* owner_;
        size_t num_;
    };
    class ConstRow {
        friend class Matrix;

    public:
        ConstReference operator[](size_t col) const {
            return owner_->GetEl(num_, col);
        }

        size_t GetSize() const {
            return owner_->col_amount_;
        }

        size_t GetRowNum() const {
            return num_;
        }

    protected:
        ConstRow(const Matrix* owner, size_t num) : owner_{owner}, num_{num} {
        }

    protected:
        const Matrix* owner_;
        size_t num_;
    };

public:
    class Column {
        friend class Matrix;

    public:
        Reference operator()(size_t row) {
            return owner_->GetEl(row, num_);
        }

        ConstReference operator()(size_t row) const {
            return owner_->GetEl(row, num_);
        }

        size_t GetSize() const {
            return owner_->row_amount_;
        }

        size_t GetColNum() const {
            return num_;
        }

    protected:
        Column(Matrix* owner, size_t num) : owner_{owner}, num_{num} {
        }

    protected:
        Matrix* owner_;
        size_t num_;
    };

    class ConstColumn {
        friend class Matrix;

    public:
        ConstReference operator()(size_t row) const {
            return owner_->GetEl(row, num_);
        }

        size_t GetSize() const {
            return owner_->row_amount_;
        }

        size_t GetColNum() const {
            return num_;
        }

    protected:
        ConstColumn(const Matrix* owner, size_t num) : owner_{owner}, num_{num} {
        }

    protected:
        const Matrix* owner_;
        size_t num_;
    };

public:
    class SquareWindow {
        friend class Matrix;

    public:
        Reference operator()(size_t row, size_t col) {
            ptrdiff_t half_size = size_ / 2;
            ptrdiff_t temp_row = static_cast<ptrdiff_t>(center_row_) - half_size + static_cast<ptrdiff_t>(row);
            ptrdiff_t temp_col = static_cast<ptrdiff_t>(center_col_) - half_size + static_cast<ptrdiff_t>(col);
            size_t correct_row = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_row, static_cast<ptrdiff_t>(owner_->GetRowAmount() - 1)));
            size_t correct_col = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_col, static_cast<ptrdiff_t>(owner_->GetColAmount() - 1)));
            return owner_->GetEl(correct_row, correct_col);
        }

        ConstReference operator()(size_t row, size_t col) const {
            ptrdiff_t half_size = size_ / 2;
            ptrdiff_t temp_row = static_cast<ptrdiff_t>(center_row_) - half_size + static_cast<ptrdiff_t>(row);
            ptrdiff_t temp_col = static_cast<ptrdiff_t>(center_col_) - half_size + static_cast<ptrdiff_t>(col);
            size_t correct_row = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_row, static_cast<ptrdiff_t>(owner_->GetRowAmount() - 1)));
            size_t correct_col = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_col, static_cast<ptrdiff_t>(owner_->GetColAmount() - 1)));
            return owner_->GetEl(correct_row, correct_col);
        }

    public:
        size_t GetCenterRow() const {
            return center_row_;
        }

        size_t GetCenterCol() const {
            return center_col_;
        }

        size_t GetSize() const {
            return size_;
        }

    protected:
        SquareWindow(Matrix* owner, size_t center_row, size_t center_col, size_t size)
            : owner_{owner}, center_row_{center_row}, center_col_{center_col}, size_{size} {
        }

    protected:
        Matrix* owner_;
        size_t center_row_;
        size_t center_col_;
        size_t size_;
    };

    class ConstSquareWindow {
        friend class Matrix;

    public:
        ConstReference operator()(size_t row, size_t col) const {
            ptrdiff_t half_size = size_ / 2;
            ptrdiff_t temp_row = static_cast<ptrdiff_t>(center_row_) - half_size + static_cast<ptrdiff_t>(row);
            ptrdiff_t temp_col = static_cast<ptrdiff_t>(center_col_) - half_size + static_cast<ptrdiff_t>(col);
            size_t correct_row = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_row, static_cast<ptrdiff_t>(owner_->GetRowAmount() - 1)));
            size_t correct_col = std::max(static_cast<ptrdiff_t>(0),
                                          std::min(temp_col, static_cast<ptrdiff_t>(owner_->GetColAmount() - 1)));
            return owner_->GetEl(correct_row, correct_col);
        }

    public:
        size_t GetCenterRow() const {
            return center_row_;
        }

        size_t GetCenterCol() const {
            return center_col_;
        }

        size_t GetSize() const {
            return size_;
        }

    protected:
        ConstSquareWindow(const Matrix* owner, size_t center_row, size_t center_col, size_t size)
            : owner_{owner}, center_row_{center_row}, center_col_{center_col}, size_{size} {
        }

    protected:
        const Matrix* owner_;
        size_t center_row_;
        size_t center_col_;
        size_t size_;
    };

public:
    Row operator[](size_t row) {
        return Row(this, row);
    }

    ConstRow operator[](size_t row) const {
        return ConstRow(this, row);
    }

    Column operator()(size_t col) {
        return Column(this, col);
    }

    ConstColumn operator()(size_t col) const {
        return ConstColumn(this, col);
    }

    SquareWindow GetSquareWindow(size_t center_row, size_t center_col, size_t size) {
        return SquareWindow(this, center_row, center_col, size);
    }

    ConstSquareWindow GetSquareWindow(size_t center_row, size_t center_col, size_t size) const {
        return ConstSquareWindow(this, center_row, center_col, size);
    }

public:
    size_t CalcOffset(size_t i, size_t j) const {
        return i * col_amount_ + j;
    }

    Reference GetEl(size_t i, size_t j) {
        return ptr_[CalcOffset(i, j)];
    }

    ConstReference GetEl(size_t i, size_t j) const {
        return ptr_[CalcOffset(i, j)];
    }

    size_t GetRowAmount() const {
        return row_amount_;
    }

    size_t GetColAmount() const {
        return col_amount_;
    }

    const Pointer GetPointerObject() const {
        return ptr_;
    }

private:
    static void Swap(Matrix& a, Matrix& b) noexcept {
        std::swap(a.ptr_, b.ptr_);
        std::swap(a.row_amount_, b.row_amount_);
        std::swap(a.col_amount_, b.col_amount_);
    }

private:
    T* ptr_;
    size_t row_amount_;
    size_t col_amount_;
};
