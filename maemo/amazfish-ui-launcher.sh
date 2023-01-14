#!/bin/sh

# We need to kill any existing pipewire instance to restore sound
pkill -u "${USER}" -x harbour-amazfish-ui 1>/dev/null 2>&1
export QT_STYLE_OVERRIDE=adwaita
exec /usr/bin/harbour-amazfish-ui

