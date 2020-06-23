#!/sbin/openrc-run

PIDFILE=/tmp/fb-progress.pid
BAR_IMGDIR=/usr/share/icons/hicolor/scalable/hildon
BAR=indicator_update

SECS=9

start() {
	# wait until we have /dev
	while [ ! -e /dev/tty0 ]; do
		sleep 1
	done

	# don't show progress bar if device started to ACTDEAD first
	BOOTSTATE="$(cat /var/lib/dsme/saved_state)"
	if [ "$BOOTSTATE" != "ACT_DEAD" -a ! -f /tmp/skip-fb-progress.tmp ]; then
		AF_PIDDIR=/tmp/af-piddir
		mkdir -p "$AF_PIDDIR"
		chmod 777 "$AF_PIDDIR"

		ebegin "Starting fb-progress"
		fb-progress -c -g "$BAR_IMGDIR/$BAR" "$SECS" > /dev/null 2>&1 &
		echo "$!" > "$PIDFILE"
		chmod 666 "$PIDFILE"
	fi

	rm -f /tmp/skip-fb-progress.tmp
}

stop() {
	if [ -f "$PIDFILE" ]; then
		PID="$(cat "$PIDFILE")"
		if [ -d "/proc/$PID" ]; then
			kill -TERM "$PID"
		fi
		rm -f "$PIDFILE"
	fi

	# this is for the case of USER -> ACTDEAD -> USER
	touch /tmp/skip-fb-progress.tmp
}
