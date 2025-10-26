#pragma once
#include <stdint.h>
#define REG32(addr) (*(volatile uint32_t *)(addr))

// Base GPIO ESP32-C3
#define DR_REG_GPIO_BASE     0x60004000UL

#define GPIO_OUT_REG         REG32(DR_REG_GPIO_BASE + 0x0004)
#define GPIO_OUT_W1TS_REG    REG32(DR_REG_GPIO_BASE + 0x0008)
#define GPIO_OUT_W1TC_REG    REG32(DR_REG_GPIO_BASE + 0x000C)
#define GPIO_ENABLE_REG      REG32(DR_REG_GPIO_BASE + 0x0020)
#define GPIO_ENABLE_W1TS_REG REG32(DR_REG_GPIO_BASE + 0x0024)
#define GPIO_IN_REG          REG32(DR_REG_GPIO_BASE + 0x003C)
