import fs from 'fs/promises'

export interface SectionConfig {
  end: string
  default: string

  parseId: (row: string) => string | null
  buildId: (id: string) => string
}

export class Regenerator {
  config: SectionConfig

  sections: Record<
    string,
    {
      old?: string
      default?: string
    }
  >
  cache: (
    | {
        type: 'section'
        id: string
      }
    | {
        type: 'raw'
        text: string
      }
  )[]

  constructor(cfg: SectionConfig) {
    this.config = {
      end: cfg.end.trim(),
      default: cfg.default.trim(),

      parseId: cfg.parseId,
      buildId: cfg.buildId
    }
    this.sections = {}
    this.cache = []
  }

  async load(file: string) {
    let state: 'idle' | 'process' = 'idle'
    let id: string | null = null
    let content: string[] = []
    let def: boolean = false

    for (const row of (await fs.readFile(file, 'utf-8')).split(/\r?\n/)) {
      switch (state) {
        case 'idle':
          id = this.config.parseId(row)
          if (id) {
            state = 'process'
            content = []
            def = false
          }
          break
        case 'process':
          if (row.trim() == this.config.default) {
            def = true
          }
          if (row.trim() == this.config.end) {
            if (!def) {
              this.sections[id!] = this.sections[id!] ?? {}
              this.sections[id!]!.old = content.join('\n')
            }
            state = 'idle'
          } else {
            content.push(row)
          }
          break
      }
    }
    if (state != 'idle') {
      console.warn('not finish as idle')
    }
  }

  async save(file: string) {
    const result: string[] = []
    for (const row of this.cache) {
      switch (row.type) {
        case 'raw':
          result.push(row.text)
          break
        case 'section':
          result.push(this.config.buildId(row.id))
          if (this.sections[row.id]?.old) {
            result.push(this.sections[row.id]!.old!)
          } else {
            result.push(this.config.default)
            result.push(this.sections[row.id]!.default ?? '')
          }
          result.push(this.config.end)
          break
      }
    }
    result.push('')
    await fs.writeFile(file, result.join('\n'))
  }

  add_raw(row: string) {
    this.cache.push({
      type: 'raw',
      text: row
    })
  }

  add_sec(id: string, def: string) {
    this.sections[id] = this.sections[id] ?? {}
    this.sections[id]!.default = def
    this.cache.push({
      type: 'section',
      id
    })
  }
}
