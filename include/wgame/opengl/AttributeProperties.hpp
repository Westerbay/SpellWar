/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_ATTRIBUTE_PROPERTIES_H__
#define __WG_ATTRIBUTE_PROPERTIES_H__

#include <glm/glm.hpp>


namespace wgame {

/// Traits structure for attribute properties
template <typename T> struct AttributeProperties {
  static const GLenum typeEnum;   ///< The OpenGL enum representing the type of attributes
  static const GLuint components; ///< the number of components per attribute
};

/// Traits structure for attribute properties (char specialization)
template <> struct AttributeProperties<char> {
  static const GLenum typeEnum = GL_BYTE; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;     ///< the number of components per attribute
};

/// Traits structure for attribute properties (unsigned char specialization)
template <> struct AttributeProperties<unsigned char> {
  static const GLenum typeEnum = GL_UNSIGNED_BYTE; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;              ///< the number of components per attribute
};

/// Traits structure for attribute properties (short specialization)
template <> struct AttributeProperties<short> {
  static const GLenum typeEnum = GL_SHORT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;      ///< the number of components per attribute
};

/// Traits structure for attribute properties (unsigned short specialization)
template <> struct AttributeProperties<unsigned short> {
  static const GLenum typeEnum = GL_UNSIGNED_SHORT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;               ///< the number of components per attribute
};

/// Traits structure for attribute properties (int specialization)
template <> struct AttributeProperties<int> {
  static const GLenum typeEnum = GL_INT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;    ///< the number of components per attribute
};

/// Traits structure for attribute properties (unsigned int specialization)
template <> struct AttributeProperties<unsigned int> {
  static const GLenum typeEnum = GL_UNSIGNED_INT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;             ///< the number of components per attribute
};

/// Traits structure for attribute properties (float specialization)
template <> struct AttributeProperties<float> {
  static const GLenum typeEnum = GL_FLOAT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;      ///< the number of components per attribute
};

/// Traits structure for attribute properties (double specialization)
template <> struct AttributeProperties<double> {
  static const GLenum typeEnum = GL_DOUBLE; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 1;       ///< the number of components per attribute
};

/// Traits structure for attribute properties (glm::vec2 specialization)
template <> struct AttributeProperties<glm::vec2> {
  static const GLenum typeEnum = GL_FLOAT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 2;      ///< the number of components per attribute
};

/// Traits structure for attribute properties (glm::vec3 specialization)
template <> struct AttributeProperties<glm::vec3> {
  static const GLenum typeEnum = GL_FLOAT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 3;      ///< the number of components per attribute
};

/// Traits structure for attribute properties (glm::vec4 specialization)
template <> struct AttributeProperties<glm::vec4> {
  static const GLenum typeEnum = GL_FLOAT; ///< The OpenGL enum representing the type of attribute components
  static const GLuint components = 4;      ///< the number of components per attribute
};

}

#endif 

