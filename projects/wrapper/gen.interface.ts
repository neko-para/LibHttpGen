export default {
  MaaAdbControllerCreate: {
    input: {
      adb_path: 'string',
      address: 'string',
      callback: 'string@MaaAPICallback',
      config: 'string',
      type: 'number'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  },
  MaaAdbControllerCreateV2: {
    input: {
      adb_path: 'string',
      address: 'string',
      agent_path: 'string',
      callback: 'string@MaaAPICallback',
      config: 'string',
      type: 'number'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  },
  MaaBindController: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaBindResource: {
    input: {
      inst: 'string@MaaInstanceAPI',
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaClearCustomAction: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaClearCustomRecognizer: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaClearImage: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerConnected: {
    input: {
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerDestroy: {
    input: {
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'never'
      },
      error: 'string'
    }
  },
  MaaControllerGetImage: {
    input: {
      buffer: 'string@MaaImageBuffer',
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerGetUUID: {
    input: {
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        buffer: 'string',
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostClick: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      x: 'number',
      y: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostConnection: {
    input: {
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostInputText: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      text: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostPressKey: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      keycode: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostScreencap: {
    input: {
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostSwipe: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      duration: 'number',
      x1: 'number',
      x2: 'number',
      y1: 'number',
      y2: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostTouchDown: {
    input: {
      contact: 'number',
      ctrl: 'string@MaaControllerAPI',
      pressure: 'number',
      x: 'number',
      y: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostTouchMove: {
    input: {
      contact: 'number',
      ctrl: 'string@MaaControllerAPI',
      pressure: 'number',
      x: 'number',
      y: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerPostTouchUp: {
    input: {
      contact: 'number',
      ctrl: 'string@MaaControllerAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerSetOption: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      key: 'number',
      value: 'string|number|boolean'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerStatus: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      id: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaControllerWait: {
    input: {
      ctrl: 'string@MaaControllerAPI',
      id: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaCreate: {
    input: {
      callback: 'string@MaaAPICallback'
    },
    output: {
      data: {
        return: 'string@MaaInstanceAPI'
      },
      error: 'string'
    }
  },
  MaaCreateImageBuffer: {
    input: {},
    output: {
      data: {
        return: 'string@MaaImageBuffer'
      },
      error: 'string'
    }
  },
  MaaDbgControllerCreate: {
    input: {
      callback: 'string@MaaAPICallback',
      config: 'string',
      read_path: 'string',
      type: 'number',
      write_path: 'string'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  },
  MaaDestroy: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'never'
      },
      error: 'string'
    }
  },
  MaaDestroyImageBuffer: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'never'
      },
      error: 'string'
    }
  },
  MaaGetController: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  },
  MaaGetImageEncoded: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'string@buffer'
      },
      error: 'string'
    }
  },
  MaaGetImageHeight: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaGetImageType: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaGetImageWidth: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaGetResource: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'string@MaaResourceAPI'
      },
      error: 'string'
    }
  },
  MaaInited: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaIsImageEmpty: {
    input: {
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaPostStop: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaPostTask: {
    input: {
      entry: 'string',
      inst: 'string@MaaInstanceAPI',
      param: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceCreate: {
    input: {
      callback: 'string@MaaAPICallback'
    },
    output: {
      data: {
        return: 'string@MaaResourceAPI'
      },
      error: 'string'
    }
  },
  MaaResourceDestroy: {
    input: {
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'never'
      },
      error: 'string'
    }
  },
  MaaResourceGetHash: {
    input: {
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        buffer: 'string',
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceGetTaskList: {
    input: {
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        buffer: 'string',
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceLoaded: {
    input: {
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourcePostPath: {
    input: {
      path: 'string',
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceSetOption: {
    input: {
      key: 'number',
      res: 'string@MaaResourceAPI',
      value: 'string|number|boolean'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceStatus: {
    input: {
      id: 'number',
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaResourceWait: {
    input: {
      id: 'number',
      res: 'string@MaaResourceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaSetGlobalOption: {
    input: {
      key: 'number',
      value: 'string|number|boolean'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaSetImageEncoded: {
    input: {
      data: 'string@buffer',
      handle: 'string@MaaImageBuffer'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaSetOption: {
    input: {
      inst: 'string@MaaInstanceAPI',
      key: 'number',
      value: 'string|number|boolean'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaSetTaskParam: {
    input: {
      id: 'number',
      inst: 'string@MaaInstanceAPI',
      param: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaStop: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaTaskAllFinished: {
    input: {
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaTaskStatus: {
    input: {
      id: 'number',
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaThriftControllerCreate: {
    input: {
      callback: 'string@MaaAPICallback',
      config: 'string',
      host: 'string',
      port: 'number',
      type: 'number'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  },
  MaaToolkitFindDevice: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitFindDeviceWithAdb: {
    input: {
      adb_path: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitFindWindow: {
    input: {
      class_name: 'string',
      window_name: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitGetCursorWindow: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceAdbConfig: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'string'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceAdbControllerType: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceAdbPath: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'string'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceAdbSerial: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'string'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceCount: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitGetDeviceName: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'string'
      },
      error: 'string'
    }
  },
  MaaToolkitGetWindow: {
    input: {
      index: 'number'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitInit: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitIsFindDeviceCompleted: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitPostFindDevice: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitPostFindDeviceWithAdb: {
    input: {
      adb_path: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitRegisterCustomActionExecutor: {
    input: {
      action_exec_param_json: 'string',
      action_exec_path: 'string',
      action_name: 'string',
      handle: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitRegisterCustomRecognizerExecutor: {
    input: {
      handle: 'string@MaaInstanceAPI',
      recognizer_exec_param_json: 'string',
      recognizer_exec_path: 'string',
      recognizer_name: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitSearchWindow: {
    input: {
      class_name: 'string',
      window_name: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitUninit: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitUnregisterCustomActionExecutor: {
    input: {
      action_name: 'string',
      handle: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitUnregisterCustomRecognizerExecutor: {
    input: {
      handle: 'string@MaaInstanceAPI',
      recognizer_name: 'string'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaToolkitWaitForFindDeviceToComplete: {
    input: {},
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaVersion: {
    input: {},
    output: {
      data: {
        return: 'string'
      },
      error: 'string'
    }
  },
  MaaWaitTask: {
    input: {
      id: 'number',
      inst: 'string@MaaInstanceAPI'
    },
    output: {
      data: {
        return: 'number'
      },
      error: 'string'
    }
  },
  MaaWin32ControllerCreate: {
    input: {
      callback: 'string@MaaAPICallback',
      hWnd: 'number',
      type: 'number'
    },
    output: {
      data: {
        return: 'string@MaaControllerAPI'
      },
      error: 'string'
    }
  }
} as const
