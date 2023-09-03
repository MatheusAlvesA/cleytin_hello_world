#include "cleytin_engine.h"
#include "fase1.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    Game *hw = new Game();

    hw->run(engine);
}

}
