######################################################################
# Main project file: Joffrey_s_Journey.pro
######################################################################

TEMPLATE = subdirs

# Define sub-projects
SUBDIRS += app \
           tests

# Define dependencies between sub-projects
tests.depends = app
