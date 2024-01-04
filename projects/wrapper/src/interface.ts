import axios from 'axios'

import interfaceData from '../gen.interface'

type GetRealType<K extends string> = K extends `${infer X}|${infer Y}`
  ? GetRealType<X> | GetRealType<Y>
  : K extends `${infer X}[]`
    ? GetRealType<X>[]
    : K extends `${infer R}@${infer X}`
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

function proxy() {
  return new Proxy(
    {},
    {
      get<Api extends keyof InterfaceType>(_: any, k: Api) {
        return (obj: InterfaceType[Api]['input']) => {
          return call(k, obj ?? {})
        }
      }
    }
  ) as {
    [Api in keyof InterfaceType]: {} extends InterfaceType[Api]['input']
      ? (obj?: {}) => Promise<InterfaceType[Api]['output']>
      : (obj: InterfaceType[Api]['input']) => Promise<InterfaceType[Api]['output']>
  }
}

async function main() {
  const api = proxy()
  console.log((await api.MaaVersion()).data.return)
}

main()
