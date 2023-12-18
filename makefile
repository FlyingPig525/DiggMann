# ----------------------------
# Makefile Options
# ----------------------------

NAME = DiggMann
ICON = icon.png
DESCRIPTION = "Mr. DiggMann"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
