#ifndef FASE_1_GAME
#define FASE_1_GAME

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_container.h"

class Game {
public:
    void run(CleytinEngine *engine);
};

class TextTitle : public CEContainer {
public:
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CEText *text;
    uint64_t timeStart;
};

#endif
