project('boom', 'c', default_options : ['warning_level=3', 'c_std=c17',])
add_project_arguments(language : 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)

sources = ['src/main.c', 'src/vector.c', 'src/matrix.c']
executable('boom', sources, dependencies: m_dep)
