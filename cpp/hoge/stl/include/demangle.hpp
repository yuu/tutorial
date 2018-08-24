// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_DEMANGLE_HPP)
#define SSCRISK_DEMANGLE_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// demangle.hpp

#include<string>
#include<memory>
#include<new>
#include<stdexcept>
#include<typeinfo>
#include<cstdlib>
#include<cxxabi.h>

namespace sscrisk{

 std::string demangle(char const * mangled_name)
 {
  int status;
  std::unique_ptr<char, void (*)(void*)> p(abi::__cxa_demangle(mangled_name, 0, 0, &status), std::free);
  switch(status)
  {
  case 0: return std::string(p.get());
  case -1: throw std::bad_alloc();
  case -2: throw std::invalid_argument("mangled_name is not a valid name under the C++ ABI mangling rules.");
  case -3: throw std::invalid_argument("One of the arguments is invalid.");
  default: throw std::logic_error("abi::__cxa_demangle status is unknown.");
  }
 }

 template<class T>
 std::string demangle()
 {
  return demangle(typeid(T).name());
 }

 std::string demangle(std::type_info const & ti)
 {
  return demangle(ti.name());
 }

}

#define SSCRISK_DEMANGLE(expression) demangle(typeid(expression))

#endif
