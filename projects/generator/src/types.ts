interface LHGCallbackConfig {
  name: string
  pass: number
  self: number
  all: number
  arg_name: string[]
  out?: number[]
}

interface LHGOpaqueConfig {
  'non-alloc'?: string[]
  free?: string[]
}

export interface LHGConfig {
  name?: string
  header?: string[]
  callback?: Record<string, LHGCallbackConfig>
  opaque?: Record<string, LHGOpaqueConfig>
  output?: string[]
  remove?: string[]
  check?: Record<string, string>
}

export interface LHGInterface {
  interface: {
    name: string
    return: string
    argument: {
      name: string
      type: string
    }[]
  }[]
}

export interface LHGInterfaceArgumentInfo {
  name: string
  type: string
  special?:
    | {
        type: 'callback'
        name: string
        refer: LHGCallbackConfig
      }
    | {
        type: 'callback_context'
        refer: LHGCallbackConfig
        param: string
      }
    | {
        type: 'opaque'
        name: string
        refer: LHGOpaqueConfig
      }
    | {
        type: 'output'
        name: string
      }
}
