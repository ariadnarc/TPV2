// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../utils/mpl.h"

// You should define a file ../game/ecs_defs.h with the list of your
// components, groups, and handlers. See ecs_defs_example.h for an
// example file
//
#if __has_include("../game/ecs_defs.h")
#include "../game/ecs_defs.h"
#else
#define _CMPS_LIST_ _CMP_1
#define _GRPS_LIST_ _GRP_2
#define _HDLRS_LIST_ _HDLR_1
#define _SYS_LIST_ _SYS_1
#endif


namespace ecs {

// forward declaration of some classes, to be used when we
// just need to know that they exist
struct Component;
struct Entity;
class Manager;
class System;

using entity_t = Entity*;

// We define type for the identifiers so we can change them easily.
// For example, if we have less than 256 components we can use one
// byte, i.e. uint8_t, if we have up to 512 we can use uint16_t,
// and so on ...
//
using cmpId_t = uint8_t;
using grpId_t = uint8_t;
using hdlrId_t = uint8_t;
using sysId_t = uint8_t;

// we use a name space for the components enum to avoid conflicts
namespace cmp {
// list of component identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
//enum cmpId : cmpId_t {
//	_CMPS_LIST_, /* taken from ../game/ecs_defs */
//
//	// do not remove this
//	_LAST_CMP_ID
//};

using componentsList = mpl::TypeList<_CMPS_LIST_>;
}

namespace grp {
// list of group identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum grpId : grpId_t {
	DEFAULT,
	_GRPS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_GRP_ID
};
}

namespace hdlr {
// list of handler identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
enum hdlrId : hdlrId_t {
	_HDLRS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_HDLR_ID
};
}

namespace sys {
// list of system identifiers - note that we rely on that the
// first number is 0 in C/C++ standard
//enum sysId : hdlrId_t {
//	_SYS_LIST_, /* taken from ../game/ecs_defs */
//
//	// do not remove this
//	_LAST_SYS_ID
//};
using systemsList = mpl::TypeList<_SYS_LIST_>;
}

constexpr cmpId_t maxComponentId = cmp::componentsList::size;
constexpr cmpId_t maxGroupId = grp::grpId::_LAST_GRP_ID;
constexpr hdlrId_t maxHandlerId = hdlr::hdlrId::_LAST_HDLR_ID;
constexpr sysId_t maxSystemId = sys::systemsList::size;

// a template variable to obtain the component id.
template<typename T>
constexpr cmpId_t cmpId = mpl::IndexOf<T, cmp::componentsList>();

// a template variable to obtain the system id.
template<typename T>
constexpr sysId_t sysId = mpl::IndexOf<T, sys::systemsList>();


} // end of namespace

