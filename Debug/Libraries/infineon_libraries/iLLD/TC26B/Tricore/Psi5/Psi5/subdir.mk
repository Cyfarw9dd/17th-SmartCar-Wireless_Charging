################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/IfxPsi5_Psi5.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/IfxPsi5_Psi5.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/IfxPsi5_Psi5.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/IfxPsi5_Psi5.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/%.src: ../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb -I"D:\Faith\ADC_Demo" -I"D:\Faith\ADC_Demo\Libraries" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Configurations" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Platform" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Platform\Tricore" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Platform\Tricore\Compilers" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Sfr" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Sfr\TC26B" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Infra\Sfr\TC26B\_Reg" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\If" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\If\Ccu6If" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\StdIf" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Bsp" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Comm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\General" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Math" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Time" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\Service\CpuGeneric\_Utilities" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Asc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Lin" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Spi" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Icu" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Timer" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif\Cam" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\CStart" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Irq" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Trap" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma\Dma" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts\Dts" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Emem" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Emem\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray\Eray" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce\Crc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft\Fft" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Flash" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Flash\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tim" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Trig" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl\Hssl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c\I2c" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom\Driver" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc\Msc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Mtu" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Mtu\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican\Can" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port\Io" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5\Psi5" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Scu" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Scu\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent\Sent" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Smu" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Smu\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Src" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Src\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm\Timer" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc\Adc" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc\Std" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Impl" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"D:\Faith\ADC_Demo\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_PinMap" -I"D:\Faith\ADC_Demo\Libraries\seekfree_libraries" -I"D:\Faith\ADC_Demo\Libraries\seekfree_libraries\common" -I"D:\Faith\ADC_Demo\Libraries\seekfree_peripheral" -I"D:\Faith\ADC_Demo\USER" -I"D:\Faith\ADC_Demo\CODE" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\ADC_Demo\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/%.o: ./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Psi5/Psi5/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


