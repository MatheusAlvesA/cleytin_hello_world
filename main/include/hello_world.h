#ifndef FASE_1_HELLO_WORLD
#define FASE_1_HELLO_WORLD

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_container.h"

class HelloWorld {
public:
    void run(CleytinEngine *engine);
};

class TextTitle : public CEActiveObject {
public:
    void setup(CleytinEngine *engine);
    void beforeLoop(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void beforeRender(CleytinEngine *engine);
private:
    CEText *text;
    uint64_t timeStart;
};

#endif
