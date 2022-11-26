# fetchme's config.
# options can be turned on with either
# `Y' or `y'. to deselect an option,
# comment it out.

# to set a custom color,
# uncomment both CUSTOM_COLOR
# and CUSTOM_COLOR_VALUE
# M_CUSTOM_COLOR=y
# options are: RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE
# M_CUSTOM_COLOR_VALUE=CYAN

# Works with FreeBSD
M_USERNAME_HOSTNAME=y

# Works with FreeBSD
M_DISTRO=y

# Works with FreeBSD
M_KERNEL=y

# Does NOT work with FreeBSD
M_UPTIME=y

# Off by default.
# Currently only works
# with pacman-based
# distros and
# portage-based
# distros.
#
# Works with FreeBSD
M_PACKAGE=y

# Works with FreeBSD
# M_SHELL=y

# Might work with FreeBSD
# XCB might be faster than Xlib
# both modules must be uncommented
# and set to 'y' to use xcb. otherwise,
# Xlib is used.
M_RESOLUTION=y
# M_RESOLUTION_XCB=y

# Might work with FreeBSD
# XCB might be faster than Xlib
# both modules must be uncommented
# and set to 'y' to use xcb. otherwise,
# Xlib is used.
M_REFRESH_RATE=y
# M_REFRESH_RATE_XCB=y

# Might work with FreeBSD
# M_WM only works with XWayland and X11.
# M_WM_WAYLAND only works with Wayland (but is slower)
M_WM=y
# M_WM_WAYLAND=y

# Works with FreeBSD
M_TERMINAL=y

# any option associated with CPU
# needs to have CPU=y
# Does NOT work with FreeBSD
M_CPU=y
M_CPU_THREADS=y
# commented out by default since
# it's **experimental**
# M_CPU_TEMP=y
M_CPU_FREQUENCY=y

# Works with FreeBSD
M_GPU=y

# any option associated with MEMORY
# needs to have MEMORY=y
# Does NOT work with FreeBSD
M_MEMORY=y
M_MEMORY_PERCENT=y

# any option associated with DISK
# needs to have DISK=y
# Does NOT work with FreeBSD
M_DISK=y
M_DISK_PERCENT=y
