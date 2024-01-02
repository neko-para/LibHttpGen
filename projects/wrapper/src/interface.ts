import axios from 'axios'

import interfaceData from '../gen.interface'

type GetRealType<K extends string> = K extends `${infer R}@${infer X}`
  ? GetRealType<R>
  : K extends 'string'
    ? string
    : K extends 'number'
      ? number
      : K extends 'boolean'
        ? boolean
        : unknown

type ReduceType<T> = T extends Record<string, unknown>
  ? {
      [key in keyof T]: ReduceType<T[key]>
    }
  : T extends string
    ? GetRealType<T>
    : never

type InterfaceType = ReduceType<typeof interfaceData>

async function call<Api extends keyof InterfaceType>(
  api: Api,
  body: InterfaceType[Api]['input']
): Promise<InterfaceType[Api]['output']> {
  return (
    await axios({
      baseURL: 'http://localhost:9876',
      url: `/api/${api}`,
      data: body,
      responseType: 'json'
    })
  ).data
}

async function main() {
  console.log((await call('MaaVersion', {})).data.return)
}

main()
