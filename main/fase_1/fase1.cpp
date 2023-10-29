#include "fase1.h"

void Fase1::run(CleytinEngine *engine, CleytinControls *controls) {
    TextTitle *title = new TextTitle();
    title->setControls(controls);
    engine->addObject(title);

    while(1) { // Essa 'fase' do game nunca termina
        engine->loopAndRender();
    }
    engine->clear(true);
}
