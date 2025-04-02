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
# Create configuration data object
rtos_config = configuration_data()
message('Configuring FreeRTOS library')



rtos_non_bool_option_list = [
    'CPU_CLOCK_HZ',
    'TICK_RATE_HZ',
    'USE_TICKLESS_IDLE',
    'MAX_PRIORITIES',
    'MINIMAL_STACK_SIZE',
    'MAX_TASK_NAME_LEN',
    'TASK_NOTIFICATION_ARRAY_ENTRIES',
    'QUEUE_REGISTRY_SIZE',
    'NUM_THREAD_LOCAL_STORAGE_POINTERS',
    'TOTAL_HEAP_SIZE',
    'CORTEX_M_PRIO_BITS',
    'LOWEST_INTERRUPT_PRIORITY',
    'MAX_SYSCALL_INTERRUPT_PRIORITY',
    'CHECK_FOR_STACK_OVERFLOW',
    'FREERTOS_PORT',
    'FREERTOS_HEAP',
]

bool_option_list = [
    'USE_PREEMPTION',
    'USE_TIME_SLICING',
    'USE_TICKLESS_IDLE',
    'USE_PORT_OPTIMISED_TASK_SELECTION',
    'USE_IDLE_HOOK',
    'USE_TICK_HOOK',
    'USE_MALLOC_FAILED_HOOK',
    'USE_DAEMON_TASK_STARTUP_HOOK',
    'USE_TIMERS',
    'USE_EVENT_GROUPS',
    'USE_STREAM_BUFFERS',
    'USE_MINI_LIST_ITEM',
    'USE_TRACE_FACILITY',
    'USE_STATS_FORMATTING_FUNCTIONS',
    'INCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS',
    'ENABLE_MPU',
]

# set options
foreach non_bool_option : rtos_non_bool_option_list
  if get_option(non_bool_option) == ''
    error('Option {} is not set. Please specify it as an option when running Meson.'.format(non_bool_option))
  endif
    if get_option(non_bool_option) == 0
        rtos_config.set(non_bool_option, 0)
    else
        rtos_config.set(non_bool_option, get_option(non_bool_option))
    endif
endforeach

# set boolean options
foreach bool_option : bool_option_list
  if get_option(bool_option)
    rtos_config.set(bool_option, 1)
  else
    rtos_config.set(bool_option, 0)
  endif
endforeach

# Generate configuration header
configure_file(
  input : 'config/FreeRTOSConfig.h.in',
  output : 'FreeRTOSConfig.h',
  configuration : rtos_config
)



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

# Add MPU  implementation if specified
freertos_heap = get_option('ENABLE_MPU')
if freertos_heap
  mpu_source = 'Common/mpu_wrappers_v2.c'
  mpu_source += 'Common/mpu_wrappers.c'
  freertos_kernel_sources += files(mpu_source)
endif

freertos_port = get_option('FREERTOS_PORT')
if freertos_port == 'GCC_ARM_CM4F'
  freertos_kernel_sources += 'portable/GCC/ARM_CM4F/port.c'
  freertos_kernel_port_headers = include_directories('portable/GCC/ARM_CM4F')

endif

if freertos_port == 'GCC_ARM_CM7'
  freertos_kernel_sources += 'portable/GCC/ARM_CM7/r0p1/port.c'
  freertos_kernel_port_headers = include_directories('portable/GCC/ARM_CM7/r0p1')

endif


# Define include directories
freertos_kernel_include = include_directories('include')

# Create library target for freertos_kernel
freertos_kernel = static_library('freertos_kernel',
    freertos_kernel_sources,
    include_directories : [freertos_kernel_include, freertos_kernel_port_headers],
    dependencies: dependencies,
    c_args: compile_definitions,
    install: false # Usually FreeRTOS is not installed as a system library
)