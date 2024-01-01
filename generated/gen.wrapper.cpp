// clang-format off

#include "helper.h"
#define LHG_PROCESS

// LHG SEC BEGIN lhg.include
#include "MaaFramework/MaaAPI.h"
#include "MaaToolKit/MaaToolKitAPI.h"
// LHG SEC END

// LHG SEC BEGIN lhg.custom.global
inline std::string to_string_and_del(MaaStringBufferHandle handle) {
    size_t len = MaaGetStringSize(handle);
    std::string res(MaaGetString(handle), len);
    MaaDestroyStringBuffer(handle);
    return res;
}

template <>
inline MaaStringBuffer *output_prepare<MaaStringBuffer *>() {
    return MaaCreateStringBuffer();
}

template <>
inline json::value output_finalize<MaaStringBuffer *>(MaaStringBuffer *v) {
    size_t len = MaaGetStringSize(v);
    std::string res(MaaGetString(v), len);
    MaaDestroyStringBuffer(v);
    return res;
}
// LHG SEC END

static callback_manager<void (*)(const char *, const char *, void *)> MaaAPICallback__Manager;

static HandleManager<MaaControllerAPI *> MaaControllerAPI__OpaqueManager;

static HandleManager<MaaResourceAPI *> MaaResourceAPI__OpaqueManager;

static HandleManager<MaaInstanceAPI *> MaaInstanceAPI__OpaqueManager;

static HandleManager<MaaImageBuffer *> MaaImageBuffer__OpaqueManager;

