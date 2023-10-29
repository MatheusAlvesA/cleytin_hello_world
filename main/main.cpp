#include "cleytin_engine.h"
#include "cleytin_controls.h"
#include "fase1.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    CleytinControls *controls = new CleytinControls();
    controls->init();
    Fase1 *hw = new Fase1();

    hw->run(engine, controls);

    delete hw;
    delete controls;
    delete engine;
}

}
