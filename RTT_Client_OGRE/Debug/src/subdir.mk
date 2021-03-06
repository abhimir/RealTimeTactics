################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AdvancedOgreFramework.cpp \
../src/AppStateManager.cpp \
../src/DemoApp.cpp \
../src/GameState.cpp \
../src/MenuState.cpp \
../src/OgreGameEvents.cpp \
../src/RTT_Ogre_Map.cpp \
../src/RTT_Ogre_Player.cpp \
../src/RTT_Ogre_Unit.cpp \
../src/main.cpp 

OBJS += \
./src/AdvancedOgreFramework.o \
./src/AppStateManager.o \
./src/DemoApp.o \
./src/GameState.o \
./src/MenuState.o \
./src/OgreGameEvents.o \
./src/RTT_Ogre_Map.o \
./src/RTT_Ogre_Player.o \
./src/RTT_Ogre_Unit.o \
./src/main.o 

CPP_DEPS += \
./src/AdvancedOgreFramework.d \
./src/AppStateManager.d \
./src/DemoApp.d \
./src/GameState.d \
./src/MenuState.d \
./src/OgreGameEvents.d \
./src/RTT_Ogre_Map.d \
./src/RTT_Ogre_Player.d \
./src/RTT_Ogre_Unit.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../RTT_Client_Core/src -I../../RTT_Common/src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -pthread `pkg-config --cflags OGRE OIS CEGUI CEGUI-OGRE` -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


