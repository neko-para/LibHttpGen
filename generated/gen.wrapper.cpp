// clang-format off

#include "helper.h"
#define LHG_PROCESS

// LHG SEC BEGIN lhg.include
#include "MaaFramework/MaaAPI.h"
#include "MaaToolKit/MaaToolKitAPI.h"
// LHG SEC END

// LHG SEC BEGIN lhg.custom.global
// LHG SEC DEF

// LHG SEC END

static callback_manager<void (*)(const char *, const char *, void *)> MaaAPICallback__Manager;

static HandleManager<MaaControllerAPI *> MaaControllerAPI__OpaqueManager;

static HandleManager<MaaResourceAPI *> MaaResourceAPI__OpaqueManager;

static HandleManager<MaaInstanceAPI *> MaaInstanceAPI__OpaqueManager;

static HandleManager<MaaImageBuffer *> MaaImageBuffer__OpaqueManager;

static HandleManager<MaaStringBuffer *> MaaStringBuffer__OpaqueManager;

static HandleManager<MaaRect *> MaaRect__OpaqueManager;

std::optional<json::object> MaaAdbControllerCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.adb_path
// LHG SEC DEF
    auto adb_path_temp = from_json<const char *>(__param["adb_path"]);
    auto adb_path = from_json_fix<const char *>(adb_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.address
// LHG SEC DEF
    auto address_temp = from_json<const char *>(__param["address"]);
    auto address = from_json_fix<const char *>(address_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.type
// LHG SEC DEF
    auto type_temp = from_json<int>(__param["type"]);
    auto type = from_json_fix<int>(type_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.config
// LHG SEC DEF
    auto config_temp = from_json<const char *>(__param["config"]);
    auto config = from_json_fix<const char *>(config_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaAdbControllerCreate(
        adb_path,
        address,
        type,
        config,
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaWin32ControllerCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.hWnd
// LHG SEC DEF
    auto hWnd_temp = from_json<unsigned long long>(__param["hWnd"]);
    auto hWnd = from_json_fix<unsigned long long>(hWnd_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.type
// LHG SEC DEF
    auto type_temp = from_json<int>(__param["type"]);
    auto type = from_json_fix<int>(type_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaWin32ControllerCreate(
        hWnd,
        type,
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaAdbControllerCreateV2_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.adb_path
// LHG SEC DEF
    auto adb_path_temp = from_json<const char *>(__param["adb_path"]);
    auto adb_path = from_json_fix<const char *>(adb_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.address
// LHG SEC DEF
    auto address_temp = from_json<const char *>(__param["address"]);
    auto address = from_json_fix<const char *>(address_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.type
// LHG SEC DEF
    auto type_temp = from_json<int>(__param["type"]);
    auto type = from_json_fix<int>(type_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.config
// LHG SEC DEF
    auto config_temp = from_json<const char *>(__param["config"]);
    auto config = from_json_fix<const char *>(config_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.agent_path
// LHG SEC DEF
    auto agent_path_temp = from_json<const char *>(__param["agent_path"]);
    auto agent_path = from_json_fix<const char *>(agent_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaAdbControllerCreateV2(
        adb_path,
        address,
        type,
        config,
        agent_path,
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaThriftControllerCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.type
// LHG SEC DEF
    auto type_temp = from_json<int>(__param["type"]);
    auto type = from_json_fix<int>(type_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.host
// LHG SEC DEF
    auto host_temp = from_json<const char *>(__param["host"]);
    auto host = from_json_fix<const char *>(host_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.port
// LHG SEC DEF
    auto port_temp = from_json<int>(__param["port"]);
    auto port = from_json_fix<int>(port_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.config
// LHG SEC DEF
    auto config_temp = from_json<const char *>(__param["config"]);
    auto config = from_json_fix<const char *>(config_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaThriftControllerCreate(
        type,
        host,
        port,
        config,
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaDbgControllerCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.read_path
// LHG SEC DEF
    auto read_path_temp = from_json<const char *>(__param["read_path"]);
    auto read_path = from_json_fix<const char *>(read_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.write_path
// LHG SEC DEF
    auto write_path_temp = from_json<const char *>(__param["write_path"]);
    auto write_path = from_json_fix<const char *>(write_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.type
// LHG SEC DEF
    auto type_temp = from_json<int>(__param["type"]);
    auto type = from_json_fix<int>(type_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.config
// LHG SEC DEF
    auto config_temp = from_json<const char *>(__param["config"]);
    auto config = from_json_fix<const char *>(config_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaDbgControllerCreate(
        read_path,
        write_path,
        type,
        config,
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerDestroy_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerDestroy.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    MaaControllerAPI *ctrl;
    MaaControllerAPI__OpaqueManager.del(ctrl_id, ctrl);
// LHG SEC END
    MaaControllerDestroy(
        ctrl
    );
// LHG SEC BEGIN lhg.impl.MaaControllerDestroy.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerDestroy.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaControllerSetOption_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.key
// LHG SEC DEF
    auto key_temp = from_json<int>(__param["key"]);
    auto key = from_json_fix<int>(key_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.value
// LHG SEC DEF
    auto value_temp = from_json<void *>(__param["value"]);
    auto value = from_json_fix<void *>(value_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.val_size
// LHG SEC DEF
    auto val_size_temp = from_json<unsigned long long>(__param["val_size"]);
    auto val_size = from_json_fix<unsigned long long>(val_size_temp);
// LHG SEC END
    auto __return = MaaControllerSetOption(
        ctrl,
        key,
        value,
        val_size
    );
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostConnection_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostConnection.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
    auto __return = MaaControllerPostConnection(
        ctrl
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostConnection.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostConnection.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostClick_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.x
// LHG SEC DEF
    auto x_temp = from_json<int>(__param["x"]);
    auto x = from_json_fix<int>(x_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.y
// LHG SEC DEF
    auto y_temp = from_json<int>(__param["y"]);
    auto y = from_json_fix<int>(y_temp);
// LHG SEC END
    auto __return = MaaControllerPostClick(
        ctrl,
        x,
        y
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostSwipe_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.x1
// LHG SEC DEF
    auto x1_temp = from_json<int>(__param["x1"]);
    auto x1 = from_json_fix<int>(x1_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.y1
// LHG SEC DEF
    auto y1_temp = from_json<int>(__param["y1"]);
    auto y1 = from_json_fix<int>(y1_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.x2
// LHG SEC DEF
    auto x2_temp = from_json<int>(__param["x2"]);
    auto x2 = from_json_fix<int>(x2_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.y2
// LHG SEC DEF
    auto y2_temp = from_json<int>(__param["y2"]);
    auto y2 = from_json_fix<int>(y2_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.duration
// LHG SEC DEF
    auto duration_temp = from_json<int>(__param["duration"]);
    auto duration = from_json_fix<int>(duration_temp);
// LHG SEC END
    auto __return = MaaControllerPostSwipe(
        ctrl,
        x1,
        y1,
        x2,
        y2,
        duration
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostPressKey_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.arg.keycode
// LHG SEC DEF
    auto keycode_temp = from_json<int>(__param["keycode"]);
    auto keycode = from_json_fix<int>(keycode_temp);
// LHG SEC END
    auto __return = MaaControllerPostPressKey(
        ctrl,
        keycode
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchDown_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.contact
// LHG SEC DEF
    auto contact_temp = from_json<int>(__param["contact"]);
    auto contact = from_json_fix<int>(contact_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.x
// LHG SEC DEF
    auto x_temp = from_json<int>(__param["x"]);
    auto x = from_json_fix<int>(x_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.y
// LHG SEC DEF
    auto y_temp = from_json<int>(__param["y"]);
    auto y = from_json_fix<int>(y_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.pressure
// LHG SEC DEF
    auto pressure_temp = from_json<int>(__param["pressure"]);
    auto pressure = from_json_fix<int>(pressure_temp);
// LHG SEC END
    auto __return = MaaControllerPostTouchDown(
        ctrl,
        contact,
        x,
        y,
        pressure
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchMove_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.contact
// LHG SEC DEF
    auto contact_temp = from_json<int>(__param["contact"]);
    auto contact = from_json_fix<int>(contact_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.x
// LHG SEC DEF
    auto x_temp = from_json<int>(__param["x"]);
    auto x = from_json_fix<int>(x_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.y
// LHG SEC DEF
    auto y_temp = from_json<int>(__param["y"]);
    auto y = from_json_fix<int>(y_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.pressure
// LHG SEC DEF
    auto pressure_temp = from_json<int>(__param["pressure"]);
    auto pressure = from_json_fix<int>(pressure_temp);
// LHG SEC END
    auto __return = MaaControllerPostTouchMove(
        ctrl,
        contact,
        x,
        y,
        pressure
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchUp_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.arg.contact
// LHG SEC DEF
    auto contact_temp = from_json<int>(__param["contact"]);
    auto contact = from_json_fix<int>(contact_temp);
// LHG SEC END
    auto __return = MaaControllerPostTouchUp(
        ctrl,
        contact
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostScreencap_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostScreencap.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
    auto __return = MaaControllerPostScreencap(
        ctrl
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostScreencap.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostScreencap.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerStatus_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaControllerStatus(
        ctrl,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerWait_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerWait.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerWait.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaControllerWait(
        ctrl,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaControllerWait.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerWait.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerConnected_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerConnected.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
    auto __return = MaaControllerConnected(
        ctrl
    );
// LHG SEC BEGIN lhg.impl.MaaControllerConnected.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerConnected.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerGetImage_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.arg.buffer
// LHG SEC DEF
    auto buffer_id = __param["buffer"].as_string();
    auto buffer = MaaImageBuffer__OpaqueManager.get(buffer_id);
// LHG SEC END
    auto __return = MaaControllerGetImage(
        ctrl,
        buffer
    );
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaControllerGetUUID_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.arg.buffer
// LHG SEC DEF
    auto buffer_id = __param["buffer"].as_string();
    auto buffer = MaaStringBuffer__OpaqueManager.get(buffer_id);
// LHG SEC END
    auto __return = MaaControllerGetUUID(
        ctrl,
        buffer
    );
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaCreate(
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaCreate.return
// LHG SEC DEF
    auto __ret = MaaInstanceAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaDestroy_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaDestroy.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    MaaInstanceAPI *inst;
    MaaInstanceAPI__OpaqueManager.del(inst_id, inst);
// LHG SEC END
    MaaDestroy(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaDestroy.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDestroy.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaSetOption_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.key
// LHG SEC DEF
    auto key_temp = from_json<int>(__param["key"]);
    auto key = from_json_fix<int>(key_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.value
// LHG SEC DEF
    auto value_temp = from_json<void *>(__param["value"]);
    auto value = from_json_fix<void *>(value_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.val_size
// LHG SEC DEF
    auto val_size_temp = from_json<unsigned long long>(__param["val_size"]);
    auto val_size = from_json_fix<unsigned long long>(val_size_temp);
// LHG SEC END
    auto __return = MaaSetOption(
        inst,
        key,
        value,
        val_size
    );
// LHG SEC BEGIN lhg.impl.MaaSetOption.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaBindResource_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaBindResource.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindResource.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
    auto __return = MaaBindResource(
        inst,
        res
    );
// LHG SEC BEGIN lhg.impl.MaaBindResource.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindResource.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaBindController_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaBindController.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindController.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
    auto __return = MaaBindController(
        inst,
        ctrl
    );
// LHG SEC BEGIN lhg.impl.MaaBindController.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindController.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaInited_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaInited.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaInited(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaInited.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaInited.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaClearCustomRecognizer_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaClearCustomRecognizer.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaClearCustomRecognizer(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaClearCustomRecognizer.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaClearCustomRecognizer.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaClearCustomAction_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaClearCustomAction.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaClearCustomAction(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaClearCustomAction.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaClearCustomAction.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaPostTask_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.entry
// LHG SEC DEF
    auto entry_temp = from_json<const char *>(__param["entry"]);
    auto entry = from_json_fix<const char *>(entry_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.param
// LHG SEC DEF
    auto param_temp = from_json<const char *>(__param["param"]);
    auto param = from_json_fix<const char *>(param_temp);
// LHG SEC END
    auto __return = MaaPostTask(
        inst,
        entry,
        param
    );
// LHG SEC BEGIN lhg.impl.MaaPostTask.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostTask.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetTaskParam_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.param
// LHG SEC DEF
    auto param_temp = from_json<const char *>(__param["param"]);
    auto param = from_json_fix<const char *>(param_temp);
// LHG SEC END
    auto __return = MaaSetTaskParam(
        inst,
        id,
        param
    );
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaTaskStatus_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaTaskStatus(
        inst,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaWaitTask_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaWaitTask.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWaitTask.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaWaitTask(
        inst,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaWaitTask.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWaitTask.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaTaskAllFinished_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaTaskAllFinished.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaTaskAllFinished(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaTaskAllFinished.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaTaskAllFinished.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaStop_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaStop.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaStop(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaStop.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaStop.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetResource_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetResource.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaGetResource(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaGetResource.return
// LHG SEC DEF
    auto __ret = MaaResourceAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetResource.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetController_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetController.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaGetController(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaGetController.return
// LHG SEC DEF
    auto __ret = MaaControllerAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetController.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceCreate_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceCreate.arg.callback
// LHG SEC DEF
    auto callback = &__CallbackImpl<2, void (*)(const char *, const char *, void *), const char *, const char *, void *>;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceCreate.arg.callback_arg
// LHG SEC DEF
    auto callback_arg_id = __param["callback"].as_string();
    auto callback_arg = MaaAPICallback__Manager.find(callback_arg_id).get();
// LHG SEC END
    auto __return = MaaResourceCreate(
        callback,
        callback_arg
    );
// LHG SEC BEGIN lhg.impl.MaaResourceCreate.return
// LHG SEC DEF
    auto __ret = MaaResourceAPI__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceCreate.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceDestroy_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceDestroy.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    MaaResourceAPI *res;
    MaaResourceAPI__OpaqueManager.del(res_id, res);
// LHG SEC END
    MaaResourceDestroy(
        res
    );
// LHG SEC BEGIN lhg.impl.MaaResourceDestroy.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceDestroy.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaResourcePostPath_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.arg.path
// LHG SEC DEF
    auto path_temp = from_json<const char *>(__param["path"]);
    auto path = from_json_fix<const char *>(path_temp);
// LHG SEC END
    auto __return = MaaResourcePostPath(
        res,
        path
    );
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceStatus_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaResourceStatus(
        res,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceWait_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceWait.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceWait.arg.id
// LHG SEC DEF
    auto id_temp = from_json<long long>(__param["id"]);
    auto id = from_json_fix<long long>(id_temp);
// LHG SEC END
    auto __return = MaaResourceWait(
        res,
        id
    );
// LHG SEC BEGIN lhg.impl.MaaResourceWait.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceWait.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceLoaded_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceLoaded.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
    auto __return = MaaResourceLoaded(
        res
    );
// LHG SEC BEGIN lhg.impl.MaaResourceLoaded.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceLoaded.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceSetOption_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.key
// LHG SEC DEF
    auto key_temp = from_json<int>(__param["key"]);
    auto key = from_json_fix<int>(key_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.value
// LHG SEC DEF
    auto value_temp = from_json<void *>(__param["value"]);
    auto value = from_json_fix<void *>(value_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.val_size
// LHG SEC DEF
    auto val_size_temp = from_json<unsigned long long>(__param["val_size"]);
    auto val_size = from_json_fix<unsigned long long>(val_size_temp);
// LHG SEC END
    auto __return = MaaResourceSetOption(
        res,
        key,
        value,
        val_size
    );
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceGetHash_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.arg.buffer
// LHG SEC DEF
    auto buffer_id = __param["buffer"].as_string();
    auto buffer = MaaStringBuffer__OpaqueManager.get(buffer_id);
// LHG SEC END
    auto __return = MaaResourceGetHash(
        res,
        buffer
    );
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceGetTaskList_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.arg.buffer
// LHG SEC DEF
    auto buffer_id = __param["buffer"].as_string();
    auto buffer = MaaStringBuffer__OpaqueManager.get(buffer_id);
// LHG SEC END
    auto __return = MaaResourceGetTaskList(
        res,
        buffer
    );
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaCreateStringBuffer_Wrapper(json::object __param) {
    auto __return = MaaCreateStringBuffer(

    );
// LHG SEC BEGIN lhg.impl.MaaCreateStringBuffer.return
// LHG SEC DEF
    auto __ret = MaaStringBuffer__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreateStringBuffer.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaDestroyStringBuffer_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaDestroyStringBuffer.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    MaaStringBuffer *handle;
    MaaStringBuffer__OpaqueManager.del(handle_id, handle);
// LHG SEC END
    MaaDestroyStringBuffer(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaDestroyStringBuffer.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDestroyStringBuffer.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaIsStringEmpty_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaIsStringEmpty.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaIsStringEmpty(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaIsStringEmpty.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaIsStringEmpty.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaClearString_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaClearString.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaClearString(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaClearString.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaClearString.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetString_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetString.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetString(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetString.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetString.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetStringSize_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetStringSize.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetStringSize(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetStringSize.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetStringSize.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetString_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetString.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetString.arg.str
// LHG SEC DEF
    auto str_temp = from_json<const char *>(__param["str"]);
    auto str = from_json_fix<const char *>(str_temp);
// LHG SEC END
    auto __return = MaaSetString(
        handle,
        str
    );
// LHG SEC BEGIN lhg.impl.MaaSetString.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetString.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetStringEx_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetStringEx.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaStringBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetStringEx.arg.str
// LHG SEC DEF
    auto str_temp = from_json<const char *>(__param["str"]);
    auto str = from_json_fix<const char *>(str_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetStringEx.arg.size
// LHG SEC DEF
    auto size_temp = from_json<unsigned long long>(__param["size"]);
    auto size = from_json_fix<unsigned long long>(size_temp);
// LHG SEC END
    auto __return = MaaSetStringEx(
        handle,
        str,
        size
    );
// LHG SEC BEGIN lhg.impl.MaaSetStringEx.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetStringEx.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaCreateImageBuffer_Wrapper(json::object __param) {
    auto __return = MaaCreateImageBuffer(

    );
// LHG SEC BEGIN lhg.impl.MaaCreateImageBuffer.return
// LHG SEC DEF
    auto __ret = MaaImageBuffer__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreateImageBuffer.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaDestroyImageBuffer_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaDestroyImageBuffer.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    MaaImageBuffer *handle;
    MaaImageBuffer__OpaqueManager.del(handle_id, handle);
// LHG SEC END
    MaaDestroyImageBuffer(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaDestroyImageBuffer.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDestroyImageBuffer.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaIsImageEmpty_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaIsImageEmpty.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaIsImageEmpty(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaIsImageEmpty.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaIsImageEmpty.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaClearImage_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaClearImage.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaClearImage(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaClearImage.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaClearImage.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageRawData_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageRawData.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageRawData(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageRawData.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageRawData.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageWidth_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageWidth.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageWidth(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageWidth.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageWidth.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageHeight_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageHeight.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageHeight(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageHeight.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageHeight.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageType_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageType.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageType(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageType.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageType.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageEncoded_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageEncoded.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageEncoded(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageEncoded.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageEncoded.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetImageEncodedSize_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetImageEncodedSize.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetImageEncodedSize(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetImageEncodedSize.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetImageEncodedSize.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetImageEncoded_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaImageBuffer__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.data
// LHG SEC DEF
    auto data_temp = from_json<unsigned char *>(__param["data"]);
    auto data = from_json_fix<unsigned char *>(data_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.size
// LHG SEC DEF
    auto size_temp = from_json<unsigned long long>(__param["size"]);
    auto size = from_json_fix<unsigned long long>(size_temp);
// LHG SEC END
    auto __return = MaaSetImageEncoded(
        handle,
        data,
        size
    );
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaCreateRectBuffer_Wrapper(json::object __param) {
    auto __return = MaaCreateRectBuffer(

    );
// LHG SEC BEGIN lhg.impl.MaaCreateRectBuffer.return
// LHG SEC DEF
    auto __ret = MaaRect__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreateRectBuffer.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaDestroyRectBuffer_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaDestroyRectBuffer.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    MaaRect *handle;
    MaaRect__OpaqueManager.del(handle_id, handle);
// LHG SEC END
    MaaDestroyRectBuffer(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaDestroyRectBuffer.return
// LHG SEC DEF

// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDestroyRectBuffer.final
// LHG SEC DEF
    return json::object {};
// LHG SEC END
}

std::optional<json::object> MaaGetRectX_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetRectX.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetRectX(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetRectX.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetRectX.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetRectY_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetRectY.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetRectY(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetRectY.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetRectY.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetRectW_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetRectW.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetRectW(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetRectW.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetRectW.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaGetRectH_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaGetRectH.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
    auto __return = MaaGetRectH(
        handle
    );
// LHG SEC BEGIN lhg.impl.MaaGetRectH.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaGetRectH.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetRectX_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetRectX.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectX.arg.value
// LHG SEC DEF
    auto value_temp = from_json<int>(__param["value"]);
    auto value = from_json_fix<int>(value_temp);
// LHG SEC END
    auto __return = MaaSetRectX(
        handle,
        value
    );
// LHG SEC BEGIN lhg.impl.MaaSetRectX.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectX.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetRectY_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetRectY.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectY.arg.value
// LHG SEC DEF
    auto value_temp = from_json<int>(__param["value"]);
    auto value = from_json_fix<int>(value_temp);
// LHG SEC END
    auto __return = MaaSetRectY(
        handle,
        value
    );
// LHG SEC BEGIN lhg.impl.MaaSetRectY.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectY.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetRectW_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetRectW.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectW.arg.value
// LHG SEC DEF
    auto value_temp = from_json<int>(__param["value"]);
    auto value = from_json_fix<int>(value_temp);
// LHG SEC END
    auto __return = MaaSetRectW(
        handle,
        value
    );
// LHG SEC BEGIN lhg.impl.MaaSetRectW.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectW.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetRectH_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetRectH.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaRect__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectH.arg.value
// LHG SEC DEF
    auto value_temp = from_json<int>(__param["value"]);
    auto value = from_json_fix<int>(value_temp);
// LHG SEC END
    auto __return = MaaSetRectH(
        handle,
        value
    );
// LHG SEC BEGIN lhg.impl.MaaSetRectH.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetRectH.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaVersion_Wrapper(json::object __param) {
    auto __return = MaaVersion(

    );
// LHG SEC BEGIN lhg.impl.MaaVersion.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaVersion.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaSetGlobalOption_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.key
// LHG SEC DEF
    auto key_temp = from_json<int>(__param["key"]);
    auto key = from_json_fix<int>(key_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.value
// LHG SEC DEF
    auto value_temp = from_json<void *>(__param["value"]);
    auto value = from_json_fix<void *>(value_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.val_size
// LHG SEC DEF
    auto val_size_temp = from_json<unsigned long long>(__param["val_size"]);
    auto val_size = from_json_fix<unsigned long long>(val_size_temp);
// LHG SEC END
    auto __return = MaaSetGlobalOption(
        key,
        value,
        val_size
    );
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitInit_Wrapper(json::object __param) {
    auto __return = MaaToolKitInit(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitInit.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitInit.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitUninit_Wrapper(json::object __param) {
    auto __return = MaaToolKitUninit(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitUninit.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUninit.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindDevice_Wrapper(json::object __param) {
    auto __return = MaaToolKitFindDevice(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDevice.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDevice.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindDeviceWithAdb_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDeviceWithAdb.arg.adb_path
// LHG SEC DEF
    auto adb_path_temp = from_json<const char *>(__param["adb_path"]);
    auto adb_path = from_json_fix<const char *>(adb_path_temp);
// LHG SEC END
    auto __return = MaaToolKitFindDeviceWithAdb(
        adb_path
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDeviceWithAdb.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDeviceWithAdb.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceName_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceName.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetDeviceName(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceName.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceName.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbPath_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbPath.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetDeviceAdbPath(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbPath.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbPath.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbSerial_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbSerial.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetDeviceAdbSerial(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbSerial.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbSerial.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbControllerType_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbControllerType.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetDeviceAdbControllerType(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbControllerType.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbControllerType.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbConfig_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbConfig.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetDeviceAdbConfig(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbConfig.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbConfig.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindWindow_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.arg.class_name
// LHG SEC DEF
    auto class_name_temp = from_json<const char *>(__param["class_name"]);
    auto class_name = from_json_fix<const char *>(class_name_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.arg.window_name
// LHG SEC DEF
    auto window_name_temp = from_json<const char *>(__param["window_name"]);
    auto window_name = from_json_fix<const char *>(window_name_temp);
// LHG SEC END
    auto __return = MaaToolKitFindWindow(
        class_name,
        window_name
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitSearchWindow_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.arg.class_name
// LHG SEC DEF
    auto class_name_temp = from_json<const char *>(__param["class_name"]);
    auto class_name = from_json_fix<const char *>(class_name_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.arg.window_name
// LHG SEC DEF
    auto window_name_temp = from_json<const char *>(__param["window_name"]);
    auto window_name = from_json_fix<const char *>(window_name_temp);
// LHG SEC END
    auto __return = MaaToolKitSearchWindow(
        class_name,
        window_name
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetWindow_Wrapper(json::object __param) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetWindow.arg.index
// LHG SEC DEF
    auto index_temp = from_json<unsigned long long>(__param["index"]);
    auto index = from_json_fix<unsigned long long>(index_temp);
// LHG SEC END
    auto __return = MaaToolKitGetWindow(
        index
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetWindow.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetWindow.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetCursorWindow_Wrapper(json::object __param) {
    auto __return = MaaToolKitGetCursorWindow(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetCursorWindow.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetCursorWindow.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) } };
// LHG SEC END
}

bool handle_request(Context& ctx, UrlSegments segs) {
    // callback MaaAPICallback
    if (handle_callback("MaaAPICallback", MaaAPICallback__Manager, ctx, segs, [](const auto& args) {
        auto v0 = std::get<0>(args);
        auto v1 = std::get<1>(args);
        return json::object {
            { "msg", v0 },
            { "details_json", v1 },
        };
    })) {
        return true;
    }
    // MaaAdbControllerCreate /maa/adb/controller/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("adb") && segs.enter_path("controller") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaAdbControllerCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaWin32ControllerCreate /maa/win32/controller/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("win32") && segs.enter_path("controller") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaWin32ControllerCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaAdbControllerCreateV2 /maa/adb/controller/create/v2
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("adb") && segs.enter_path("controller") && segs.enter_path("create") && segs.enter_path("v2") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaAdbControllerCreateV2_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaThriftControllerCreate /maa/thrift/controller/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("thrift") && segs.enter_path("controller") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaThriftControllerCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaDbgControllerCreate /maa/dbg/controller/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("dbg") && segs.enter_path("controller") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaDbgControllerCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerDestroy /maa/controller/destroy
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("destroy") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerDestroy_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerSetOption /maa/controller/set/option
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("set") && segs.enter_path("option") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerSetOption_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostConnection /maa/controller/post/connection
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("connection") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostConnection_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostClick /maa/controller/post/click
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("click") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostClick_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostSwipe /maa/controller/post/swipe
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("swipe") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostSwipe_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostPressKey /maa/controller/post/press/key
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("press") && segs.enter_path("key") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostPressKey_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostTouchDown /maa/controller/post/touch/down
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("touch") && segs.enter_path("down") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostTouchDown_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostTouchMove /maa/controller/post/touch/move
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("touch") && segs.enter_path("move") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostTouchMove_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostTouchUp /maa/controller/post/touch/up
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("touch") && segs.enter_path("up") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostTouchUp_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerPostScreencap /maa/controller/post/screencap
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("post") && segs.enter_path("screencap") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerPostScreencap_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerStatus /maa/controller/status
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("status") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerStatus_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerWait /maa/controller/wait
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("wait") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerWait_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerConnected /maa/controller/connected
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("connected") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerConnected_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerGetImage /maa/controller/get/image
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("get") && segs.enter_path("image") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerGetImage_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaControllerGetUUID /maa/controller/get/uuid
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("controller") && segs.enter_path("get") && segs.enter_path("uuid") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaControllerGetUUID_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaCreate /maa/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaDestroy /maa/destroy
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("destroy") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaDestroy_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetOption /maa/set/option
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("option") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetOption_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaBindResource /maa/bind/resource
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("bind") && segs.enter_path("resource") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaBindResource_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaBindController /maa/bind/controller
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("bind") && segs.enter_path("controller") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaBindController_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaInited /maa/inited
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("inited") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaInited_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaClearCustomRecognizer /maa/clear/custom/recognizer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("clear") && segs.enter_path("custom") && segs.enter_path("recognizer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaClearCustomRecognizer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaClearCustomAction /maa/clear/custom/action
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("clear") && segs.enter_path("custom") && segs.enter_path("action") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaClearCustomAction_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaPostTask /maa/post/task
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("post") && segs.enter_path("task") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaPostTask_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetTaskParam /maa/set/task/param
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("task") && segs.enter_path("param") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetTaskParam_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaTaskStatus /maa/task/status
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("task") && segs.enter_path("status") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaTaskStatus_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaWaitTask /maa/wait/task
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("wait") && segs.enter_path("task") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaWaitTask_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaTaskAllFinished /maa/task/all/finished
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("task") && segs.enter_path("all") && segs.enter_path("finished") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaTaskAllFinished_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaStop /maa/stop
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("stop") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaStop_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetResource /maa/get/resource
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("resource") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetResource_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetController /maa/get/controller
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("controller") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetController_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceCreate /maa/resource/create
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("create") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceCreate_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceDestroy /maa/resource/destroy
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("destroy") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceDestroy_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourcePostPath /maa/resource/post/path
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("post") && segs.enter_path("path") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourcePostPath_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceStatus /maa/resource/status
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("status") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceStatus_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceWait /maa/resource/wait
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("wait") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceWait_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceLoaded /maa/resource/loaded
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("loaded") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceLoaded_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceSetOption /maa/resource/set/option
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("set") && segs.enter_path("option") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceSetOption_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceGetHash /maa/resource/get/hash
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("get") && segs.enter_path("hash") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceGetHash_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaResourceGetTaskList /maa/resource/get/task/list
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("resource") && segs.enter_path("get") && segs.enter_path("task") && segs.enter_path("list") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaResourceGetTaskList_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaCreateStringBuffer /maa/create/string/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("create") && segs.enter_path("string") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaCreateStringBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaDestroyStringBuffer /maa/destroy/string/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("destroy") && segs.enter_path("string") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaDestroyStringBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaIsStringEmpty /maa/is/string/empty
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("is") && segs.enter_path("string") && segs.enter_path("empty") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaIsStringEmpty_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaClearString /maa/clear/string
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("clear") && segs.enter_path("string") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaClearString_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetString /maa/get/string
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("string") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetString_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetStringSize /maa/get/string/size
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("string") && segs.enter_path("size") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetStringSize_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetString /maa/set/string
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("string") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetString_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetStringEx /maa/set/string/ex
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("string") && segs.enter_path("ex") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetStringEx_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaCreateImageBuffer /maa/create/image/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("create") && segs.enter_path("image") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaCreateImageBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaDestroyImageBuffer /maa/destroy/image/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("destroy") && segs.enter_path("image") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaDestroyImageBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaIsImageEmpty /maa/is/image/empty
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("is") && segs.enter_path("image") && segs.enter_path("empty") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaIsImageEmpty_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaClearImage /maa/clear/image
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("clear") && segs.enter_path("image") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaClearImage_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageRawData /maa/get/image/raw/data
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("raw") && segs.enter_path("data") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageRawData_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageWidth /maa/get/image/width
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("width") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageWidth_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageHeight /maa/get/image/height
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("height") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageHeight_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageType /maa/get/image/type
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("type") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageType_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageEncoded /maa/get/image/encoded
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("encoded") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageEncoded_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetImageEncodedSize /maa/get/image/encoded/size
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("image") && segs.enter_path("encoded") && segs.enter_path("size") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetImageEncodedSize_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetImageEncoded /maa/set/image/encoded
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("image") && segs.enter_path("encoded") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetImageEncoded_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaCreateRectBuffer /maa/create/rect/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("create") && segs.enter_path("rect") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaCreateRectBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaDestroyRectBuffer /maa/destroy/rect/buffer
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("destroy") && segs.enter_path("rect") && segs.enter_path("buffer") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaDestroyRectBuffer_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetRectX /maa/get/rect/x
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("rect") && segs.enter_path("x") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetRectX_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetRectY /maa/get/rect/y
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("rect") && segs.enter_path("y") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetRectY_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetRectW /maa/get/rect/w
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("rect") && segs.enter_path("w") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetRectW_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaGetRectH /maa/get/rect/h
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("get") && segs.enter_path("rect") && segs.enter_path("h") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaGetRectH_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetRectX /maa/set/rect/x
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("rect") && segs.enter_path("x") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetRectX_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetRectY /maa/set/rect/y
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("rect") && segs.enter_path("y") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetRectY_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetRectW /maa/set/rect/w
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("rect") && segs.enter_path("w") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetRectW_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetRectH /maa/set/rect/h
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("rect") && segs.enter_path("h") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetRectH_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaVersion /maa/version
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("version") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaVersion_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaSetGlobalOption /maa/set/global/option
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("set") && segs.enter_path("global") && segs.enter_path("option") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaSetGlobalOption_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitInit /maa/tool/kit/init
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("init") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitInit_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitUninit /maa/tool/kit/uninit
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("uninit") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitUninit_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitFindDevice /maa/tool/kit/find/device
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("find") && segs.enter_path("device") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitFindDevice_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitFindDeviceWithAdb /maa/tool/kit/find/device/with/adb
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("find") && segs.enter_path("device") && segs.enter_path("with") && segs.enter_path("adb") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitFindDeviceWithAdb_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetDeviceName /maa/tool/kit/get/device/name
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("device") && segs.enter_path("name") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetDeviceName_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetDeviceAdbPath /maa/tool/kit/get/device/adb/path
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("device") && segs.enter_path("adb") && segs.enter_path("path") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetDeviceAdbPath_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetDeviceAdbSerial /maa/tool/kit/get/device/adb/serial
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("device") && segs.enter_path("adb") && segs.enter_path("serial") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetDeviceAdbSerial_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetDeviceAdbControllerType /maa/tool/kit/get/device/adb/controller/type
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("device") && segs.enter_path("adb") && segs.enter_path("controller") && segs.enter_path("type") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetDeviceAdbControllerType_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetDeviceAdbConfig /maa/tool/kit/get/device/adb/config
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("device") && segs.enter_path("adb") && segs.enter_path("config") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetDeviceAdbConfig_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitFindWindow /maa/tool/kit/find/window
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("find") && segs.enter_path("window") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitFindWindow_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitSearchWindow /maa/tool/kit/search/window
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("search") && segs.enter_path("window") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitSearchWindow_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetWindow /maa/tool/kit/get/window
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("window") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetWindow_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    // MaaToolKitGetCursorWindow /maa/tool/kit/get/cursor/window
    segs.reset();
    if (segs.enter_path("maa") && segs.enter_path("tool") && segs.enter_path("kit") && segs.enter_path("get") && segs.enter_path("cursor") && segs.enter_path("window") && segs.end()) {
        auto body = json::parse(ctx.req_.body());
        auto& obj = body.value().as_object();
        auto ret = MaaToolKitGetCursorWindow_Wrapper(obj);
        ctx.json_body(ret.value());
        return true;
    }
    return false;
}
