project('FreeRTOS-LTS', 
    'c',
    version: '202406-LTS', 
    meson_version: '>=1.3.0',
    default_options: ['buildtype=release'])

setmod = import('sourceset')
compiler = meson.get_compiler('c', native: false)

add_project_arguments([
  '-Wno-implicit-fallthrough',
  '-Wno-missing-prototypes',
  '-Wno-unused-parameter',
  '-Wno-redundant-decls',
  '-Wno-sign-conversion',
  '-Wno-switch-enum',
  '-Wno-return-type',
  '-Wno-pedantic',
  '-Wno-comment',
  '-Wno-error',
], native: false, language: 'c')


# Options
freertos_port = get_option('FREERTOS_PORT')
freertos_heap = get_option('FREERTOS_HEAP')


if not freertos_port
  error('FREERTOS_PORT is not set. Please specify it as an option when running Meson.')
endif

# Create configuration data object
rtos_config = configuration_data()
message('Configuring FreeRTOS library')


# Define mandatory library target: freertos_config
if not compiler.has_header_symbol('FreeRTOSConfig.h', 'config')
  error('freertos_config target not specified. Please define the include directory for FreeRTOSConfig.h.')
endif


# Define sources for freertos_kernel
freertos_kernel_sources = files(
  'croutine.c',
  'event_groups.c',
  'list.c',
  'queue.c',
  'stream_buffer.c',
  'tasks.c',
  'timers.c'
)

# Add heap implementation if specified
freertos_heap = get_option('FREERTOS_HEAP')
if freertos_heap
  heap_source = 'portable/MemMang/heap_{}.c'.format(freertos_heap)
  freertos_kernel_sources += files(heap_source)
endif



# Define include directories
freertos_kernel_include = include_directories('include')
freertos_kernel_port_headers = include_directories('portable')

# Create library target for freertos_kernel
freertos_kernel = static_library('freertos_kernel',
    freertos_kernel_sources,
    include_directories : [freertos_kernel_include, freertos_kernel_port_headers]
    dependencies: dependencies,
    c_args: compile_definitions,
    install: false # Usually FreeRTOS is not installed as a system library
)