class A
{
public:
  A() {};

private:
  // some resources
  A(const A&) = delete;
  void operator=(const A&) = delete;
};
