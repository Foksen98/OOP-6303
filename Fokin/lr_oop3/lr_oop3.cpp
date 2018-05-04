#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>

//namespace stepik
//{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

//  step1
    explicit vector(size_t count = 0)
        : m_first(count ? new value_type[count] : nullptr)
        , m_last(count ? (m_first + count) : nullptr)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        difference_type size = last - first;
        m_first = new value_type[size];
        m_last = (m_first + size);
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
        : m_first(init.size() ? new value_type[init.size()] : nullptr)
        , m_last(m_first ? (m_first + init.size()) : nullptr)
    {
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other)
        : m_first(!(other.empty()) ? new value_type[other.size()] : nullptr)
        , m_last(!(other.empty()) ? (m_first + other.size()) : nullptr)
    {
        std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other)
        : m_first(other.begin())
        , m_last(other.end())
    {
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete [] m_first;
    }


    //assignment operators
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            delete [] m_first;
            m_first = !(other.empty()) ? new value_type[other.size()] : nullptr;
            m_last = !(other.empty()) ? (m_first + other.size()) : nullptr;
            std::copy(other.begin(), other.end(), m_first);
        }

        return *this;
    }

    vector& operator=(vector&& other)
    {
        if (this != &other)
        {
            delete [] m_first;
            m_first = other.begin();
            m_last = other.end();
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete [] m_first;
        difference_type size = last - first;
        m_first = new value_type[size];
        m_last = (m_first + size);
        std::copy(first, last, m_first);
    }

//  step3
    // resize methods
    void resize(size_t count)
    {
        iterator newFirst = count ? new value_type[count] : nullptr;
        std::copy(m_first, ((size() > count) ? (m_first + count) : m_last), newFirst);
        delete [] m_first;
        m_first = newFirst;
        m_last = m_first + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        if ((pos >= m_first) && (pos <= m_last))
        {
            difference_type delta = pos - m_first;
            if (pos != m_last)
                std::rotate((m_first + delta), (m_first + delta + 1), m_last);
            resize(size() - 1);

            return (m_first + delta);
        }

        return nullptr;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if ((first >= m_first) && (first <= m_last) && (last >= m_first) && (last <= m_last))
        {
            difference_type delta = first - m_first;
            difference_type size = last - first;
            std::rotate((m_first + delta), (m_first + delta + size), m_last);
            resize(this->size() - size);

            return (m_first + delta);
        }

        return nullptr;
    }
// step4
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        if ((pos >= m_first) && (pos <= m_last))
        {
            difference_type delta = pos - m_first;
            push_back(value);
            std::rotate((m_first + delta), (m_last - 1), m_last);

            return (m_first + delta);
        }

        return nullptr;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        if ((pos >= m_first) && (pos <= m_last))
        {
            difference_type delta = pos - m_first;
            difference_type size = last - first;
            resize(this->size() + size);
            std::copy(first, last, (m_last - size));
            std::rotate((m_first + delta), (m_last - size), m_last);

            return (m_first + delta);
        }

        return nullptr;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        resize(size() + 1);
        *(m_last - 1) = value;
    }


    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }
//  idz
    vector sum1(vector v2)
    {
        vector sum_v;
        for (int i = 0; i < size(); ++i)
            if ((i < size()) & (i < v2.size()))
                sum_v.push_back(*(m_first + i) + *(v2.begin() + i));
            else
                break;

        return sum_v;
    }

    vector sub1(vector v2)
    {
        vector sub_v;
        for (int i = 0; i < size(); ++i)
            if ((i < size()) & (i < v2.size()))
                sub_v.push_back(*(m_first + i) - *(v2.begin() + i));
            else
                break;

        return sub_v;
    }

    void sum2(vector v2)
    {
        vector sum_v;
        for (int i = 0; i < size(); ++i)
            if ((i < size()) & (i < v2.size()))
                sum_v.push_back(*(m_first + i) + *(v2.begin() + i));
            else
                break;

        std::copy(sum_v.begin(), sum_v.end(), m_first);
        resize(sum_v.size());
    }

    void sub2(vector v2)
    {
        vector sub_v;
        for (int i = 0; i < size(); ++i)
            if ((i < size()) & (i < v2.size()))
                sub_v.push_back(*(m_first + i) - *(v2.begin() + i));
            else
                break;

        std::copy(sub_v.begin(), sub_v.end(), m_first);
        resize(sub_v.size());
    }


    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
//}// namespace stepik

int main ()
{
    vector<int> my_v = {1, 2, 3, 4, 5, 34};
    vector<int> my2_v = {-1, -2, -3, -4, -10};

    std::cout << "My vector:" << std::endl;
    for (int i : my_v)
        std::cout << i << '\n';

    std::cout << "My vector2:" << std::endl;
    for (int i : my2_v)
        std::cout << i << '\n';
//
//
    vector<int> sum1_v = my_v.sum1(my2_v);
    std::cout << "Sum1 vector:" << std::endl;
    for (int i : sum1_v)
        std::cout << i << '\n';

    vector<int> sub1_v = my_v.sub1(my2_v);
    std::cout << "Sub1 vector:" << std::endl;
    for (int i : sub1_v)
        std::cout << i << '\n';

    my_v.sum2(my2_v);
    std::cout << "Sum2 vector:" << std::endl;
    for (int i : my_v)
        std::cout << i << '\n';

    my_v.sub2(my2_v);
    std::cout << "Sub2 vector:" << std::endl;
    for (int i : my_v)
        std::cout << i << '\n';
}