std::optional<json::object> MaaAdbControllerCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.adb_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["adb_path"])) {
            __error = "adb_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.address.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["address"])) {
            __error = "address should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.type.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["type"])) {
            __error = "type should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.config.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["config"])) {
            __error = "config should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaWin32ControllerCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.hWnd.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["hWnd"])) {
            __error = "hWnd should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.type.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["type"])) {
            __error = "type should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWin32ControllerCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaAdbControllerCreateV2_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.adb_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["adb_path"])) {
            __error = "adb_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.address.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["address"])) {
            __error = "address should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.type.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["type"])) {
            __error = "type should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.config.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["config"])) {
            __error = "config should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.agent_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["agent_path"])) {
            __error = "agent_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaAdbControllerCreateV2.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaThriftControllerCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.type.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["type"])) {
            __error = "type should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.host.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["host"])) {
            __error = "host should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.port.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["port"])) {
            __error = "port should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.config.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["config"])) {
            __error = "config should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaThriftControllerCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaDbgControllerCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.read_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["read_path"])) {
            __error = "read_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.write_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["write_path"])) {
            __error = "write_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.type.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["type"])) {
            __error = "type should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.config.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["config"])) {
            __error = "config should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaDbgControllerCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerDestroy_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerDestroy.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", json::value(json::value::value_type::null) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerSetOption_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.key.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["key"])) {
            __error = "key should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.value.check
// LHG SEC DEF
    if constexpr (check_var_t<void *>::value) {
        if (!check_var<void *>(__param["value"])) {
            __error = "value should be void *";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.val_size.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["val_size"])) {
            __error = "val_size should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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

    std::string temp_str;
    bool temp_bool;
    int32_t temp_i32;
    void *value = 0;
    uint64_t val_size = 0;
    switch (key) {
        case MaaCtrlOption_DefaultAppPackageEntry:
        case MaaCtrlOption_DefaultAppPackage:
            temp_str = __param["value"].as_string();
            value = const_cast<char *>(temp_str.c_str());
            val_size = temp_str.size();
            break;
        case MaaCtrlOption_ScreenshotTargetLongSide:
        case MaaCtrlOption_ScreenshotTargetShortSide:
            temp_i32 = __param["value"].as_integer();
            value = &temp_i32;
            val_size = 4;
            break;
        case MaaCtrlOption_Recording:
            temp_bool = __param["value"].as_boolean();
            value = &temp_bool;
            val_size = 1;
            break;
        default:
            return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerSetOption.arg.val_size

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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostConnection_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostConnection.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostClick_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.x.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["x"])) {
            __error = "x should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostClick.arg.y.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["y"])) {
            __error = "y should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostSwipe_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.x1.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["x1"])) {
            __error = "x1 should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.y1.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["y1"])) {
            __error = "y1 should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.x2.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["x2"])) {
            __error = "x2 should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.y2.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["y2"])) {
            __error = "y2 should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostSwipe.arg.duration.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["duration"])) {
            __error = "duration should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostPressKey_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostPressKey.arg.keycode.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["keycode"])) {
            __error = "keycode should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostInputText_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.arg.text.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["text"])) {
            __error = "text should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.arg.text
// LHG SEC DEF
    auto text_temp = from_json<const char *>(__param["text"]);
    auto text = from_json_fix<const char *>(text_temp);
// LHG SEC END
    auto __return = MaaControllerPostInputText(
        ctrl,
        text
    );
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostInputText.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchDown_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.contact.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["contact"])) {
            __error = "contact should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.x.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["x"])) {
            __error = "x should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.y.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["y"])) {
            __error = "y should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchDown.arg.pressure.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["pressure"])) {
            __error = "pressure should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchMove_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.contact.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["contact"])) {
            __error = "contact should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.x.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["x"])) {
            __error = "x should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.y.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["y"])) {
            __error = "y should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchMove.arg.pressure.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["pressure"])) {
            __error = "pressure should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostTouchUp_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerPostTouchUp.arg.contact.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["contact"])) {
            __error = "contact should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerPostScreencap_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerPostScreencap.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerStatus_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerStatus.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerWait_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerWait.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerWait.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerConnected_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerConnected.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerGetImage_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetImage.arg.buffer.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["buffer"])) {
        __error = "buffer should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaControllerGetUUID_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.arg.ctrl
// LHG SEC DEF
    auto ctrl_id = __param["ctrl"].as_string();
    auto ctrl = MaaControllerAPI__OpaqueManager.get(ctrl_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaControllerGetUUID.arg.buffer
// LHG SEC DEF
    auto buffer = output_prepare<MaaStringBuffer *>();
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
    return json::object { { "return", to_json(__ret) }, { "buffer", output_finalize(buffer) } };
// LHG SEC END
}

std::optional<json::object> MaaCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaDestroy_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaDestroy.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", json::value(json::value::value_type::null) },  };
// LHG SEC END
}

