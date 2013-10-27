# In this CMakeLists.txt we define which files
# are used to compile the application
set(akonadimailsearch_SRCS
   akonadimailsearch.cpp
   main.cpp
 )

# Run ui files through uic
kde4_add_ui_files(akonadimailsearch_SRCS akonadimailsearch.ui)

# Set the name of the application
kde4_add_executable(akonadimailsearch ${akonadimailsearch_SRCS})

# Select which libraries we need to link to
target_link_libraries(akonadimailsearch ${KDE4_KDEUI_LIBS}  ${KDEPIMLIBS_AKONADI_LIBS} ${KDEPIMLIBS_AKONADI_CONTACT_LIBS})

# Tell cmake to install the application binary
install(TARGETS akonadimailsearch ${INSTALL_TARGETS_DEFAULT_ARGS})

# Install the .desktop file
install( PROGRAMS akonadimailsearch.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
