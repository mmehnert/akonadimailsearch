project(akonadimailsearch)

find_package(KDE4 REQUIRED)
find_package (KdepimLibs REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${KDEPIMLIBS_INCLUDE_DIRS}  ${QT_INCLUDES} )
#add_subdirectory( doc )
add_subdirectory( src )
