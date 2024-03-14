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