std::optional<json::object> MaaSetOption_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.key.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["key"])) {
            __error = "key should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.value.check
// LHG SEC DEF
    if constexpr (check_var_t<void *>::value) {
        if (!check_var<void *>(__param["value"])) {
            __error = "value should be void *";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.val_size.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["val_size"])) {
            __error = "val_size should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    void *value;
    uint64_t val_size;
    return std::nullopt;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetOption.arg.val_size

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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaBindResource_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaBindResource.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindResource.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaBindController_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaBindController.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaBindController.arg.ctrl.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["ctrl"])) {
        __error = "ctrl should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaInited_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaInited.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaClearCustomRecognizer_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaClearCustomRecognizer.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaClearCustomAction_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaClearCustomAction.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaPostTask_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.entry.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["entry"])) {
            __error = "entry should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostTask.arg.param.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["param"])) {
            __error = "param should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaSetTaskParam_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetTaskParam.arg.param.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["param"])) {
            __error = "param should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaTaskStatus_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaTaskStatus.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaWaitTask_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaWaitTask.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaWaitTask.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaTaskAllFinished_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaTaskAllFinished.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaPostStop_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaPostStop.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostStop.arg.inst
// LHG SEC DEF
    auto inst_id = __param["inst"].as_string();
    auto inst = MaaInstanceAPI__OpaqueManager.get(inst_id);
// LHG SEC END
    auto __return = MaaPostStop(
        inst
    );
// LHG SEC BEGIN lhg.impl.MaaPostStop.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaPostStop.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaStop_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaStop.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetResource_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetResource.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetController_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetController.arg.inst.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["inst"])) {
        __error = "inst should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceCreate_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceCreate.arg.callback_arg.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["null"])) {
        __error = "null should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceDestroy_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceDestroy.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", json::value(json::value::value_type::null) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourcePostPath_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourcePostPath.arg.path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["path"])) {
            __error = "path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceStatus_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceStatus.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceWait_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceWait.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceWait.arg.id.check
// LHG SEC DEF
    if constexpr (check_var_t<long long>::value) {
        if (!check_var<long long>(__param["id"])) {
            __error = "id should be long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceLoaded_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceLoaded.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceSetOption_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.key.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["key"])) {
            __error = "key should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.value.check
// LHG SEC DEF
    if constexpr (check_var_t<void *>::value) {
        if (!check_var<void *>(__param["value"])) {
            __error = "value should be void *";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.val_size.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["val_size"])) {
            __error = "val_size should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    void *value;
    uint64_t val_size;
    return std::nullopt;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceSetOption.arg.val_size

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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaResourceGetHash_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetHash.arg.buffer
// LHG SEC DEF
    auto buffer = output_prepare<MaaStringBuffer *>();
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
    return json::object { { "return", to_json(__ret) }, { "buffer", output_finalize(buffer) } };
// LHG SEC END
}

std::optional<json::object> MaaResourceGetTaskList_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.arg.res.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["res"])) {
        __error = "res should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.arg.res
// LHG SEC DEF
    auto res_id = __param["res"].as_string();
    auto res = MaaResourceAPI__OpaqueManager.get(res_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaResourceGetTaskList.arg.buffer
// LHG SEC DEF
    auto buffer = output_prepare<MaaStringBuffer *>();
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
    return json::object { { "return", to_json(__ret) }, { "buffer", output_finalize(buffer) } };
// LHG SEC END
}

std::optional<json::object> MaaCreateImageBuffer_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaCreateImageBuffer(

    );
// LHG SEC BEGIN lhg.impl.MaaCreateImageBuffer.return
// LHG SEC DEF
    auto __ret = MaaImageBuffer__OpaqueManager.add(__return);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaCreateImageBuffer.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaDestroyImageBuffer_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaDestroyImageBuffer.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", json::value(json::value::value_type::null) },  };
// LHG SEC END
}

std::optional<json::object> MaaIsImageEmpty_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaIsImageEmpty.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaClearImage_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaClearImage.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageRawData_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageRawData.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageWidth_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageWidth.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageHeight_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageHeight.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageType_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageType.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageEncoded_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageEncoded.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaGetImageEncodedSize_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaGetImageEncodedSize.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaSetImageEncoded_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.data.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned char *>::value) {
        if (!check_var<unsigned char *>(__param["data"])) {
            __error = "data should be unsigned char *";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetImageEncoded.arg.size.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["size"])) {
            __error = "size should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaVersion_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaVersion(

    );
