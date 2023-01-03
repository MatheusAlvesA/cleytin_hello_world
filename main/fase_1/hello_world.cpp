#include "hello_world.h"

void HelloWorld::run(CleytinEngine *engine) {
    TextTitle *title = new TextTitle();
    engine->addObject(title);

    while(1) { // Essa 'fase' do game nunca termina
        engine->loop();
        engine->render();
    }
}


void TextTitle::setup(CleytinEngine *engine) {
    CEContainer *container = new CEContainer();
    container->setPos(0, 0);
    container->setWidth(LCD_WIDTH_PIXELS);
    container->setHeight(LCD_HEIGHT_PIXELS);
    container->setPositioningStyle(CEPositioningStyle::FLEX_ROW);
    container->setAlignX(CEAlign::CENTER);
    container->setAlignY(CEAlign::CENTER);

    this->text = new CEText();
    this->text->setText("");
    this->text->setSizeMultiplier(3);
    container->addObject(this->text);

    this->graphicObject = container;
    this->timeStart = esp_timer_get_time();
}

void TextTitle::beforeLoop(CleytinEngine *engine) {/* VAZIO */}

void TextTitle::loop(CleytinEngine *engine) {
    uint64_t elapsedTime = esp_timer_get_time() - this->timeStart;
    elapsedTime /= 1000; // Convertendo para milisegundos
    switch (elapsedTime) {
        case 0 ... 200:
            this->text->setText("");
            break;
        case 201 ... 400:
            this->text->setText("O         ");
            break;
        case 401 ... 600:
            this->text->setText("Ol        ");
            break;
        case 601 ... 800:
            this->text->setText("Olá       ");
            break;
        case 801 ... 1000:
            this->text->setText("Olá       ");
            break;
        case 1001 ... 1200:
            this->text->setText("Olá M     ");
            break;
        case 1201 ... 1400:
            this->text->setText("Olá Mu    ");
            break;
        case 1401 ... 1600:
            this->text->setText("Olá Mun   ");
            break;
        case 1601 ... 1800:
            this->text->setText("Olá Mund  ");
            break;
        case 1801 ... 2000:
            this->text->setText("Olá Mundo ");
            break;
        default:
            this->text->setText("Olá Mundo!");
            break;
    }

    if(elapsedTime > 2000) {
        uint64_t segundos = elapsedTime / 1000; //Segundos
        switch (segundos % 5) {
            case 0:
                this->text->setBaseColor({255, 0, 0});
                break;
            case 1:
                this->text->setBaseColor({0, 255, 0});
                break;
            case 2:
                this->text->setBaseColor({0, 0, 255});
                break;
            case 3:
                this->text->setBaseColor({255, 0, 255});
                break;
            case 4:
                this->text->setBaseColor({255, 255, 0});
                break;
            default:
                this->text->setBaseColor({0, 0, 0});
                break;
        }
    }
}

void TextTitle::beforeRender(CleytinEngine *engine) {/* VAZIO */}
