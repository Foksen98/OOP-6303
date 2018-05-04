#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

using namespace std;

template <class Type>
struct node
{
  Type value;
  node* next;
  node* prev;

  node(const Type& value, node<Type>* next, node<Type>* prev)
    : value(value), next(next), prev(prev)
  {
  }
};

template <class Type>
class list; //forward declaration

template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

//    step3
    list_iterator& operator = (const list_iterator& other)
    {
        m_node = other.m_node;

        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return (m_node == other.m_node);
    }

    bool operator != (const list_iterator& other) const
    {
        return (m_node != other.m_node);
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;

        return *this;
    }

    list_iterator operator ++ (int)
    {
        m_node = m_node->next;

        return *this;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
  };

template <class Type>
class list
{
public:
  typedef Type value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef list_iterator<Type> iterator;

  list()
    : m_head(nullptr), m_tail(nullptr)
  {
  }

  list::iterator begin()
  {
    return iterator(m_head);
  }

  list::iterator end()
  {
    return iterator();
  }

//  step2
  ~list()
  {
      this->clear();
  }

  list(const list& other)
  {
      list *newList = new list;
      node<value_type>* tempNode = other.m_head;
      while (tempNode)
      {
          newList->push_back(tempNode->value);
          tempNode = tempNode->next;
      }
      m_head = newList->m_head;
      m_tail = newList->m_tail;
  }

  list(list&& other)
      : m_head(other.m_head)
      , m_tail(other.m_tail)
  {
      other.m_head = nullptr;
      other.m_tail = nullptr;
  }

  list& operator= (const list& other)
  {
      if (this != &other)
      {
          this->clear();
          node<value_type>* tempNode = other.m_head;
          while (tempNode)
          {
              this->push_back(tempNode->value);
              tempNode = tempNode->next;
          }
      }
  }

//  step4
  iterator insert(iterator pos, const Type& value)
  {
      node<value_type>* newNode = new node<value_type>(value, pos.m_node, pos.m_node->prev);
      if (!pos.m_node->prev)
          m_head = newNode;
      else
          pos.m_node->prev->next = newNode;
      pos.m_node->prev = newNode;
      pos.m_node = newNode;

      return pos;
  }

  iterator erase(iterator pos)
  {
      if (pos.m_node)
      {
         if (pos.m_node == m_head)
         {
             this->pop_front();
             pos.m_node = m_head;
         }
         else if (pos.m_node == m_tail)
         {
             this->pop_back();
             pos = this->end();
         }
         else
         {
             pos.m_node->prev->next = pos.m_node->next;
             pos.m_node->next->prev = pos.m_node->prev;
             node<value_type>* deleteNode = pos.m_node;
             pos.m_node = pos.m_node->next;
             delete deleteNode;
         }
         return pos;
      }

      return this->end();
  }

//  step1
  void push_back(const value_type& value)
  {
      node<value_type>* newNode = new node<value_type>(value, nullptr, m_tail);
      if (m_tail)
          m_tail->next = newNode;
      else
          m_head = newNode;
      m_tail = newNode;
  }

  void push_front(const value_type& value)
  {
      node<value_type>* newNode = new node<value_type>(value, m_head, nullptr);
      if (m_head)
          m_head->prev = newNode;
      else
          m_tail = newNode;
      m_head = newNode;
  }

  reference front()
  {
      return m_head->value;
  }

  const_reference front() const
  {
      return m_head->value;
  }

  reference back()
  {
      return m_tail->value;
  }

  const_reference back() const
  {
      return m_tail->value;
  }

  void pop_front()
  {
      if (m_head)
      {
          node<value_type>* tempNode = m_head->next;
          delete m_head;
          m_head = tempNode;
          if (m_head)
              m_head->prev = nullptr;
          else
              m_tail = nullptr;
      }
  }

