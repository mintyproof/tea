#ifndef TEA_SCRIPTING_SCRIPTINGEVENTS_H
#define TEA_SCRIPTING_SCRIPTINGEVENTS_H

#include <memory>

namespace tea {

class Scripting;

class ScriptingEvents {
public:
    explicit ScriptingEvents(std::shared_ptr<Scripting> scripting);

    void on_start();
    void on_quit();

    void on_update(double delta_time);
    void on_draw(double delta_time);
private:
    std::shared_ptr<Scripting> scripting;
};

}

#endif // TEA_SCRIPTING_SCRIPTINGEVENTS_H