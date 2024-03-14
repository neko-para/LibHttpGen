import { build } from 'esbuild'

build({
  entryPoints: ['src/new.ts'],
  outdir: './dist',
  platform: 'node',
  bundle: true,
  sourcemap: true
})
