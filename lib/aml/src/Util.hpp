#ifndef OPENGL_PLAYGROUND_LIB_AML_SRC_UTIL_HPP
#define OPENGL_PLAYGROUND_LIB_AML_SRC_UTIL_HPP

// Template to only accept the derivation of a specific type
template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;

#endif //OPENGL_PLAYGROUND_LIB_AML_SRC_UTIL_HPP
