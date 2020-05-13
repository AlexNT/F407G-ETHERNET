######################################
# target
######################################
TARGET = f407g-ethernet


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Main source dir
MAIN_SOURCE_DIR = src
# HAL_Driver dir
STD_DIR = third_part/STM32F4xx_StdPeriph_Driver
# SEGGER path
SEGGER_DIR = third_part/SEGGER
# LwIP
LwIP_DIR = third_part/lwip
# FREERTOS
FREERTOS_DIR = third_part/FreeRTOS
# CMSIS
CMSIS_DIR = third_part/CMSIS
# HAL_Driver dir
ETH_DIR = third_part/STM32F4x7_ETH_Driver
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
$(MAIN_SOURCE_DIR)/main.c \
$(MAIN_SOURCE_DIR)/stm32f4_discovery.c \
$(MAIN_SOURCE_DIR)/stm32f4x7_eth_bsp.c \
$(MAIN_SOURCE_DIR)/stm32f4xx_it.c \
$(ETH_DIR)/src/stm32f4x7_eth.c \
$(CMSIS_DIR)/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
$(STD_DIR)/src/misc.c \
$(STD_DIR)/src/stm32f4xx_rcc.c \
$(STD_DIR)/src/stm32f4xx_syscfg.c \
$(STD_DIR)/src/stm32f4xx_gpio.c \
$(STD_DIR)/src/stm32f4xx_tim.c \
$(FREERTOS_DIR)/croutine.c \
$(FREERTOS_DIR)/event_groups.c \
$(FREERTOS_DIR)/list.c \
$(FREERTOS_DIR)/queue.c \
$(FREERTOS_DIR)/tasks.c \
$(FREERTOS_DIR)/portable/MemMang/heap_4.c \
$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c \
$(LwIP_DIR)/src/netif/ppp/auth.c \
$(LwIP_DIR)/src/netif/ppp/fsm.c \
$(LwIP_DIR)/src/netif/ppp/ipcp.c \
$(LwIP_DIR)/src/netif/ppp/lcp.c \
$(LwIP_DIR)/src/netif/ppp/magic.c \
$(LwIP_DIR)/src/netif/ppp/ppp.c \
$(LwIP_DIR)/src/netif/ppp/vj.c \
$(LwIP_DIR)/src/netif/slipif.c \
$(LwIP_DIR)/src/api/api_lib.c \
$(LwIP_DIR)/src/api/api_msg.c \
$(LwIP_DIR)/src/api/err.c \
$(LwIP_DIR)/src/api/netbuf.c \
$(LwIP_DIR)/src/api/netdb.c \
$(LwIP_DIR)/src/api/netifapi.c \
$(LwIP_DIR)/src/api/sockets.c \
$(LwIP_DIR)/src/api/tcpip.c \
$(LwIP_DIR)/src/core/def.c \
$(LwIP_DIR)/src/core/dns.c \
$(LwIP_DIR)/src/core/inet_chksum.c \
$(LwIP_DIR)/src/core/init.c \
$(LwIP_DIR)/src/core/ip.c \
$(LwIP_DIR)/src/core/mem.c \
$(LwIP_DIR)/src/core/memp.c \
$(LwIP_DIR)/src/core/netif.c \
$(LwIP_DIR)/src/core/pbuf.c \
$(LwIP_DIR)/src/core/raw.c \
$(LwIP_DIR)/src/core/stats.c \
$(LwIP_DIR)/src/core/sys.c \
$(LwIP_DIR)/src/core/tcp.c \
$(LwIP_DIR)/src/core/tcp_in.c \
$(LwIP_DIR)/src/core/tcp_out.c \
$(LwIP_DIR)/src/core/udp.c \
$(LwIP_DIR)/src/core/timers.c \
$(LwIP_DIR)/src/core/ipv4/autoip.c \
$(LwIP_DIR)/src/core/ipv4/dhcp.c \
$(LwIP_DIR)/src/core/ipv4/etharp.c \
$(LwIP_DIR)/src/core/ipv4/icmp.c \
$(LwIP_DIR)/src/core/ipv4/igmp.c \
$(LwIP_DIR)/src/core/ipv4/ip_addr.c \
$(LwIP_DIR)/port/ethernetif.c \
$(LwIP_DIR)/port/sys_arch.c \
$(SEGGER_DIR)/SEGGER/SEGGER_RTT.c \
$(SEGGER_DIR)/SEGGER/SEGGER_RTT_Syscalls_GCC.c \
$(SEGGER_DIR)/SEGGER/SEGGER_SYSVIEW.c \
$(SEGGER_DIR)/SEGGER/SEGGER_RTT_printf.c  

# ASM sources
ASM_SOURCES =  \
startup/startup_stm32.s

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DHSE_VALUE=8000000 \
-DSTM32F40_41xxx

# AS includes
AS_INCLUDES = \
-IInc

# C includes
C_INCLUDES =  \
-IInc \
-I$(FREERTOS_DIR)/include \
-I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F \
-I$(ETH_DIR)/inc \
-I$(LwIP_DIR)/src/include/netif/ppp \
-I$(CMSIS_DIR)/Include \
-I$(CMSIS_DIR)/Device/ST/STM32F4xx/Include \
-I$(STD_DIR)/inc \
-I$(LwIP_DIR)/port \
-I$(LwIP_DIR)/port/include \
-I$(LwIP_DIR)/port/include/arch \
-I$(LwIP_DIR)/src/include \
-I$(LwIP_DIR)/src/include/ipv4 \
-I$(LwIP_DIR)/src/include/netif \
-I$(SEGGER_DIR)/SEGGER \
-I$(SEGGER_DIR)/config 

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = LinkerScript.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***