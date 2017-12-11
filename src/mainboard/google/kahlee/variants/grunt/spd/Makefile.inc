##
## This file is part of the coreboot project.
##
## Copyright (C) 2014 Google Inc.
## Copyright (C) 2015 Intel Corporation.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##

LIB_SPD_DEPS = $(foreach f, $(SPD_SOURCES), src/mainboard/$(MAINBOARDDIR)/variants/$(VARIANT_DIR)/spd/$(f).spd.hex)

SPD_SOURCES =  hynix-H5AN8G6NAFR-UH.spd.hex		# 0b0000
SPD_SOURCES += hynix-H5ANAG6NAMR-UH.spd.hex		# 1b0001
SPD_SOURCES += micron-MT40A512M16JY-083E:B.spd.hex	# 2b0010
SPD_SOURCES += micron-MT40A1G16KNR-075:E.spd.hex	# 3b0011
SPD_SOURCES += samsung-K4A8G165WB-BCRC.spd.hex		# 4b0100
SPD_SOURCES += samsung-K4AAG165WB-MCRC.spd.hex		# 5b0101
SPD_SOURCES += empty					# 6b0110
SPD_SOURCES += empty					# 7b0111
SPD_SOURCES += empty					# 8b1000
SPD_SOURCES += empty					# 9b1001
SPD_SOURCES += empty					# Ab1010
SPD_SOURCES += empty					# Bb1011
SPD_SOURCES += empty					# Cb1100
SPD_SOURCES += empty					# Db1101
SPD_SOURCES += empty					# Eb1110
SPD_SOURCES += empty					# Fb1111