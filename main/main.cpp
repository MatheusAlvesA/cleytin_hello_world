#include "cleytin_engine.h"
#include "hello_world.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    HelloWorld *hw = new HelloWorld();

    hw->run(engine);
}

}
