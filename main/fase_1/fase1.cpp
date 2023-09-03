#include "fase1.h"

void Game::run(CleytinEngine *engine) {
    TextTitle *title = new TextTitle();
    engine->addObject(title);

    while(1) { // Essa 'fase' do game nunca termina
        engine->loop();
        engine->render();
        cleytin_delay(10);
    }
}


void TextTitle::setup(CleytinEngine *engine) {
    this->setPos(0, 0);
    this->setWidth(LCD_WIDTH_PIXELS);
    this->setHeight(LCD_HEIGHT_PIXELS);
    this->setPositioningStyle(CEPositioningStyle::FLEX_ROW);
    this->setAlignX(CEAlign::CENTER);
    this->setAlignY(CEAlign::CENTER);

    this->text = new CEText();
    this->text->setText("");
    this->text->setSizeMultiplier(3);
    this->addObject(this->text);

    this->timeStart = esp_timer_get_time();
}

void TextTitle::loop(CleytinEngine *engine) {
    uint64_t elapsedTime = esp_timer_get_time() - this->timeStart;
    elapsedTime /= 1000; // Convertendo para milisegundos
    switch (elapsedTime) {
        case 0 ... 200:
            this->text->setText("");
            this->onObjectUpdated();
            break;
        case 201 ... 400:
            this->text->setText("O         ");
            this->onObjectUpdated();
            break;
        case 401 ... 600:
            this->text->setText("Ol        ");
            this->onObjectUpdated();
            break;
        case 601 ... 800:
            this->text->setText("Olá       ");
            this->onObjectUpdated();
            break;
        case 801 ... 1000:
            this->text->setText("Olá       ");
            this->onObjectUpdated();
            break;
        case 1001 ... 1200:
            this->text->setText("Olá M     ");
            this->onObjectUpdated();
            break;
        case 1201 ... 1400:
            this->text->setText("Olá Mu    ");
            this->onObjectUpdated();
            break;
        case 1401 ... 1600:
            this->text->setText("Olá Mun   ");
            this->onObjectUpdated();
            break;
        case 1601 ... 1800:
            this->text->setText("Olá Mund  ");
            this->onObjectUpdated();
            break;
        case 1801 ... 2000:
            this->text->setText("Olá Mundo ");
            this->onObjectUpdated();
            break;
        default:
            this->text->setText("Olá Mundo!");
            this->onObjectUpdated();
            break;
    }

    if(elapsedTime > 2000) {
        uint64_t segundos = elapsedTime / 1000; //Segundos
        switch (segundos % 5) {
            case 0:
                this->text->setBaseColor({255, 0, 0});
                this->onObjectUpdated();
                break;
            case 1:
                this->text->setBaseColor({0, 255, 0});
                this->onObjectUpdated();
                break;
            case 2:
                this->text->setBaseColor({0, 0, 255});
                this->onObjectUpdated();
                break;
            case 3:
                this->text->setBaseColor({255, 0, 255});
                this->onObjectUpdated();
                break;
            case 4:
                this->text->setBaseColor({255, 255, 0});
                this->onObjectUpdated();
                break;
            default:
                this->text->setBaseColor({0, 0, 0});
                this->onObjectUpdated();
                break;
        }
    }
}

