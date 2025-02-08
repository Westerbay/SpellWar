/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/spell/Spell.hpp>
#include <iostream>


Spell::Spell() {
    _program = new Program(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    _vao = new VertexArrayObject(1);

    StochasticRules * rules = new StochasticRules;
	rules -> add('F', "FF", 1.0/7);
	rules -> add('F', "F[+F]F", 1.0/7);
	rules -> add('F', "F[-F]F", 1.0/7);
    rules -> add('F', "F[&F]F", 1.0/7);
	rules -> add('F', "F[^F]F", 1.0/7);
    rules -> add('F', "F[\\F]F", 1.0/7);
	rules -> add('F', "F[/F]F", 1.0/7);
	_system = new LSystem("F", rules, 5);

    glm::vec3 position = {-0.5f, 0.0f, 0.0f};
	glm::mat3 heading(1.0f);
	TurtleState turtleState = {position, heading, 0.1f};
	float angle = 20.0f;
	_turtle = new Turtle(turtleState, angle, 0.1f);
	_interpreter = new Interpreter(_turtle);
    _word = _system -> generate();
}

Spell::~Spell() {
    delete _program;
    delete _vao;
    delete _interpreter;
}

unsigned n = 0;

void Spell::render() {
    n ++;
    _interpreter -> systemToWorld(_word);
    _vao -> setVBO(0, _turtle -> getLines());
    _program -> bind();
    _vao -> draw(GL_LINES);
    _program -> unbind();
    _turtle -> reset({
        {-0.5f, 0.0f, 0.0f},
        Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(20.0f), Vector3D(0.0f, 1.0f, 1.0f))),
        0.1f
    });
    if (n%2 == 0) _word = _system -> generate();
}

