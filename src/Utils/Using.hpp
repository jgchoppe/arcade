//
// Created by Jean-Gaël Choppe on 18/03/2020.
//

#ifndef USING_HPP
#define USING_HPP

#include <iostream>
#include <memory>
#include <string>

template <typename T>
using u_ptr = std::unique_ptr<T>;
template <typename T>
using s_ptr = std::shared_ptr<T>;

#endif /* USING_HPP */