  void pop_back()
  {
      if (m_tail)
      {
          node<value_type>* tempNode = m_tail->prev;
          delete m_tail;
          m_tail = tempNode;
          if (m_tail)
              m_tail->next = nullptr;
          else
              m_head = nullptr;
      }
  }

  void clear()
  {
      node<value_type>* tempNode = m_head;
      while (tempNode)
      {
          node<value_type>* deleteNode = tempNode;
          tempNode = tempNode->next;
          delete deleteNode;
      }
      m_head = nullptr;
      m_tail = nullptr;
  }

  bool empty() const
  {
      return (m_head == nullptr);
  }

  size_t size() const
  {
      size_t size = 0;
      node<value_type>* tempNode = m_head;
      while (tempNode)
      {
          ++size;
          tempNode = tempNode->next;
      }

      return size;
  }

//  my functions
//  find element in list
bool find (const Type& value) const
{
    node<value_type>* tempNode = this->m_head;
    while (tempNode)
    {
        if (tempNode->value == value)
            return true;
        tempNode = tempNode->next;
    }

    return false;
}
//  func print list elements
void print()
{
    node<value_type>* tempNode = this->m_head;
    while (tempNode)
    {
        cout << tempNode->value << " ";
        tempNode = tempNode->next;
    }
}
//  sum 2 lists, result in new lists
list sumInNew (const list& other)
{
    list<value_type> newList(*this);
    node<value_type>* iterNode1 = newList.m_head;
    node<value_type>* iterNode2 = other.m_head;
    while (iterNode1 && iterNode2)
    {
        iterNode1->value += iterNode2->value;
        iterNode1 = iterNode1->next;
        iterNode2 = iterNode2->next;
    }

    return newList;
}
//  sum 2 lists, result in list1
void sumInOld (const list& other)
{
    node<value_type>* iterNode1 = this->m_head;
    node<value_type>* iterNode2 = other.m_head;
    while (iterNode1 && iterNode2)
    {
        iterNode1->value += iterNode2->value;
        iterNode1 = iterNode1->next;
        iterNode2 = iterNode2->next;
    }
}
//  logic sub 2 lists, result in new list
list subLogicInNew (const list& other)
{
    list<value_type> newList(*this);
    iterator tempPos = newList.begin();
    while (tempPos.m_node)
    {
        if (!(other.find(tempPos.m_node->value)))
            tempPos = newList.erase(tempPos);
        else
            ++tempPos;
    }

    return newList;
}

private:
  //your private functions

  node<Type>* m_head;
  node<Type>* m_tail;
};

int main ()
{
    //  initialisation
    //  list1
    cout << "Initialisation of lists:" << endl;
    list<int> list1;
    list1.push_back(1);
    list1.push_front(10);
    list1.push_back(15);
    list1.push_front(36);
    list1.push_back(7);
    list1.push_front(405);
    cout << "list1: ";
    list1.print();
    cout << endl;

    //  list2
    list<int> list2;
    cout << "list2: ";
    list2.print();
    cout << endl << endl;

    //  stepik func tests
    cout << "Tests:" << endl;
    list2 = list1;
    cout << "list2 (copied from list1): ";
    list2.print();
    cout << endl;

    list2.insert(list2.begin(), 100);
    cout << "list2 (insert to begin): ";
    list2.print();
    cout << endl;

    list1.erase(list1.begin());
    cout << "list1 (erase from begin): ";
    list1.print();
    cout << endl;

    //  logic sub tests
    list<int> list3 = list1.subLogicInNew(list2);
    cout << "list3 (list1 - list2): ";
    list3.print();
    cout << endl;

    //  sum tests
    //  sumInNew
    list3 = list1.sumInNew(list2);
    cout << "list3 (list1 + list2): ";
    list3.print();
    cout << endl;
    //  sumInOld
    cout << "list1 (list1 + list 3): ";
    list1.sumInOld(list3);
    list1.print();
    cout << endl;


    return 0;
}
