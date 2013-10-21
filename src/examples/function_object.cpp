#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

// 将单参数函数封装成函数对象的封装类模板
template<typename T, typename RetT>
struct unary_func
{
  typedef T param_type;         // 参数类型
  typedef RetT return_type;     // 返回值类型
  typedef return_type (*func_type)(param_type); // 函数指针类型
  func_type func_ptr;                           // 所封装的函数指针
  unary_func(func_type func_ptr) : func_ptr(func_ptr) {}
  // 重载的括号操作符，直接调用所封装的函数。
  return_type operator() (param_type v) {return func_ptr(v);}
};

// 生成封装类的助手函数模板
template<typename T, typename RetT>
unary_func<T, RetT> unary(RetT (*func_ptr)(T))
{
  return unary_func<T, RetT>(func_ptr);
}

// 连锁调用两个单参数函数的函数对象
template<typename Func0,        // Func0与Func1为所调用的函数对象类型。
         typename Func1>
struct chain_func
{
  // 按照约定提取出函数对象的参数类型和返回值类型
  typedef typename Func0::return_type return_type;
  typedef typename Func1::param_type param_type;
  Func0 func0;                  // 所复用的函数对象
  Func1 func1;
  chain_func(Func0 func0, Func1 func1) : func0(func0), func1(func1) {}
  // 重载的括号操作符，连锁调用func1与func0
  return_type operator() (param_type v) {return func0(func1(v));}
};

// 生成连锁调用函数对象的助手函数模板
template<typename Func0, typename Func1>
chain_func<Func0, Func1> chain(Func0 func_ptr0, Func1 func_ptr1)
{
  return chain_func<Func0, Func1>(func_ptr0, func_ptr1);
}

double root3(int v) {return pow(v, -3);}
double root4(int v) {return pow(v, -4);}

std::string double_to_string(double v)
{
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

void test_chain()
{
  typedef unary_func<double, int>
  unary_func<double, int> r3 = 
  std::cout << chain(unary(double_to_string), unary(root3))(3) << std::endl
            << chain(unary(double_to_string), unary(root4))(3) << std::endl;
}
int main()
{
  test_chain();
  return 0;
}
