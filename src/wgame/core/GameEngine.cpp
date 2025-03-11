/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameEngine.hpp>


namespace wgame {

GameEngine::GameEngine(AbstractGame * game, AbstractFrame * frame) {
    _game = game;
    _frame = frame;
    _camera = new GameCamera();
    _world = new GameObjectGroup();
    _light = new GameLight();
}

GameEngine::~GameEngine() {
    delete _light;
    delete _camera;
    delete _world;
    delete _game;
    delete _frame;
}

void GameEngine::start() {
    using namespace std::chrono;

    _game -> initWorld(_world);
    _frame -> initWorld(_world);

    _game -> initCamera(_camera);
    _frame -> initCamera(_camera);

    _game -> initLight(_light);
    _frame -> initLight(_light);

    _game -> init();   
    while (!glfwWindowShouldClose(_frame -> getFrameWindow())) {
        steady_clock::time_point updateStart = steady_clock::now();
        
        glfwPollEvents();   
        System::record();             
        
        _game -> update();
        _camera -> update();
        _frame -> render();
        glfwSwapBuffers(_frame -> getFrameWindow());
        
        #ifdef _WIN32
        while (duration_cast<milliseconds>(steady_clock::now() - updateStart).count() < _game -> getUpdateDelay());
        #else
        steady_clock::time_point updateEnd = steady_clock::now();
        unsigned updateTime = duration_cast<milliseconds>(updateEnd - updateStart).count();
        if (updateTime < _game -> getUpdateDelay()) {
            std::this_thread::sleep_for(
                milliseconds(_game -> getUpdateDelay() - updateTime)
            );
        }
        #endif
    }

}

}

