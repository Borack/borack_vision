#ifndef MACROS_HPP
#define MACROS_HPP

#include <iostream>
#include <string>

//! Macro that replaces an input variable to its string representation with the class name as prefix.
//! The intension is that the returned string is unique and can be used for e.g. QSettings.
//! @note This macro might not work with all compilers.
//!
#define VARIABLE_TO_STRING(VARIABLE_NAME)  ({std::string a(typeid(*this).name()); \
                                              a.append("-"); \
                                              a.append(#VARIABLE_NAME); \
                                              a.c_str(); })

#endif // MACROS_HPP
