#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=common/maths.c common/bitops.c common/ring_buffer.c common/logger.c control/pathplanning.c control/pid.c drivers/timer.c drivers/dma.c drivers/adc.c drivers/serial_uart.c drivers/encoder.c drivers/motor.c dspic/init.c dspic/core.c dspic/tasks.c dspic/board.c io/serial.c /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/common/maths.o ${OBJECTDIR}/common/bitops.o ${OBJECTDIR}/common/ring_buffer.o ${OBJECTDIR}/common/logger.o ${OBJECTDIR}/control/pathplanning.o ${OBJECTDIR}/control/pid.o ${OBJECTDIR}/drivers/timer.o ${OBJECTDIR}/drivers/dma.o ${OBJECTDIR}/drivers/adc.o ${OBJECTDIR}/drivers/serial_uart.o ${OBJECTDIR}/drivers/encoder.o ${OBJECTDIR}/drivers/motor.o ${OBJECTDIR}/dspic/init.o ${OBJECTDIR}/dspic/core.o ${OBJECTDIR}/dspic/tasks.o ${OBJECTDIR}/dspic/board.o ${OBJECTDIR}/io/serial.o ${OBJECTDIR}/_ext/331430879/ranging.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/common/maths.o.d ${OBJECTDIR}/common/bitops.o.d ${OBJECTDIR}/common/ring_buffer.o.d ${OBJECTDIR}/common/logger.o.d ${OBJECTDIR}/control/pathplanning.o.d ${OBJECTDIR}/control/pid.o.d ${OBJECTDIR}/drivers/timer.o.d ${OBJECTDIR}/drivers/dma.o.d ${OBJECTDIR}/drivers/adc.o.d ${OBJECTDIR}/drivers/serial_uart.o.d ${OBJECTDIR}/drivers/encoder.o.d ${OBJECTDIR}/drivers/motor.o.d ${OBJECTDIR}/dspic/init.o.d ${OBJECTDIR}/dspic/core.o.d ${OBJECTDIR}/dspic/tasks.o.d ${OBJECTDIR}/dspic/board.o.d ${OBJECTDIR}/io/serial.o.d ${OBJECTDIR}/_ext/331430879/ranging.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/common/maths.o ${OBJECTDIR}/common/bitops.o ${OBJECTDIR}/common/ring_buffer.o ${OBJECTDIR}/common/logger.o ${OBJECTDIR}/control/pathplanning.o ${OBJECTDIR}/control/pid.o ${OBJECTDIR}/drivers/timer.o ${OBJECTDIR}/drivers/dma.o ${OBJECTDIR}/drivers/adc.o ${OBJECTDIR}/drivers/serial_uart.o ${OBJECTDIR}/drivers/encoder.o ${OBJECTDIR}/drivers/motor.o ${OBJECTDIR}/dspic/init.o ${OBJECTDIR}/dspic/core.o ${OBJECTDIR}/dspic/tasks.o ${OBJECTDIR}/dspic/board.o ${OBJECTDIR}/io/serial.o ${OBJECTDIR}/_ext/331430879/ranging.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=common/maths.c common/bitops.c common/ring_buffer.c common/logger.c control/pathplanning.c control/pid.c drivers/timer.c drivers/dma.c drivers/adc.c drivers/serial_uart.c drivers/encoder.c drivers/motor.c dspic/init.c dspic/core.c dspic/tasks.c dspic/board.c io/serial.c /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/common/maths.o: common/maths.c  .generated_files/fe77cbc8f6746113a68087de9c79921818756da9.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/maths.o.d 
	@${RM} ${OBJECTDIR}/common/maths.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/maths.c  -o ${OBJECTDIR}/common/maths.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/maths.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/bitops.o: common/bitops.c  .generated_files/2182cd79e774e533badc2f8e834f879834928b62.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/bitops.o.d 
	@${RM} ${OBJECTDIR}/common/bitops.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/bitops.c  -o ${OBJECTDIR}/common/bitops.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/bitops.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/ring_buffer.o: common/ring_buffer.c  .generated_files/a832e193e64713cc00040e10b626014df8b0828a.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/common/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/ring_buffer.c  -o ${OBJECTDIR}/common/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/ring_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/logger.o: common/logger.c  .generated_files/f46e7328e42673dbfdab2d9cc5ac3a9413438cb2.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/logger.o.d 
	@${RM} ${OBJECTDIR}/common/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/logger.c  -o ${OBJECTDIR}/common/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/logger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/control/pathplanning.o: control/pathplanning.c  .generated_files/664d46a88e5f733f3629c900725af9926cb8a3f8.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/control" 
	@${RM} ${OBJECTDIR}/control/pathplanning.o.d 
	@${RM} ${OBJECTDIR}/control/pathplanning.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control/pathplanning.c  -o ${OBJECTDIR}/control/pathplanning.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/control/pathplanning.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/control/pid.o: control/pid.c  .generated_files/1a61413e813c41958d5f5dde4d60edc009b4f779.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/control" 
	@${RM} ${OBJECTDIR}/control/pid.o.d 
	@${RM} ${OBJECTDIR}/control/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control/pid.c  -o ${OBJECTDIR}/control/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/control/pid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api.c  .generated_files/fafc8d2c2b74c0912a531af519a226d1a09eb7a4.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_ranging.c  .generated_files/a4fba137eb15bff91575b1bbe7714a4e3f40f35f.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_ranging.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_core.c  .generated_files/88803a7db5dd0a2c48c90a619c86ffb291e12a8c.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_core.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform_log.c  .generated_files/19785909258e1cbe03ef86df3400e4f858af87ec.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform_log.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_i2c_win_serial_comms.c  .generated_files/552c627c739c310abb677081139063db2932ebf8.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_i2c_win_serial_comms.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_calibration.c  .generated_files/b5d3ec38e1426415abc96d7a2096c3c205ff8743.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_calibration.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform.c  .generated_files/452a859165cc65f0729563df56ebbe4cdf2f670.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_strings.c  .generated_files/8a7ec4ebc737a4b948e745ba9e081da5f53c2527.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_strings.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/timer.o: drivers/timer.c  .generated_files/9cfdf8eec2871a1152ce1227eb5ccb91749fa0aa.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/timer.o.d 
	@${RM} ${OBJECTDIR}/drivers/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/timer.c  -o ${OBJECTDIR}/drivers/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/dma.o: drivers/dma.c  .generated_files/6b0b4e7d3bc52c43cdbc17b58db448a0462a9e66.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/dma.o.d 
	@${RM} ${OBJECTDIR}/drivers/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/dma.c  -o ${OBJECTDIR}/drivers/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/adc.o: drivers/adc.c  .generated_files/5fa3eba84da9edffd63bdc4195c959c37e8dbca5.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/adc.o.d 
	@${RM} ${OBJECTDIR}/drivers/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/adc.c  -o ${OBJECTDIR}/drivers/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/serial_uart.o: drivers/serial_uart.c  .generated_files/11d741677b574d996cfea2782ccc3fcf0c274e24.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/serial_uart.o.d 
	@${RM} ${OBJECTDIR}/drivers/serial_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/serial_uart.c  -o ${OBJECTDIR}/drivers/serial_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/serial_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/encoder.o: drivers/encoder.c  .generated_files/f41f8586aae8985ff679b18f2047292e983d43fa.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/encoder.o.d 
	@${RM} ${OBJECTDIR}/drivers/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/encoder.c  -o ${OBJECTDIR}/drivers/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/encoder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/motor.o: drivers/motor.c  .generated_files/415b030d74f56411cf8f29675649789156df55da.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/motor.o.d 
	@${RM} ${OBJECTDIR}/drivers/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/motor.c  -o ${OBJECTDIR}/drivers/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/init.o: dspic/init.c  .generated_files/38ca1516569887a55f4bd86dff37b7342702bfb5.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/init.o.d 
	@${RM} ${OBJECTDIR}/dspic/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/init.c  -o ${OBJECTDIR}/dspic/init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/core.o: dspic/core.c  .generated_files/78aca57eb51f0c76b6b6560658562c9d6a7606c5.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/core.o.d 
	@${RM} ${OBJECTDIR}/dspic/core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/core.c  -o ${OBJECTDIR}/dspic/core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/tasks.o: dspic/tasks.c  .generated_files/12bdad40ec67a0c3e723340d0cede17c828401d2.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/tasks.o.d 
	@${RM} ${OBJECTDIR}/dspic/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/tasks.c  -o ${OBJECTDIR}/dspic/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/tasks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/board.o: dspic/board.c  .generated_files/1ae7452a9bef612dc22bca6803ecdd7d95204f6b.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/board.o.d 
	@${RM} ${OBJECTDIR}/dspic/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/board.c  -o ${OBJECTDIR}/dspic/board.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/board.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/io/serial.o: io/serial.c  .generated_files/a88966da8d665b94d60add83516702eed3ca87eb.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/io" 
	@${RM} ${OBJECTDIR}/io/serial.o.d 
	@${RM} ${OBJECTDIR}/io/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  io/serial.c  -o ${OBJECTDIR}/io/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/io/serial.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/331430879/ranging.o: /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c  .generated_files/c94d712a096908c8dcbaf70843997a786dbea581.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/331430879" 
	@${RM} ${OBJECTDIR}/_ext/331430879/ranging.o.d 
	@${RM} ${OBJECTDIR}/_ext/331430879/ranging.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c  -o ${OBJECTDIR}/_ext/331430879/ranging.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/331430879/ranging.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/ab25677cf00346ce94d279872f108969c6a07400.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/common/maths.o: common/maths.c  .generated_files/82b819434af5389147f76671acc7ddd586a44694.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/maths.o.d 
	@${RM} ${OBJECTDIR}/common/maths.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/maths.c  -o ${OBJECTDIR}/common/maths.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/maths.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/bitops.o: common/bitops.c  .generated_files/655cf9386b4aeca4f9b95b91719080f5e7955ef6.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/bitops.o.d 
	@${RM} ${OBJECTDIR}/common/bitops.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/bitops.c  -o ${OBJECTDIR}/common/bitops.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/bitops.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/ring_buffer.o: common/ring_buffer.c  .generated_files/bd79d145790b729671eb86b42470bfa033d5d2b2.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/common/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/ring_buffer.c  -o ${OBJECTDIR}/common/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/ring_buffer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/common/logger.o: common/logger.c  .generated_files/d6e7ca180325d8da6398a1a9fba2a8fe3a380a94.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/logger.o.d 
	@${RM} ${OBJECTDIR}/common/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  common/logger.c  -o ${OBJECTDIR}/common/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/common/logger.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/control/pathplanning.o: control/pathplanning.c  .generated_files/ce9ab228cf73415d1e6982730421781e31f03706.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/control" 
	@${RM} ${OBJECTDIR}/control/pathplanning.o.d 
	@${RM} ${OBJECTDIR}/control/pathplanning.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control/pathplanning.c  -o ${OBJECTDIR}/control/pathplanning.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/control/pathplanning.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/control/pid.o: control/pid.c  .generated_files/59fa25defdf9925b096d3571e999b0ef55ea899b.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/control" 
	@${RM} ${OBJECTDIR}/control/pid.o.d 
	@${RM} ${OBJECTDIR}/control/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control/pid.c  -o ${OBJECTDIR}/control/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/control/pid.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api.c  .generated_files/4d285b99a15e453e63fdfcc98e1a841117e8cf57.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_ranging.c  .generated_files/f203fe7ac90e0d6151e69a71ea8b0f3876c01939.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_ranging.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_ranging.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_core.c  .generated_files/6766a6fc5eb50e0b92cb1da2e7c4e99cd3a68744.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_core.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_core.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform_log.c  .generated_files/79f18d0ed5aa47fa3368a7b195925eaa8b79a88e.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform_log.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_platform_log.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_i2c_win_serial_comms.c  .generated_files/8097b6a480c262a460a29d53cd0782f4beb34d97.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_i2c_win_serial_comms.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_i2c_win_serial_comms.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_calibration.c  .generated_files/bbd03cfdbd5fccf99a639effd3064b799e0a46c5.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_calibration.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_calibration.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform.c  .generated_files/c6432b4273c8ebee47dc3ff3e7a848da24a0c9b.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_platform.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_platform.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o: /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_strings.c  .generated_files/c948e19030b80a327933acfeb94b1871c5b66cbb.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829162532" 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/drivers/ranging/vl53l0x_api_strings.c  -o ${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/829162532/vl53l0x_api_strings.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/timer.o: drivers/timer.c  .generated_files/db77403fc0a758f6f8d15300448641502a7196e0.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/timer.o.d 
	@${RM} ${OBJECTDIR}/drivers/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/timer.c  -o ${OBJECTDIR}/drivers/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/timer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/dma.o: drivers/dma.c  .generated_files/cb1b47b5100af4a1c17928adb78d18cfde219fa9.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/dma.o.d 
	@${RM} ${OBJECTDIR}/drivers/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/dma.c  -o ${OBJECTDIR}/drivers/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/dma.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/adc.o: drivers/adc.c  .generated_files/21291f90d2be77562600c1d5f03f96a4f0b26c42.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/adc.o.d 
	@${RM} ${OBJECTDIR}/drivers/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/adc.c  -o ${OBJECTDIR}/drivers/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/serial_uart.o: drivers/serial_uart.c  .generated_files/1f2eac8fea624d3296223eb0d94a58380b4f6c53.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/serial_uart.o.d 
	@${RM} ${OBJECTDIR}/drivers/serial_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/serial_uart.c  -o ${OBJECTDIR}/drivers/serial_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/serial_uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/encoder.o: drivers/encoder.c  .generated_files/de4de6ad558482039fea2f32de4391cd6cdf2126.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/encoder.o.d 
	@${RM} ${OBJECTDIR}/drivers/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/encoder.c  -o ${OBJECTDIR}/drivers/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/encoder.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drivers/motor.o: drivers/motor.c  .generated_files/b2761e6dfaea5f9a259836ff324c5a940e93d2d9.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/drivers" 
	@${RM} ${OBJECTDIR}/drivers/motor.o.d 
	@${RM} ${OBJECTDIR}/drivers/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drivers/motor.c  -o ${OBJECTDIR}/drivers/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drivers/motor.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/init.o: dspic/init.c  .generated_files/bf04d431d2e2455af60ff4aad0e7f3840bdd69d6.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/init.o.d 
	@${RM} ${OBJECTDIR}/dspic/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/init.c  -o ${OBJECTDIR}/dspic/init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/init.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/core.o: dspic/core.c  .generated_files/13278ec51a305e7ad79809a37be6d8f6769d821b.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/core.o.d 
	@${RM} ${OBJECTDIR}/dspic/core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/core.c  -o ${OBJECTDIR}/dspic/core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/core.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/tasks.o: dspic/tasks.c  .generated_files/f0ff84965e2698eb070d3df20f9b360c0d5c791e.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/tasks.o.d 
	@${RM} ${OBJECTDIR}/dspic/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/tasks.c  -o ${OBJECTDIR}/dspic/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/tasks.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dspic/board.o: dspic/board.c  .generated_files/a52dcfd8bcfe645491003c1f1b4ef42ff36771f7.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/dspic" 
	@${RM} ${OBJECTDIR}/dspic/board.o.d 
	@${RM} ${OBJECTDIR}/dspic/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic/board.c  -o ${OBJECTDIR}/dspic/board.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dspic/board.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/io/serial.o: io/serial.c  .generated_files/939e4cacb64a4abbcc3af96a56a1d49846acacd3.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/io" 
	@${RM} ${OBJECTDIR}/io/serial.o.d 
	@${RM} ${OBJECTDIR}/io/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  io/serial.c  -o ${OBJECTDIR}/io/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/io/serial.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/331430879/ranging.o: /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c  .generated_files/f7dc1d46c43c6af479ea9d4de76feb43d988a52d.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}/_ext/331430879" 
	@${RM} ${OBJECTDIR}/_ext/331430879/ranging.o.d 
	@${RM} ${OBJECTDIR}/_ext/331430879/ranging.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/oliver/Documents/Workspace/C/micromouse/sensors/ranging.c  -o ${OBJECTDIR}/_ext/331430879/ranging.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/331430879/ranging.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/bc4d5b7a43f3c7946c9e08d84b3b5b260c17075a.flag .generated_files/84a00fe3fec8648bb2130ba09c26adb59497f229.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99     -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
