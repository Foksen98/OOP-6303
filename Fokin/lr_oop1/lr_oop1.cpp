#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef>   // size_t

using namespace std;

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

  // lr_oop1
  // Copy constructor
  Array(const Array& other)
    : m_size(other.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
    if (m_array)
      copy(other.m_array.get(), other.m_array.get() + m_size, m_array.get());
  }

  // Copy assignment operator
  Array& operator = (Array other)
  {
    if (this != &other)
    {
        copy(other.m_array.get(), other.m_array.get() + other.m_size, m_array.get());
        m_size = other.m_size;
    }

    return *this;
  }

  // Move constructor
  Array(Array &&other)
    : m_size(0)
    , m_array(nullptr)
  {
    *this = move(other);
    other.m_size = 0;
    other.m_array.release();
  }

  private:
    size_t m_size;
    unique_ptr<T[]> m_array;
};
