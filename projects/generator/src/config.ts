import fs from 'fs/promises'
import path from 'path'

import { LHGConfig, LHGInterface } from './types'

export const root_path = '..'
export const source_path = path.join(root_path, 'wrapper.cpp')
export const config_path = path.join(root_path, 'config.json')
export const interface_path = path.join(root_path, 'interface.json')

export async function loadConfig() {
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

export async function loadInterface() {
  return JSON.parse(await fs.readFile(interface_path, 'utf-8')) as LHGInterface
}
