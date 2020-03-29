bin_PROGRAMS = xset770 ageoffile play-sound
sbin_PROGRAMS = waitdbus waitx runas fb-progress temp-reaper anim-shower

xset770_CFLAGS = $(X11_CFLAGS) $(XI_CFLAGS)
xset770_LDADD = $(X11_LIBS) $(XI_LIBS)
xset770_SOURCES = \
	xset770.c

fb_progress_CFLAGS = $(LIBPNG_CFLAGS) $(LIBJPEG_CFLAGS)
fb_progress_LDADD = $(LIBPNG_LIBS) $(LIBJPEG_LIBS)
fb_progress_SOURCES = \
	fb-progress.c \
	omapfb.h

anim_shower_CFLAGS = $(GDK_CFLAGS)
anim_shower_LDADD = $(GDK_LIBS)
anim_shower_SOURCES = \
	anim-shower.c

waitdbus_CFLAGS = $(DBUS_CFLAGS)
waitdbus_LDADD = $(DBUS_LIBS)
waitdbus_SOURCES = \
	waitdbus.c \
	waitdbus.h

waitx_CFLAGS = $(X11_CFLAGS)
waitx_LDADD = $(X11_LIBS)
waitx_SOURCES = \
	waitx.c \
	waitx.h

play_sound_CFLAGS = $(GCONF_CFLAGS) $(CANBERRA_CFLAGS)
play_sound_LDADD = $(GCONF_LIBS) $(CANBERRA_LIBS)
play_sound_SOURCES = \
	play-sound.c

runas_SOURCES = \
	runas.h \
	runas.c

ageoffile_SOURCES = \
	ageoffile.c

temp_reaper_SOURCES = \
	temp-reaper.c
