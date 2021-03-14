#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))
#define ARRAY_FILL(array, len, in) for (int i = 0; i < len; i++) array[i] = in

template <class T, size_t N>
struct Array {
    // Storage
    T data[N];

    static size_t length() { return N; }
    using type = T;

    // Item access
    T &operator[](size_t index) { return data[index]; }
    const T &operator[](size_t index) const { return data[index]; }

    // Iterators
    T *begin() { return &data[0]; }
    const T *begin() const { return &data[0]; }
    T *end() { return &data[N]; }
    const T *end() const { return &data[N]; }

    // Comparisons
    bool operator==(const Array<T, N> &rhs) const {
        if (this == &rhs)
            return true;
        for (size_t i = 0; i < N; i++)
            if ((*this)[i] != rhs[i])
                return false;
        return true;
    }
    bool operator!=(const Array<T, N> &rhs) const {
        return !(*this == rhs);
    }
};

#endif