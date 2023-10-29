#ifndef TEXT_TITLE_H
#define TEXT_TITLE_H

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_container.h"
#include "ce_text_reveal_animation.h"
#include "cleytin_controls.h"
#include "ce_timer.h"
#include <vector>

#define TEXT_TITLE_COLORS_COUNT 6
#define TEXT_TITLE_COLOR_CHANGE_TIME 500

class TextTitle : public CEContainer {
public:
    TextTitle();
    ~TextTitle();
    void setControls(CleytinControls *controls);
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CEText *text;
    CETextRevealAnimation *animation;
    CleytinControls *controls;
    std::vector<CEColor> colors;
    size_t colorIndex;
    CETimer *timer;
};

#endif
