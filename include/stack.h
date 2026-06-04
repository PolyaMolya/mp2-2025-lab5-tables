// объявление и реализация шаблонного стека
// стек поддерживает операции:
// - вставка элемента,
// - извлечение элемента,
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту,
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef STACK_H
#define STACK_H

#include <algorithm>
#include <stdexcept>
#include <string>

template <typename T> class Stack {
private:
  T *data;
  size_t capacity;
  size_t topIndex;

  void resize() {
    size_t newCapacity = capacity == 0 ? 2 : capacity * 2;
    T *newData = new T[newCapacity];
    for (size_t i = 0; i < topIndex; i++)
      newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCapacity;
  }

public:
  Stack() : data(nullptr), capacity(0), topIndex(0) {}

  Stack(const Stack &other)
      : capacity(other.capacity), topIndex(other.topIndex) {
    data = new T[capacity];
    for (size_t i = 0; i < topIndex; i++)
      data[i] = other.data[i];
  }

  Stack &operator=(const Stack &other) {
    if (this != &other) {
      delete[] data;
      capacity = other.capacity;
      topIndex = other.topIndex;
      data = new T[capacity];
      for (size_t i = 0; i < topIndex; i++)
        data[i] = other.data[i];
    }
    return *this;
  }

  ~Stack() {
    delete[] data;
    data = nullptr;
    capacity = 0;
    topIndex = 0;
  }

  void push(const T &value) {
    if (topIndex >= capacity)
      resize();
    data[topIndex++] = value;
  }

  T pop() {
    if (isEmpty())
      throw std::out_of_range("Stack is empty");
    return data[--topIndex];
  }

  T &peek() const {
    if (isEmpty())
      throw std::out_of_range("Stack is empty");
    return data[topIndex - 1];
  }

  bool isEmpty() const { return topIndex == 0; }

  size_t size() const { return topIndex; }

  void clear() { topIndex = 0; }

  size_t getCapacity() const { return capacity; }
};

#endif