// LHG SEC BEGIN lhg.impl.MaaVersion.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaVersion.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaSetGlobalOption_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.key.check
// LHG SEC DEF
    if constexpr (check_var_t<int>::value) {
        if (!check_var<int>(__param["key"])) {
            __error = "key should be int";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.value.check
// LHG SEC DEF
    if constexpr (check_var_t<void *>::value) {
        if (!check_var<void *>(__param["value"])) {
            __error = "value should be void *";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.val_size.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["val_size"])) {
            __error = "val_size should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.key
// LHG SEC DEF
    auto key_temp = from_json<int>(__param["key"]);
    auto key = from_json_fix<int>(key_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.value
    std::string temp_str;
    bool temp_bool;
    int32_t temp_i32;
    void *value = 0;
    uint64_t val_size = 0;
    switch (key) {
        case MaaGlobalOption_LogDir:
            temp_str = __param["value"].as_string();
            value = const_cast<char *>(temp_str.c_str());
            val_size = temp_str.size();
            break;
        case MaaGlobalOption_StdoutLevel:
            temp_i32 = __param["value"].as_integer();
            value = &temp_i32;
            val_size = 4;
            break;
        case MaaGlobalOption_SaveDraw:
        case MaaGlobalOption_Recording:
        case MaaGlobalOption_ShowHitDraw:
            temp_bool = __param["value"].as_boolean();
            value = &temp_bool;
            val_size = 1;
            break;
        default:
            return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaSetGlobalOption.arg.val_size

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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitInit_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitInit(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitInit.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitInit.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitUninit_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitUninit(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitUninit.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUninit.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindDevice_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitFindDevice(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDevice.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDevice.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindDeviceWithAdb_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitFindDeviceWithAdb.arg.adb_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["adb_path"])) {
            __error = "adb_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitPostFindDevice_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitPostFindDevice(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDevice.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDevice.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitPostFindDeviceWithAdb_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDeviceWithAdb.arg.adb_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["adb_path"])) {
            __error = "adb_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDeviceWithAdb.arg.adb_path
// LHG SEC DEF
    auto adb_path_temp = from_json<const char *>(__param["adb_path"]);
    auto adb_path = from_json_fix<const char *>(adb_path_temp);
// LHG SEC END
    auto __return = MaaToolKitPostFindDeviceWithAdb(
        adb_path
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDeviceWithAdb.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitPostFindDeviceWithAdb.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitIsFindDeviceCompleted_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitIsFindDeviceCompleted(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitIsFindDeviceCompleted.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitIsFindDeviceCompleted.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitWaitForFindDeviceToComplete_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitWaitForFindDeviceToComplete(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitWaitForFindDeviceToComplete.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitWaitForFindDeviceToComplete.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceCount_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitGetDeviceCount(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceCount.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceCount.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceName_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceName.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbPath_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbPath.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbSerial_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbSerial.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbControllerType_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbControllerType.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetDeviceAdbConfig_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetDeviceAdbConfig.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitRegisterCustomRecognizerExecutor_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["recognizer_name"])) {
            __error = "recognizer_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_exec_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["recognizer_exec_path"])) {
            __error = "recognizer_exec_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_exec_param_json.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["recognizer_exec_param_json"])) {
            __error = "recognizer_exec_param_json should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaInstanceAPI__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_name
// LHG SEC DEF
    auto recognizer_name_temp = from_json<const char *>(__param["recognizer_name"]);
    auto recognizer_name = from_json_fix<const char *>(recognizer_name_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_exec_path
// LHG SEC DEF
    auto recognizer_exec_path_temp = from_json<const char *>(__param["recognizer_exec_path"]);
    auto recognizer_exec_path = from_json_fix<const char *>(recognizer_exec_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.arg.recognizer_exec_param_json
// LHG SEC DEF
    auto recognizer_exec_param_json_temp = from_json<const char *>(__param["recognizer_exec_param_json"]);
    auto recognizer_exec_param_json = from_json_fix<const char *>(recognizer_exec_param_json_temp);
// LHG SEC END
    auto __return = MaaToolKitRegisterCustomRecognizerExecutor(
        handle,
        recognizer_name,
        recognizer_exec_path,
        recognizer_exec_param_json
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomRecognizerExecutor.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitUnregisterCustomRecognizerExecutor_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.arg.recognizer_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["recognizer_name"])) {
            __error = "recognizer_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaInstanceAPI__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.arg.recognizer_name
// LHG SEC DEF
    auto recognizer_name_temp = from_json<const char *>(__param["recognizer_name"]);
    auto recognizer_name = from_json_fix<const char *>(recognizer_name_temp);
// LHG SEC END
    auto __return = MaaToolKitUnregisterCustomRecognizerExecutor(
        handle,
        recognizer_name
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomRecognizerExecutor.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitRegisterCustomActionExecutor_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["action_name"])) {
            __error = "action_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_exec_path.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["action_exec_path"])) {
            __error = "action_exec_path should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_exec_param_json.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["action_exec_param_json"])) {
            __error = "action_exec_param_json should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaInstanceAPI__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_name
// LHG SEC DEF
    auto action_name_temp = from_json<const char *>(__param["action_name"]);
    auto action_name = from_json_fix<const char *>(action_name_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_exec_path
// LHG SEC DEF
    auto action_exec_path_temp = from_json<const char *>(__param["action_exec_path"]);
    auto action_exec_path = from_json_fix<const char *>(action_exec_path_temp);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.arg.action_exec_param_json
// LHG SEC DEF
    auto action_exec_param_json_temp = from_json<const char *>(__param["action_exec_param_json"]);
    auto action_exec_param_json = from_json_fix<const char *>(action_exec_param_json_temp);
// LHG SEC END
    auto __return = MaaToolKitRegisterCustomActionExecutor(
        handle,
        action_name,
        action_exec_path,
        action_exec_param_json
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitRegisterCustomActionExecutor.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitUnregisterCustomActionExecutor_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.arg.handle.check
// LHG SEC DEF
    if (!check_var<const char*>(__param["handle"])) {
        __error = "handle should be string";
        return std::nullopt;
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.arg.action_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["action_name"])) {
            __error = "action_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.arg.handle
// LHG SEC DEF
    auto handle_id = __param["handle"].as_string();
    auto handle = MaaInstanceAPI__OpaqueManager.get(handle_id);
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.arg.action_name
// LHG SEC DEF
    auto action_name_temp = from_json<const char *>(__param["action_name"]);
    auto action_name = from_json_fix<const char *>(action_name_temp);
// LHG SEC END
    auto __return = MaaToolKitUnregisterCustomActionExecutor(
        handle,
        action_name
    );
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitUnregisterCustomActionExecutor.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitFindWindow_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.arg.class_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["class_name"])) {
            __error = "class_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitFindWindow.arg.window_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["window_name"])) {
            __error = "window_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitSearchWindow_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.arg.class_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["class_name"])) {
            __error = "class_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitSearchWindow.arg.window_name.check
// LHG SEC DEF
    if constexpr (check_var_t<const char *>::value) {
        if (!check_var<const char *>(__param["window_name"])) {
            __error = "window_name should be string";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetWindow_Wrapper(json::object __param, std::string &__error) {
// LHG SEC BEGIN lhg.impl.MaaToolKitGetWindow.arg.index.check
// LHG SEC DEF
    if constexpr (check_var_t<unsigned long long>::value) {
        if (!check_var<unsigned long long>(__param["index"])) {
            __error = "index should be unsigned long long";
            return std::nullopt;
        }
    }
// LHG SEC END
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
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

std::optional<json::object> MaaToolKitGetCursorWindow_Wrapper(json::object __param, std::string &__error) {
    auto __return = MaaToolKitGetCursorWindow(

    );
// LHG SEC BEGIN lhg.impl.MaaToolKitGetCursorWindow.return
// LHG SEC DEF
    auto __ret = __return;
// LHG SEC END
// LHG SEC BEGIN lhg.impl.MaaToolKitGetCursorWindow.final
// LHG SEC DEF
    return json::object { { "return", to_json(__ret) },  };
// LHG SEC END
}

bool handle_request(Context& ctx, UrlSegments segs) {
    auto obj = json::parse(ctx.req_.body()).value_or(json::object {}).as_object();
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
    const static std::map<std::string, std::optional<json::object> (*)(json::object, std::string&)> wrappers = {
        { "MaaAdbControllerCreate", &MaaAdbControllerCreate_Wrapper },
        { "MaaWin32ControllerCreate", &MaaWin32ControllerCreate_Wrapper },
        { "MaaAdbControllerCreateV2", &MaaAdbControllerCreateV2_Wrapper },
        { "MaaThriftControllerCreate", &MaaThriftControllerCreate_Wrapper },
        { "MaaDbgControllerCreate", &MaaDbgControllerCreate_Wrapper },
        { "MaaControllerDestroy", &MaaControllerDestroy_Wrapper },
        { "MaaControllerSetOption", &MaaControllerSetOption_Wrapper },
        { "MaaControllerPostConnection", &MaaControllerPostConnection_Wrapper },
        { "MaaControllerPostClick", &MaaControllerPostClick_Wrapper },
        { "MaaControllerPostSwipe", &MaaControllerPostSwipe_Wrapper },
        { "MaaControllerPostPressKey", &MaaControllerPostPressKey_Wrapper },
        { "MaaControllerPostInputText", &MaaControllerPostInputText_Wrapper },
        { "MaaControllerPostTouchDown", &MaaControllerPostTouchDown_Wrapper },
        { "MaaControllerPostTouchMove", &MaaControllerPostTouchMove_Wrapper },
        { "MaaControllerPostTouchUp", &MaaControllerPostTouchUp_Wrapper },
        { "MaaControllerPostScreencap", &MaaControllerPostScreencap_Wrapper },
        { "MaaControllerStatus", &MaaControllerStatus_Wrapper },
        { "MaaControllerWait", &MaaControllerWait_Wrapper },
        { "MaaControllerConnected", &MaaControllerConnected_Wrapper },
        { "MaaControllerGetImage", &MaaControllerGetImage_Wrapper },
        { "MaaControllerGetUUID", &MaaControllerGetUUID_Wrapper },
        { "MaaCreate", &MaaCreate_Wrapper },
        { "MaaDestroy", &MaaDestroy_Wrapper },
        { "MaaSetOption", &MaaSetOption_Wrapper },
        { "MaaBindResource", &MaaBindResource_Wrapper },
        { "MaaBindController", &MaaBindController_Wrapper },
        { "MaaInited", &MaaInited_Wrapper },
        { "MaaClearCustomRecognizer", &MaaClearCustomRecognizer_Wrapper },
        { "MaaClearCustomAction", &MaaClearCustomAction_Wrapper },
        { "MaaPostTask", &MaaPostTask_Wrapper },
        { "MaaSetTaskParam", &MaaSetTaskParam_Wrapper },
        { "MaaTaskStatus", &MaaTaskStatus_Wrapper },
        { "MaaWaitTask", &MaaWaitTask_Wrapper },
        { "MaaTaskAllFinished", &MaaTaskAllFinished_Wrapper },
        { "MaaPostStop", &MaaPostStop_Wrapper },
        { "MaaStop", &MaaStop_Wrapper },
        { "MaaGetResource", &MaaGetResource_Wrapper },
        { "MaaGetController", &MaaGetController_Wrapper },
        { "MaaResourceCreate", &MaaResourceCreate_Wrapper },
        { "MaaResourceDestroy", &MaaResourceDestroy_Wrapper },
        { "MaaResourcePostPath", &MaaResourcePostPath_Wrapper },
        { "MaaResourceStatus", &MaaResourceStatus_Wrapper },
        { "MaaResourceWait", &MaaResourceWait_Wrapper },
        { "MaaResourceLoaded", &MaaResourceLoaded_Wrapper },
        { "MaaResourceSetOption", &MaaResourceSetOption_Wrapper },
        { "MaaResourceGetHash", &MaaResourceGetHash_Wrapper },
        { "MaaResourceGetTaskList", &MaaResourceGetTaskList_Wrapper },
        { "MaaCreateImageBuffer", &MaaCreateImageBuffer_Wrapper },
        { "MaaDestroyImageBuffer", &MaaDestroyImageBuffer_Wrapper },
        { "MaaIsImageEmpty", &MaaIsImageEmpty_Wrapper },
        { "MaaClearImage", &MaaClearImage_Wrapper },
        { "MaaGetImageRawData", &MaaGetImageRawData_Wrapper },
        { "MaaGetImageWidth", &MaaGetImageWidth_Wrapper },
        { "MaaGetImageHeight", &MaaGetImageHeight_Wrapper },
        { "MaaGetImageType", &MaaGetImageType_Wrapper },
        { "MaaGetImageEncoded", &MaaGetImageEncoded_Wrapper },
        { "MaaGetImageEncodedSize", &MaaGetImageEncodedSize_Wrapper },
        { "MaaSetImageEncoded", &MaaSetImageEncoded_Wrapper },
        { "MaaVersion", &MaaVersion_Wrapper },
        { "MaaSetGlobalOption", &MaaSetGlobalOption_Wrapper },
        { "MaaToolKitInit", &MaaToolKitInit_Wrapper },
        { "MaaToolKitUninit", &MaaToolKitUninit_Wrapper },
        { "MaaToolKitFindDevice", &MaaToolKitFindDevice_Wrapper },
        { "MaaToolKitFindDeviceWithAdb", &MaaToolKitFindDeviceWithAdb_Wrapper },
        { "MaaToolKitPostFindDevice", &MaaToolKitPostFindDevice_Wrapper },
        { "MaaToolKitPostFindDeviceWithAdb", &MaaToolKitPostFindDeviceWithAdb_Wrapper },
        { "MaaToolKitIsFindDeviceCompleted", &MaaToolKitIsFindDeviceCompleted_Wrapper },
        { "MaaToolKitWaitForFindDeviceToComplete", &MaaToolKitWaitForFindDeviceToComplete_Wrapper },
        { "MaaToolKitGetDeviceCount", &MaaToolKitGetDeviceCount_Wrapper },
        { "MaaToolKitGetDeviceName", &MaaToolKitGetDeviceName_Wrapper },
        { "MaaToolKitGetDeviceAdbPath", &MaaToolKitGetDeviceAdbPath_Wrapper },
        { "MaaToolKitGetDeviceAdbSerial", &MaaToolKitGetDeviceAdbSerial_Wrapper },
        { "MaaToolKitGetDeviceAdbControllerType", &MaaToolKitGetDeviceAdbControllerType_Wrapper },
        { "MaaToolKitGetDeviceAdbConfig", &MaaToolKitGetDeviceAdbConfig_Wrapper },
        { "MaaToolKitRegisterCustomRecognizerExecutor", &MaaToolKitRegisterCustomRecognizerExecutor_Wrapper },
        { "MaaToolKitUnregisterCustomRecognizerExecutor", &MaaToolKitUnregisterCustomRecognizerExecutor_Wrapper },
        { "MaaToolKitRegisterCustomActionExecutor", &MaaToolKitRegisterCustomActionExecutor_Wrapper },
        { "MaaToolKitUnregisterCustomActionExecutor", &MaaToolKitUnregisterCustomActionExecutor_Wrapper },
        { "MaaToolKitFindWindow", &MaaToolKitFindWindow_Wrapper },
        { "MaaToolKitSearchWindow", &MaaToolKitSearchWindow_Wrapper },
        { "MaaToolKitGetWindow", &MaaToolKitGetWindow_Wrapper },
        { "MaaToolKitGetCursorWindow", &MaaToolKitGetCursorWindow_Wrapper },
    };
    std::string api;
    if (segs.enter_id(api) && segs.end()) {
        auto it = wrappers.find(api);
        if (it == wrappers.end()) {
          return false;
        }
        std::string err;
        auto ret = (it->second)(obj, err);
        if (ret.has_value()) {
            ctx.json_body(json::object { { "data", ret.value() } });
        } else {
            ctx.json_body(json::object { { "error", err } });
        }
        return true;
    }
    return false;
}
