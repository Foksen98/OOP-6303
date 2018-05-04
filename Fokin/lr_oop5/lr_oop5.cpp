#include <iostream>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0)
        : m_ptr(ptr)
        , m_amount(ptr ? new long(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        this->release();
    }

    shared_ptr(/*const*/ shared_ptr &other)
    {
        this->m_ptr = other.get();
        if (other.use_count())
            ++(*other.m_amount);
        this->m_amount = other.m_amount;
        std::cout << "Конструктор копирования (одинаковые)" << std::endl;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if (this != &other)
        {
            this->release();
            this->m_ptr = other.get();
            if (other.use_count())
                ++(*other.m_amount);
            this->m_amount = other.m_amount;
        }
    }

//  step2
    template <typename Y>
    shared_ptr(shared_ptr<Y> & other)
    {
        this->m_ptr = dynamic_cast<T*>(other.get());
        this->m_amount = other.count_get();
        if (this->m_amount)
            (*(this->m_amount))++;
        std::cout << "Конструктор копирования (разные)" << std::endl;
    }

    template<typename Y>
    shared_ptr& operator=(const shared_ptr<Y> &other)
    {
        this->release();
        this->m_ptr = dynamic_cast<T*>(other.get());
        this->m_amount = other.count_get();
        if (this->m_amount)
            (*(this->m_amount))++;

        return *this;
    }

    explicit operator bool() const
    {
        return (this->m_ptr != nullptr);
    }

    T* get() const
    {
        return this->m_ptr;
    }

    long use_count() const
    {
        return this->m_amount ? *(this->m_amount) : 0;
    }

    long* count_get() const
    {
        return m_amount;
    }

    T& operator*() const
    {
        return *(this->m_ptr);
    }

    T* operator->() const
    {
        return this->m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        T* tempPtr = this->m_ptr;
        long *tempAmount = m_amount;
        this->m_ptr = x.get();
        this->m_amount = x.m_amount;
        x.m_ptr = tempPtr;
        x.m_amount = tempAmount;
    }

    void reset(T *ptr = 0)
    {
        this->release();
        this->m_ptr = ptr;
        this->m_amount = ptr ? new long(1) : nullptr;
    }

  private:
  // data members
      void release()
      {
          if (this->m_amount)
          {
              if (!(--*(this->m_amount)))
              {
                  //delete this->m_ptr;
                  delete this->m_amount;
              }
          }
      }

      T *m_ptr;
      long *m_amount;
  };

    // compare operators
    template <class T, class U>
    bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return lhs.get() == rhs.get();
    }

    template <class T, class U>
    bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return !(lhs == rhs);
    }

    template <class T, class U>
    bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return std::less<T*>()(lhs.get(), rhs.get());
    }

    template <class T, class U>
    bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return !(rhs < lhs);
    }

    template <class T, class U>
    bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return !(lhs < rhs);
    }

    template <class T, class U>
    bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
          return !lhs;
    }

    template <class T>
    bool operator==(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return !rhs;
    }

    template <class T>
    bool operator==(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return (bool)lhs;
    }

    template <class T>
    bool operator!=(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return lhs.get() != rhs;
    }

    template <class T>
    bool operator!=(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return (bool)rhs;
    }

    template <class T>
    bool operator<(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return std::less<T*>()(lhs.get(), nullptr);
    }

    template <class T>
    bool operator<(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return std::less<T*>()(nullptr, rhs.get());
    }

    template <class T>
    bool operator<=(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return nullptr < lhs;
    }

    template <class T>
    bool operator<=(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return rhs < nullptr;
    }

    template <class T>
    bool operator>(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return !(nullptr < lhs);
    }

    template <class T>
    bool operator>(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return !(rhs < nullptr);
    }

    template <class T>
    bool operator>=(const shared_ptr<T>& lhs, std::nullptr_t rhs)
    {
          return !(lhs < nullptr);
    }

    template <class T>
    bool operator>=(std::nullptr_t lhs, const shared_ptr<T>& rhs)
    {
          return !(nullptr < rhs);
    }
    //  end of compare operators

} // namespace stepik


//  my classes
class A
{
public:
    A()
    {
        std::cout << "Конструктор класса A" << std::endl;
    }
    void type()
    {
        std::cout << "Это объект класса A" << std::endl;
    }
};

class B : public A
{
public:
    B() {
        std::cout << "Конструктор класса B" << std::endl;
    }
    void type() {
        std::cout << "Это объект класса B" << std::endl;
    }
};

int main()
{
    //  A
    A *tempA = new A;
    stepik::shared_ptr<A> obj_a(tempA);
    obj_a->type();
    std::cout << obj_a.use_count() << std::endl;

    //  B
    stepik::shared_ptr<B> obj_b(new B);
    obj_b->type();
    std::cout << obj_b.use_count() << std::endl;

    stepik::shared_ptr<A> obj_c(obj_a);
    obj_c->type();
    std::cout << obj_c.use_count() << std::endl;

    stepik::shared_ptr<A> obj_d(obj_b);
    obj_d->type();
    std::cout << obj_d.use_count() << std::endl;

    std::cout << std::endl;
    //  test
    obj_a = obj_b;
    obj_a->type();
    std::cout << obj_a.use_count() << std::endl;
    obj_b->type();
    std::cout << obj_b.use_count() << std::endl;

    std::cout << obj_c.use_count() << std::endl;
    delete tempA;
    std::cout << obj_c.use_count() << std::endl;

    return 0;
}
