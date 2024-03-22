import { context } from 'esbuild'

const ctx = await context({
  entryPoints: ['src/new.ts'],
  outdir: './dist',
  platform: 'node',
  bundle: true,
  sourcemap: true
})

ctx.watch()
