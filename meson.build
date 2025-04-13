project(
  'clover',
  ['c'],
  version: '0.1',
  license: 'GPL-3.0',
  meson_version: '>=1.0.0',
  default_options: ['c_std=c11'],
)

add_global_arguments('-D_POSIX_C_SOURCE=200809L', language: 'c')

subdir('src')
subdir('include')

clover_deps = []

cc = meson.get_compiler('c')
cfg = configuration_data()
cfg.set('version', meson.project_version())
cfg.set('buildinfo', '@0@ @1@'.format(cc.get_id(), cc.version()))
cfg.set('hostinfo', build_machine.system())
configure_file(configuration: cfg, input: 'version.h.in', output: 'version.h')

executable(
  'clover',
  sources: clover_sources,
  include_directories: clover_includes,
  dependencies: clover_deps,
)
