project(
    'ArduinoRaspi',
    'c', 
    'cpp',
    default_options : [
        'c_std=c11', 
        'cpp_std=c++17',
        'b_lto=true',
        'b_pgo=generate',
        'b_coverage=false',
    ],
    version:'0.1.0',
    meson_version: '>= 0.54.0',
)

CC = meson.get_compiler('c')

ArduinoRaspi_deps = [
    dependency('libgpiodcxx', required: true),
]

incdir = include_directories('include','.')

sources = [
    'src/ArduinoRaspi.cpp',
]

ArduinoRaspi = library(
    'ArduinoRaspi',
    sources,
    version : meson.project_version(),
    soversion : '0',
    include_directories : incdir,
    dependencies: ArduinoRaspi_deps,
    install : true,
)

ArduinoRaspi_dep = declare_dependency(
    include_directories : incdir,
    link_with : ArduinoRaspi,
    dependencies : ArduinoRaspi_deps,
    version: meson.project_version(),
)

install_subdir('include', install_dir : 'include/ArduinoRaspi', strip_directory : true)

pkg = import('pkgconfig')
pkg.generate(ArduinoRaspi)

meson.override_dependency('ArduinoRaspi',ArduinoRaspi_dep)

#if not get_option('no-data')
#    install_subdir('data', install_dir : get_option('datadir') / 'libtrainsim')
#endif
