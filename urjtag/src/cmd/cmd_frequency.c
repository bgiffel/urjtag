/*
 * $Id$
 *
 * Copyright (C) 2003 ETC s.r.o.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

#include <urjtag/sysdep.h>

#include <stdio.h>

#include <urjtag/chain.h>
#include <urjtag/cable.h>

#include <urjtag/cmd.h>

#include "cmd.h"

static int
cmd_frequency_run (urj_chain_t *chain, char *params[])
{
    unsigned int freq;

    if (!urj_cmd_test_cable (chain))
        return 1;

    if (urj_cmd_params (params) == 1)
    {
        printf (_("Current TCK frequency is %u Hz\n"),
                urj_tap_cable_get_frequency (chain->cable));
        return 1;
    }

    if (urj_cmd_params (params) != 2)
        return -1;

    if (urj_cmd_get_number (params[1], &freq))
        return -1;

    printf (_("Setting TCK frequency to %u Hz\n"), freq);
    urj_tap_cable_set_frequency (chain->cable, freq);

    return 1;
}

static void
cmd_frequency_help (void)
{
    printf (_("Usage: %s [FREQ]\n"
              "Change TCK frequency to FREQ or print current TCK frequency.\n"
              "\n"
              "FREQ is in hertz. It's a maximum TCK frequency for JTAG interface.\n"
              "In some cases the TCK frequency is less than FREQ, but the frequency\n"
              "is never more than FREQ. Maximum supported frequency depends on JTAG\n"
              "adapter.\n"
              "\n"
              "FREQ must be an unsigned integer. Minimum allowed frequency is 1 Hz.\n"
              "Use 0 for FREQ to disable frequency limit.\n"), "frequency");
}

const urj_cmd_t urj_cmd_frequency = {
    "frequency",
    N_("setup JTAG frequency"),
    cmd_frequency_help,
    cmd_frequency_run
};
