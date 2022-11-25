#include "scripting/scriptingevents.h"

namespace tea {

ScriptingEvents::ScriptingEvents(std::shared_ptr<Scripting> scripting) : scripting(std::move(scripting)) { }

void ScriptingEvents::on_start() {

}

void ScriptingEvents::on_quit() {

}

void ScriptingEvents::on_update(double delta_time) {

}

void ScriptingEvents::on_draw(double delta_time) {

}

}