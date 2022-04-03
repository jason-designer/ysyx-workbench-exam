deps_config := \
	src/device/Kconfig \
	src/memory/Kconfig \
	/home/zgs/project/ysyx-workbench/nemu/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
