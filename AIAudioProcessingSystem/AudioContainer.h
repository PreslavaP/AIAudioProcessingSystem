#pragma once
#include <stdexcept>
#include <utility>

template <typename T>

class AudioContainer {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    AudioContainer() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    //Деструктор
    ~AudioContainer() {
        delete[] data;
    }

    //Конструктор за копиране
    AudioContainer(const AudioContainer& other) {
        size = other.size;
        capacity = other.capacity;

        if (other.data != nullptr) {
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    //Оператор за присвояване чрез копиране
    AudioContainer& operator=(const AudioContainer& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        size = other.size;
        capacity = other.capacity;

        if (other.data != nullptr) {
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }

        return *this;
    }

    //Конструктор за преместване
    AudioContainer(AudioContainer&& other) noexcept {
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    //Местящ оператор за присвояване
    AudioContainer& operator=(AudioContainer&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;

        return *this;
    }

    //Помощни методи
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }

    //Оператор за достъп по индекс (за четене и промяна)
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index is out of container bounds!");
        }
        return data[index];
    }

    //Константна версия на оператора за достъп (само за четене)
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index is out of container bounds!");
        }
        return data[index];
    }

    void push_back(const T& item) {
        if (size >= capacity) {
            size_t newCapacity;
            if (capacity == 0) {
                newCapacity = 2;
            }
            else {
                newCapacity = capacity * 2;
            }

            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size; ++i) {
                newData[i] = std::move(data[i]);
            }

            delete[] data;

            data = newData;
            capacity = newCapacity;
        }

        data[size] = item;
        size++;
    }

    void clear() {
        delete[] data;
        capacity = 2;
        size = 0;
        data = new T[capacity];
    }

    void remove(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            size--;
        }
    }
};