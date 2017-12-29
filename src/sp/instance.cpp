#include "src/sp/instance.hpp"
#include "src/integration-headers/mpc-sp/input.hpp"
#include "src/integration-headers/mps-sp/integration.hpp"
#include "src/mpc-sp/handle_mi.hpp"
#include "src/mpc-sp/instance.hpp"
#include "src/mps-sp/instance.hpp"
#include "src/mps-sp/instance-private.hpp"
#include "src/mps-sp/core_utils.hpp"
#include "src/mps-sp/database.hpp"

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

#include <cstring> //memcpy
#include <string>
#include <stdlib.h> //exit(i)
#include <vector>

namespace Freeworld {

// internal definitions and declarations

mrb_value parse_mi_func (mrb_state* vm, mrb_value value);
mrb_value poll_ci_func (mrb_state* vm, mrb_value value);

class InstanceSpPrivate {
public:
	HandleMi* handle_mi;
	InstanceSpPrivate(InstanceSp* instance) {
		handle_mi = new HandleMi(instance->integration_mpcSp);
	}
	void init_mi_parser(mrb_state* vm) {
		struct RClass* parse_mi_class = mrb_define_class(vm, "Graphics", vm->object_class);
		mrb_define_module_function(vm, parse_mi_class, "parse_mi", &parse_mi_func, MRB_ARGS_ARG(1,0));
	}
	void init_ci_poller(mrb_state* vm) {
		struct RClass* poll_ci_class = mrb_define_class(vm, "Control", vm->object_class);
		mrb_define_module_function(vm, poll_ci_class, "poll_ci", &poll_ci_func, MRB_ARGS_ARG(0,0));
	}
};

mrb_value parse_mi_func (mrb_state* vm, mrb_value value) {
	mrb_value mi;
	mrb_get_args(vm, "S", &mi);
	int len = RSTRING_LEN(mi);
	uint8_t* data = new uint8_t[len];
	auto mi_ptr = RSTRING_PTR(mi);
	memcpy(data, mi_ptr, len);
	// for now, a map; TODO:
	// some neat stuff with lambda expression or virtual function
	vm_instance_map[vm]->sp->priv->handle_mi->handle_mi(len, data);
	return mrb_nil_value();
}

mrb_value poll_ci_func (mrb_state* vm, mrb_value value) {
	Freeworld::Integration::InputEvent ie;
	// for now, a map; TODO:
	// some neat stuff with lambda expression or virtual function
	auto i = vm_instance_map[vm]->sp->mpcSp->integration->input;
	if (i->poll(&ie)) {
		return mrb_str_new(vm, (char*)&ie, 8);
	}
	return mrb_str_new(vm, NULL, 0);
}

// exported definitions

InstanceSp::InstanceSp() {
	mpsSp = new InstanceMpsSp(NULL, this);
	integration_mpsSp = mpsSp->integration;
	mpcSp = new InstanceMpcSp(NULL, this);
	integration_mpcSp = mpcSp->integration;
	priv = new InstanceSpPrivate(this);
}

InstanceSp::~InstanceSp() {
	delete mpcSp;
	integration_mpcSp = NULL;
	delete mpsSp;
	integration_mpsSp = NULL;
	delete priv;
}

void InstanceSp::start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs) {
	mpsSp->start(vm_pkgs);
	mpcSp->start(media_pkgs);
	auto vm = mpsSp->priv->vm;
	priv->init_mi_parser(vm);
	priv->init_ci_poller(vm);
	//instruct the MRuby module to start and load the world
	mrb_load_string(vm, ("start_instance_sp '" + world + "'").c_str());
}

void InstanceSp::stop() {
	mpcSp->stop();
	mpsSp->stop();
}

} // end of namespace Freeworld
