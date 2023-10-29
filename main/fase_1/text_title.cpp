#include "text_title.h"

TextTitle::TextTitle() {
    this->controls = NULL;
    this->colorIndex = 0;
    this->timer = new CETimer(TEXT_TITLE_COLOR_CHANGE_TIME);
}

void TextTitle::setControls(CleytinControls *controls) {
    this->controls = controls;
}

TextTitle::~TextTitle() {
    delete this->text;
    delete this->animation;
    delete this->timer;
}

void TextTitle::setup(CleytinEngine *engine) {
    this->setPos(0, 0);
    this->setWidth(LCD_WIDTH_PIXELS);
    this->setHeight(LCD_HEIGHT_PIXELS);
    this->setPositioningStyle(CEPositioningStyle::FLEX_ROW);
    this->setAlignX(CEAlign::CENTER);
    this->setAlignY(CEAlign::CENTER);

    this->text = new CEText();
    this->text->setText("Olá mundo!");
    this->text->setSizeMultiplier(3);
    this->addObject(this->text);

    this->animation = new CETextRevealAnimation();
    this->animation->setObject(this->text);
    this->animation->setDuration(2000);
    this->animation->start();

    this->colors = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 0, 255},
        {255, 255, 0},
        {0, 0, 0}
    };
}

void TextTitle::loop(CleytinEngine *engine) {
    this->animation->loop();
    if(this->controls->getStart() && this->timer->check()) {
        this->timer->reset();
        this->colorIndex++;
        if(this->colorIndex >= TEXT_TITLE_COLORS_COUNT) {
            this->colorIndex = 0;
        }
        this->text->setBaseColor(this->colors[this->colorIndex]);
    }
    this->onObjectUpdated();
}
