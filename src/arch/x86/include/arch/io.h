/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _ASM_IO_H
#define _ASM_IO_H

#include <endian.h>
#include <stdint.h>
#include <device/pci_type.h>

/*
 * This file contains the definitions for the x86 IO instructions
 * inb/inw/inl/outb/outw/outl and the "string versions" of the same
 * (insb/insw/insl/outsb/outsw/outsl).
 */
#if defined(__ROMCC__)
static inline void outb(uint8_t value, uint16_t port)
{
	__builtin_outb(value, port);
}

static inline void outw(uint16_t value, uint16_t port)
{
	__builtin_outw(value, port);
}

static inline void outl(uint32_t value, uint16_t port)
{
	__builtin_outl(value, port);
}


static inline uint8_t inb(uint16_t port)
{
	return __builtin_inb(port);
}


static inline uint16_t inw(uint16_t port)
{
	return __builtin_inw(port);
}

static inline uint32_t inl(uint16_t port)
{
	return __builtin_inl(port);
}
#else
static inline void outb(uint8_t value, uint16_t port)
{
	__asm__ __volatile__ ("outb %b0, %w1" : : "a" (value), "Nd" (port));
}

static inline void outw(uint16_t value, uint16_t port)
{
	__asm__ __volatile__ ("outw %w0, %w1" : : "a" (value), "Nd" (port));
}

static inline void outl(uint32_t value, uint16_t port)
{
	__asm__ __volatile__ ("outl %0, %w1" : : "a" (value), "Nd" (port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t value;
	__asm__ __volatile__ ("inb %w1, %b0" : "=a"(value) : "Nd" (port));
	return value;
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t value;
	__asm__ __volatile__ ("inw %w1, %w0" : "=a"(value) : "Nd" (port));
	return value;
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t value;
	__asm__ __volatile__ ("inl %w1, %0" : "=a"(value) : "Nd" (port));
	return value;
}
#endif /* __ROMCC__ */

static inline void outsb(uint16_t port, const void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; outsb "
		: "=S" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		);
}

static inline void outsw(uint16_t port, const void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; outsw "
		: "=S" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		);
}

static inline void outsl(uint16_t port, const void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; outsl "
		: "=S" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		);
}


static inline void insb(uint16_t port, void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; insb "
		: "=D" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		: "memory"
		);
}

static inline void insw(uint16_t port, void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; insw "
		: "=D" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		: "memory"
		);
}

static inline void insl(uint16_t port, void *addr, unsigned long count)
{
	__asm__ __volatile__ (
		"cld ; rep ; insl "
		: "=D" (addr), "=c" (count)
		: "d"(port), "0"(addr), "1" (count)
		: "memory"
		);
}

static __always_inline uint8_t read8(
	const volatile void *addr)
{
	return *((volatile uint8_t *)(addr));
}

static __always_inline uint16_t read16(
	const volatile void *addr)
{
	return *((volatile uint16_t *)(addr));
}

static __always_inline uint32_t read32(
	const volatile void *addr)
{
	return *((volatile uint32_t *)(addr));
}

#ifndef __ROMCC__
static __always_inline uint64_t read64(
	const volatile void *addr)
{
	return *((volatile uint64_t *)(addr));
}
#endif

static __always_inline void write8(volatile void *addr,
	uint8_t value)
{
	*((volatile uint8_t *)(addr)) = value;
}

static __always_inline void write16(volatile void *addr,
	uint16_t value)
{
	*((volatile uint16_t *)(addr)) = value;
}

static __always_inline void write32(volatile void *addr,
	uint32_t value)
{
	*((volatile uint32_t *)(addr)) = value;
}

#ifndef __ROMCC__
static __always_inline void write64(volatile void *addr,
	uint64_t value)
{
	*((volatile uint64_t *)(addr)) = value;
}
#endif

/* FIXME: We should avoid this indirect include. Also this has to
 * appear here after all MMIO and IO read/write functions. */
#include <arch/pci_ops.h>

#ifdef __SIMPLE_DEVICE__

#define PNP_DEV(PORT, FUNC) (((PORT) << 8) | (FUNC))

/* Generic functions for pnp devices */
static __always_inline void pnp_write_config(
	pnp_devfn_t dev, uint8_t reg, uint8_t value)
{
	unsigned int port = dev >> 8;
	outb(reg, port);
	outb(value, port + 1);
}

static __always_inline uint8_t pnp_read_config(
	pnp_devfn_t dev, uint8_t reg)
{
	unsigned int port = dev >> 8;
	outb(reg, port);
	return inb(port + 1);
}

static __always_inline
void pnp_set_logical_device(pnp_devfn_t dev)
{
	unsigned int device = dev & 0xff;
	pnp_write_config(dev, 0x07, device);
}

static __always_inline
void pnp_set_enable(pnp_devfn_t dev, int enable)
{
	pnp_write_config(dev, 0x30, enable?0x1:0x0);
}

static __always_inline
int pnp_read_enable(pnp_devfn_t dev)
{
	return !!pnp_read_config(dev, 0x30);
}

static __always_inline
void pnp_set_iobase(pnp_devfn_t dev, unsigned int index, unsigned int iobase)
{
	pnp_write_config(dev, index + 0, (iobase >> 8) & 0xff);
	pnp_write_config(dev, index + 1, iobase & 0xff);
}

static __always_inline
uint16_t pnp_read_iobase(pnp_devfn_t dev, unsigned int index)
{
	return ((uint16_t)(pnp_read_config(dev, index)) << 8)
		| pnp_read_config(dev, index + 1);
}

static __always_inline
void pnp_set_irq(pnp_devfn_t dev, unsigned int index, unsigned int irq)
{
	pnp_write_config(dev, index, irq);
}

static __always_inline
void pnp_set_drq(pnp_devfn_t dev, unsigned int index, unsigned int drq)
{
	pnp_write_config(dev, index, drq & 0xff);
}

#endif /* __SIMPLE_DEVICE__ */
#endif
