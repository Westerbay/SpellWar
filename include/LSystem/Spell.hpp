/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __SPELL_H__
#define __SPELL_H__

#include <Sprite/Sprite.hpp>
#include <ObjectGL/Program.hpp>
#include <ObjectGL/VertexArrayObject.hpp>
#include <LSystem/LSystem.hpp>
#include <LSystem/Turtle.hpp>
#include <LSystem/StochasticRules.hpp>
#include <LSystem/Interpreter.hpp>

#define VERTEX_SHADER_PATH "shaders/spell.v.glsl"
#define FRAGMENT_SHADER_PATH "shaders/spell.f.glsl"

class Spell : public Sprite {
public:
    Spell();
    ~Spell();
    void render() override;
private:
    Program * _program;
    VertexArrayObject * _vao;
    LSystem * _system;
    Turtle * _turtle;
    Interpreter * _interpreter;
    std::string _word;
};

#endif

