export interface LHGConfig {
  callback?: Record<
    string,
    {
      name: string
      pass: number
      self: number
      all: number
      arg_name: string[]
    }
  >
  opaque?: Record<
    string,
    {
      free?: string[]
    }
  >
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
