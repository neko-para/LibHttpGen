import fs from 'fs/promises'
import path from 'path'

import { LHGConfig, LHGInterface } from './types'

export async function loadConfig(config_path: string) {
  const obj = JSON.parse(await fs.readFile(config_path, 'utf-8')) as LHGConfig
  return {
    name: obj.name ?? 'unknown',
    header: obj.header ?? [],
    callback: obj.callback ?? {},
    opaque: obj.opaque ?? {},
    output: obj.output ?? [],
    remove: obj.remove ?? [],
    check: obj.check ?? {}
  }
}

export async function loadInterface(interface_path: string) {
  return JSON.parse(await fs.readFile(interface_path, 'utf-8')) as LHGInterface
}
