/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2004 Stefan Reinauer
 * Copyright (C) 2018 Patrick Rudolph <siro@das-labor.org>
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

#include <stdint.h>
#include <cbmem.h>
#include <console/console.h>
#include <cpu/intel/romstage.h>
#include <timestamp.h>
#include <southbridge/intel/i82801ix/i82801ix.h>
#include <program_loading.h>

asmlinkage void car_stage_entry(void)
{
	i82801ix_early_init();
	console_init();

	cbmem_recovery(0);

	timestamp_add_now(TS_START_ROMSTAGE);

	run_ramstage();
}
