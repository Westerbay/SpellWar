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

    _mainTitleButtons.add(new MaintitleHoverButton(playButton, font));
    _mainTitleButtons.add(new MaintitleHoverButton(exitButton, font));
    _mainTitleButtons.add(new MaintitleHoverButton(optionButton, font));
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
    add(nextCharacter); 

    buttonBuilder.setText("<");
    buttonBuilder.setPosition(Point2D(600.0f, 300.0f));
    buttonBuilder.setAction([&]() {
        _world -> previousCharacter();
    });
    Button * previousCharacter = buttonBuilder.build();
    add(previousCharacter); 

    add(new MaintitleHoverButton(nextCharacter, font));
    add(new MaintitleHoverButton(previousCharacter, font));
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
        _mainTitleButtons.update();
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
        _mainTitleButtons.renderHUD(screenSize);
    }
}

MaintitleHoverButton::MaintitleHoverButton(Button * button, const Font & font) : GameObject() {
    _button = button;
    _font = font;
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
 