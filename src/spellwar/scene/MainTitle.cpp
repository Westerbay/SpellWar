/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/scene/Maintitle.hpp>


Maintitle::Maintitle(AbstractGame * game, Scene * world) : Scene() {
    _active = true;
    _world = world;
    _game = game;

    Font font(FONT_PATH, FONT_SIZE_TITLE);    
    font.setReferencedCharacter(' ');
    font.setColumnCharacterNumber(8);

    LabelBuilder labelBuilder;
    labelBuilder.setFont(font);
    labelBuilder.setHorizontalResponsive(true);
    labelBuilder.setDesignedSize(DEFAULT_SIZE);
    labelBuilder.setText("Spellwar");
    labelBuilder.setPosition(Point2D(20.0f, 0.0f));
    add(labelBuilder.build());    

    setButtons();
    setBackground();
}

void Maintitle::setButtons() {
    Font font(FONT_PATH, FONT_SIZE_BUTTONS);    
    font.setReferencedCharacter(' ');
    font.setColumnCharacterNumber(8);

    ButtonBuilder buttonBuilder;
    buttonBuilder.setFont(font);
    buttonBuilder.setHorizontalResponsive(true);
    buttonBuilder.setDesignedSize(DEFAULT_SIZE);
    buttonBuilder.setText("Play");
    buttonBuilder.setPosition(Point2D(MARGIN, 300.0f));
    buttonBuilder.setAction([&]() {
        System system;
        system.postEvent(IN_GAME_EVENT);
        _world -> setActive(true);
        setActive(false);
    });
    Button * playButton = buttonBuilder.build();
    add(playButton); 
    
    buttonBuilder.setText("Options");
    buttonBuilder.setPosition(Point2D(MARGIN, 400.0f));
    buttonBuilder.setAction([&]() {
        
    });
    Button * optionButton = buttonBuilder.build();
    add(optionButton);  

    buttonBuilder.setText("Exit");
    buttonBuilder.setPosition(Point2D(MARGIN, 500.0f));
    buttonBuilder.setAction([&]() {
        _game -> stop();
    });
    Button * exitButton = buttonBuilder.build();
    add(exitButton);  

    add(new MaintitleButton(playButton));
    add(new MaintitleButton(exitButton));
    add(new MaintitleButton(optionButton));
}

void Maintitle::setBackground() {
    Hitbox background;
    Size defaultSize = DEFAULT_SIZE;
    background.size.x = (float) defaultSize.width * 0.6f;
    background.size.y = (float) defaultSize.height;
    background.move(background.size * 0.5f);
    std::vector<ColorRGBA> _colorsEdge = {
        ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f), ColorRGBA(0.0f),
        ColorRGBA(0.0f), ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f)
    };
    std::vector<std::vector<ColorRGBA>> _colors(6, _colorsEdge);
    _colorDrawer.setFillCuboidData(background, _colors);
}

void Maintitle::setActive(bool active) {
    _active = active;
}

void Maintitle::update() {
    if (_active) {
        Scene::update();
    }
}

void Maintitle::renderHUD(const Size & screenSize) {
    if (_active) {
        Matrix4D transform(1.0f);
        Size defaultSize = DEFAULT_SIZE;
        float scaleW = (float) screenSize.width / defaultSize.width;
        float scaleH = (float) screenSize.height / defaultSize.height;
        transform = glm::scale(transform, Vector3D(scaleW, scaleH, 0.0f));
        _colorDrawer.fill(transform, Drawer::HUD);
        Scene::renderHUD(screenSize);
    }
}

MaintitleButton::MaintitleButton(Button * button) : GameObject() {
    _button = button;
    _text = button -> getText();
}

void MaintitleButton::update() {
    String text = _button -> getText();
    bool hover = _button -> hover();
    if (hover && text[0] != '>') {   
        _button -> setText(">" + _text);
        _button -> rebuild();
    } else if (!hover && text[0] == '>') {
        _button -> setText(_text);
        _button -> rebuild();
    }
}
 