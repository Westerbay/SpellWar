/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/scene/Maintitle.hpp>


Maintitle::Maintitle(AbstractGame * game, World * world) : Scene() {
    _active = true;
    _world = world;
    _game = game;
    _state = MAIN;

    _lightDisplay = true;
    _activeNormalMapping = true;
    _activeParallaxMapping = true;

    Font font(FONT_PATH, FONT_SIZE_TITLE);    
    font.setReferencedCharacter(' ');
    font.setColumnCharacterNumber(8);

    LabelBuilder labelBuilder;
    labelBuilder.setFont(font);
    labelBuilder.setHorizontalResponsive(true);
    labelBuilder.setDesignedSize(DEFAULT_SIZE);
    labelBuilder.setText("Spellwar");
    labelBuilder.setPosition(Point2D(20.0f, 20.0f));
    add(labelBuilder.build());    

    setMaintitleButtons(font);    
    setCharacterSelector(font);
    setOptions(font);
    setBackground();
}

void Maintitle::setMaintitleButtons(Font & font) {
    font.setSize(FONT_SIZE_BUTTONS);
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
    _mainTitleButtons.add(playButton); 
    
    buttonBuilder.setText("Options");
    buttonBuilder.setPosition(Point2D(MARGIN, 400.0f));
    buttonBuilder.setAction([&]() {
        _state = OPTIONS;
    });
    Button * optionButton = buttonBuilder.build();
    _mainTitleButtons.add(optionButton);  

    buttonBuilder.setText("Exit");
    buttonBuilder.setPosition(Point2D(MARGIN, 500.0f));
    buttonBuilder.setAction([&]() {
        _game -> stop();
    });
    Button * exitButton = buttonBuilder.build();
    _mainTitleButtons.add(exitButton);  

    _mainTitleButtons.add(new MaintitleHoverButton(playButton));
    _mainTitleButtons.add(new MaintitleHoverButton(exitButton));
    _mainTitleButtons.add(new MaintitleHoverButton(optionButton));
}

void Maintitle::setCharacterSelector(Font & font) {
    font.setSize(FONT_SIZE_SELECTOR);
    ButtonBuilder buttonBuilder;
    buttonBuilder.setFont(font);
    buttonBuilder.setHorizontalResponsive(true);
    buttonBuilder.setDesignedSize(DEFAULT_SIZE);
    buttonBuilder.setText(">");
    buttonBuilder.setPosition(Point2D(1030.0f, 300.0f));
    buttonBuilder.setAction([&]() {
        _world -> nextCharacter();
    });
    Button * nextCharacter = buttonBuilder.build();
    _characterSelector.add(nextCharacter); 

    buttonBuilder.setText("<");
    buttonBuilder.setPosition(Point2D(600.0f, 300.0f));
    buttonBuilder.setAction([&]() {
        _world -> previousCharacter();
    });
    Button * previousCharacter = buttonBuilder.build();
    _characterSelector.add(previousCharacter); 

    _characterSelector.add(new CharacterSelector(nextCharacter, false));
    _characterSelector.add(new CharacterSelector(previousCharacter, true));
}

void Maintitle::setOptions(Font & font) {
    font.setSize(FONT_SIZE_OPTIONS);
    ButtonBuilder buttonBuilder;
    buttonBuilder.setFont(font);
    buttonBuilder.setHorizontalResponsive(true);
    buttonBuilder.setDesignedSize(DEFAULT_SIZE);
    buttonBuilder.setText("Enable lighting");
    buttonBuilder.setPosition(Point2D(MARGIN, 250.0f));
    buttonBuilder.setAction([&]() {
        _lightDisplay = !_lightDisplay;
        _world -> setActiveLight(_lightDisplay);
        if (!_lightDisplay) {
            _activeNormalMapping = false;
            _activeParallaxMapping = false;
        }
    });
    Button * lightButton = buttonBuilder.build();
    _optionButtons.add(lightButton); 
    
    buttonBuilder.setText("Enable normal map");
    buttonBuilder.setPosition(Point2D(MARGIN, 350.0f));
    buttonBuilder.setAction([&]() {
        _activeNormalMapping = !_activeNormalMapping;
        _world -> setActiveNormalMap(_activeNormalMapping);
        if (!_activeNormalMapping) {
            _activeParallaxMapping = false;
        }
    });
    Button * normalButton = buttonBuilder.build();
    _optionButtons.add(normalButton);  

    buttonBuilder.setText("Enable parallax mapping");
    buttonBuilder.setPosition(Point2D(MARGIN, 450.0f));
    buttonBuilder.setAction([&]() {
        _activeParallaxMapping = !_activeParallaxMapping;
        _world -> setActiveParallaxMapping(_activeParallaxMapping);
    });
    Button * parallaxMapping = buttonBuilder.build();
    _optionButtons.add(parallaxMapping);  

    buttonBuilder.setText("Back");
    buttonBuilder.setPosition(Point2D(MARGIN, 550.0f));
    buttonBuilder.setAction([&]() {
        _state = MAIN;
    });
    Button * backButton = buttonBuilder.build();
    _optionButtons.add(backButton);  

    _optionButtons.add(new MaintitleHoverButton(lightButton));
    _optionButtons.add(new MaintitleHoverButton(normalButton));
    _optionButtons.add(new MaintitleHoverButton(parallaxMapping));
    _optionButtons.add(new MaintitleHoverButton(backButton));
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
        _characterSelector.update();
        if (_state == MAIN) {
            _mainTitleButtons.update();
        }       
        else {
            _optionButtons.update();
        }
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

        if (_state == MAIN) {
            _mainTitleButtons.renderHUD(screenSize);
        }       
        else {
            _optionButtons.renderHUD(screenSize);
        }        

        Size designedSize = DEFAULT_SIZE;
        float designedRatio = (float) designedSize.width / designedSize.height;
        float ratio = (float) screenSize.width / screenSize.height;
        float diff = designedRatio - ratio;        
        if (diff > -0.4f && diff < 0.85f) {
            _characterSelector.renderHUD(screenSize);
        }        
    }
}

MaintitleHoverButton::MaintitleHoverButton(Button * button) : GameObject() {
    _button = button;
    _font = button -> getFont();
    _rebuild = false;
}

void MaintitleHoverButton::update() {
    bool hover = _button -> hover();
    if (hover && !_rebuild) { 
        Font font = _font;
        font.setColor(HOVER_COLOR);
        _button -> setFont(font);
        _button -> rebuild();
        _rebuild = true;
    } else if (!hover && _rebuild) {
        _button -> setFont(_font);
        _button -> rebuild();
        _rebuild = false;
    }
}

CharacterSelector::CharacterSelector(Button * button, bool left) : MaintitleHoverButton(button) {
    _left = left;
    _position = button -> getPosition();
    _screenSize = DEFAULT_SIZE;
}

void CharacterSelector::renderHUD(const Size & screenSize) {
    if (_screenSize.width == screenSize.width && _screenSize.height == screenSize.height) {
        MaintitleHoverButton::renderHUD(screenSize);
        return;
    }
    Size designedSize = DEFAULT_SIZE;
    float designedRatio = (float) designedSize.width / designedSize.height;
    float ratio = (float) screenSize.width / screenSize.height;
    float diff = designedRatio - ratio;
    _button -> setPosition(_position + Vector2D(diff * 175.0f));
    _button -> rebuild();
    _screenSize = screenSize;
    MaintitleHoverButton::renderHUD(screenSize);
}
 