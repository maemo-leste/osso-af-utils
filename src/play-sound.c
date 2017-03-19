/*
  Copyright (C) 2006-2008 Nokia Corporation. All rights reserved.
 
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.
 
  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
  02110-1301 USA
*/

#include <gconf/gconf-client.h>
#include <canberra.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

#define ALARM_GCONF_PATH "/apps/osso/sound/system_alert_volume"


static void callback(ca_context *c, uint32_t id, int error, void *userdata)
{
        fprintf(stderr, "callback called, error '%s'\n", ca_strerror(error));
        exit(0);
}

static int play_sound(char *filename)
{
        int ret, pan;
        GConfClient *gc;
        GConfValue *value;
        ca_context *ca_con;
        ca_proplist *pl = NULL;
        float volume;
#if !GLIB_CHECK_VERSION(2,35,0)
        g_type_init();
#endif
        gc = gconf_client_get_default();
        value = gconf_client_get(gc, ALARM_GCONF_PATH, NULL);

        if (value && value->type == GCONF_VALUE_INT)
                pan = gconf_value_get_int(value);
        else 
                pan = 2;

        /* FIXME: This might need adjusting...
         *
         * The volume is from -0dB to -6dB,
           The full volume is marked as 2 in gconf */
        volume = ((1.0 - (float)pan / 2.0)) * (-6.0);

        if ((ret = ca_context_create(&ca_con)) != CA_SUCCESS) {
                fprintf(stderr, "ca_context_create: %s\n", ca_strerror(ret));
                return 1;
        }
        if ((ret = ca_context_open(ca_con)) != CA_SUCCESS) {
                fprintf(stderr, "ca_context_open: %s\n", ca_strerror(ret));
                return 1;
        }
        ca_proplist_create(&pl);
        ca_proplist_sets(pl, CA_PROP_MEDIA_FILENAME, filename);
        ca_proplist_setf(pl, CA_PROP_CANBERRA_VOLUME, "%f", volume);

        ret = ca_context_play_full(ca_con, 0, pl, callback, NULL);
        fprintf(stderr, "ca_context_play_full (vol %f): %s\n", volume,
                ca_strerror(ret));
        if (ret == CA_SUCCESS) {
                /* wait for the callback */
                sleep(100);
                fprintf(stderr, "timeout\n");
        }

        return 0;
}

int main(int argc, char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "usage: %s <sound file>\n", argv[0]);	
                return 1;
        }
        return play_sound(argv[1]);
}
