#! /bin/sh

### BEGIN INIT INFO
# Provides:          forked-daapd
# Required-Start:    $local_fs $remote_fs $network $time avahi
# Required-Stop:     $local_fs $remote_fs $network $time
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: media server with support for RSP, DAAP, DACP and AirTunes
# Description:       forked-daapd is an iTunes-compatible media server for
#                    sharing your music library over the local network with RSP
#                    clients like the SoundBridge from Roku and DAAP clients like
#                    iTunes. It can also stream music to AirTunes devices.
### END INIT INFO

PATH=@PREFIX@/sbin:@PREFIX@/bin:/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin
DAEMON=@PREFIX@/sbin/forked-daapd
NAME=forked-daapd
DESC="RSP and DAAP media server"

test -x $DAEMON || exit 0

PIDFILE=/var/run/$NAME.pid
DAEMON_OPTS="-P ${PIDFILE}"

set -e

running_pid()
{
    # Check if a given process pid's cmdline matches a given name
    pid=$1
    name=$2
    [ -z "$pid" ] && return 1
    [ ! -d /proc/$pid ] &&  return 1
    cmd=`cat /proc/$pid/cmdline | tr "\000" "\n"|head -n 1 |cut -d : -f 1`
    # Is this the expected child?
    [ "$cmd" != "$name" ] &&  return 1
    return 0
}

running()
{
# Check if the process is running looking at /proc
# (works for all users)

    # No pidfile, probably no daemon present
    [ ! -f "$PIDFILE" ] && return 1
    # Obtain the pid and check it against the binary name
    pid=`cat $PIDFILE`
    running_pid $pid $DAEMON || return 1
    return 0
}

force_stop() {
# Forcefully kill the process
    [ ! -f "$PIDFILE" ] && return
    if running ; then
        kill -15 $pid
        # Is it really dead?
        if running ; then
            kill -9 $pid
            if running ; then
                echo "Cannot kill $NAME (pid=$pid)!"
                exit 1
            fi
        fi
    fi
    rm -f $PIDFILE
    return 0
}

case "$1" in
  start)
        echo -n "Starting $DESC: "
        start-stop-daemon --start --quiet --pidfile $PIDFILE \
            --exec $DAEMON -- $DAEMON_OPTS
        if running ; then
            echo "$NAME."
        else
            echo " ERROR."
        fi
        ;;
  stop)
        echo -n "Stopping $DESC: "
        start-stop-daemon --oknodo --stop --quiet --pidfile $PIDFILE \
            --exec $DAEMON
        echo "$NAME."
        ;;
  force-reload)
        start-stop-daemon --stop --test --quiet --pidfile \
            /var/run/$NAME.pid --exec $DAEMON \
            && $0 restart \
            || exit 0
        ;;
  restart)
        PID=$(cat $PIDFILE 2> /dev/null || true)

        echo -n "Restarting $DESC: "
        start-stop-daemon --stop --quiet --oknodo --pidfile \
            /var/run/$NAME.pid --exec $DAEMON

        if [ -n "$PID" ]; then
            while running_pid $PID $DAEMON; do echo -n "."; sleep 1; done
        fi

        start-stop-daemon --start --quiet --pidfile \
            /var/run/$NAME.pid --exec $DAEMON -- $DAEMON_OPTS
        echo "$NAME."
        ;;
  status)
    echo -n "$NAME is "
    if running ;  then
        echo "running"
    else
        echo " not running."
        exit 1
    fi
    ;;
  *)
    N=/etc/init.d/$NAME
    echo "Usage: $N {start|stop|restart|force-reload|status}" >&2
    exit 1
    ;;
esac

exit 0
