import exp = require('constants')

export class expressionItem {
  expr: string

  constructor(expr: string) {
    this.expr = expr
  }
}

type JsonValue =
  | {
      [key: string]: JsonValue
    }
  | JsonValue[]
  | string
  | number
  | boolean
  | null
  | expressionItem

export function objectEntryToJson(key: string, value: JsonValue) {
  return `{ ${JSON.stringify(key)}, ${objectToJson(value, true)} }`
}

export function objectToJson(obj: JsonValue, inside = false) {
  if (obj instanceof expressionItem) {
    return obj.expr
  } else if (obj instanceof Array) {
    return `json::array { ${obj.map(x => objectToJson(x, true)).join(', ')} }`
  } else if (typeof obj === 'object') {
    const res: string[] = []
    for (const key in obj) {
      res.push(objectEntryToJson(key, obj[key]))
    }
    return `${inside && res.length > 0 ? '' : 'json::object '}{${
      res.length > 0 ? ` ${res.join(', ')} ` : ''
    }}`
  } else {
    return JSON.stringify(obj)
  }
}
