project('FreeRTOS-LTS', 
    'c', version: '202406-LTS', meson_version: '>=1.3.0', default_options: ['buildtype=release'])

setmod = import('sourceset')
compiler = meson.get_compiler('c', native: false)
cmake = import('cmake')



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



# Define the configuration variables
config_variables = configuration_data()
config_variables.set('configMAX_TASK_NAME_LEN', 32)
config_variables.set('configMINIMAL_STACK_SIZE', 128)
config_variables.set('configENABLE_MPU', 0)
config_variables.set('configUSE_TICKLESS_IDLE', 0)




build_c_flags = get_option('build_defines')  ## gets STM32 family


freertos_opts = cmake.subproject_options()
freertos_opts.add_cmake_defines({
	'CMAKE_POSITION_INDEPENDENT_CODE': true,
  })

if not build_libs
	freertos_opts.add_cmake_defines({
		'ENABLE_INSTALL': false
	})

	freertos_opts.set_install(false)
	freertos_opts.set_override_option('build_by_default','false')
else
	freertos_opts.add_cmake_defines({
		'ENABLE_INSTALL': true
	})

	freertos_opts.set_override_option('install_dir', join_paths(game_dir,'bin'))
endif

FreeRTOS_Kernel = cmake.subproject('FreeRTOS-Kernel', options: freertos_opts)

FreeRTOS_Kernel_dep = declare_dependency(
	dependencies: [
		FreeRTOS_Kernel.dependency('FreeRTOS-Kernel'),
    FreeRTOS_Kernel.dependency('FreeRTOS-Kernel-Config'),
	]
)