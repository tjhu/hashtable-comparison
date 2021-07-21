project(
    'ht-comparison',
    'cpp',
    default_options: [
        'buildtype=release',
        'optimization=3',
        'debug=true',
        'cpp_std=gnu++20',
        'warning_level=3',
    ],
)

dependencies = [
    dependency('absl_container', default_options: ['werror=false', 'cpp_args=-Wno-pedantic', 'warning_level=1', 'debug=true']),
]

executable('ht-comparison', 'main.cpp', dependencies: dependencies, default_options : ['cpp_std=c++20'])
