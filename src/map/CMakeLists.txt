#
# setup
#
set( MAP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}  CACHE INTERNAL "" )


#
# map server
#
if( BUILD_SERVERS )
message( STATUS "Creating target map-server" )
file(GLOB_RECURSE MAP_HEADERS ${MAP_SOURCE_DIR}/*.hpp)
list(FILTER MAP_HEADERS EXCLUDE REGEX ".*/skills/.*")
file(GLOB_RECURSE MAP_SOURCES ${MAP_SOURCE_DIR}/*.cpp)
list(FILTER MAP_SOURCES EXCLUDE REGEX ".*/skills/.*")
if( WIN32 )
	set( MAP_RESOURCES "${MAP_SOURCE_DIR}/map-server.rc" )
	set( MAP_GENERATOR_RESOURCES "${MAP_SOURCE_DIR}/map-server-generator.rc" )
endif()
set( DEPENDENCIES common ryml)
set( LIBRARIES ${GLOBAL_LIBRARIES} ${MYSQL_LIBRARIES} )
set( INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${COMMON_BASE_INCLUDE_DIRS} ${RA_INCLUDE_DIRS} ${MYSQL_INCLUDE_DIRS} )
set( DEFINITIONS "${GLOBAL_DEFINITIONS} ${COMMON_BASE_DEFINITIONS}" )
if( WITH_PCRE )
	message( STATUS "Enabled PCRE code" )
	set( LIBRARIES ${LIBRARIES} ${PCRE_LIBRARIES} )
	set( INCLUDE_DIRS ${INCLUDE_DIRS} ${PCRE_INCLUDE_DIRS} )
	set( DEFINITIONS "${DEFINITIONS} -DPCRE_SUPPORT" )
else()
	message( STATUS "Disabled PCRE code" )
endif()
set( SOURCE_FILES ${COMMON_BASE_HEADERS} ${COMMON_HEADERS} ${MAP_HEADERS} ${MAP_SOURCES} ${MAP_RESOURCES} )
set( MAP_GENERATOR_SOURCE_FILES ${COMMON_BASE_HEADERS} ${COMMON_HEADERS} ${MAP_HEADERS} ${MAP_SOURCES} ${MAP_GENERATOR_RESOURCES} )
source_group( common FILES ${COMMON_BASE_HEADERS} ${COMMON_HEADERS} )
source_group( map FILES ${MAP_HEADERS} ${MAP_SOURCES} )
source_group( resources FILES ${MAP_RESOURCES} ${MAP_GENERATOR_RESOURCES} )
include_directories( ${INCLUDE_DIRS} )

#message( STATUS "map-server SOURCE_FILES=${SOURCE_FILES}")
add_executable( map-server ${SOURCE_FILES} )
#message( STATUS "map-server LIBRARIES=${LIBRARIES}, DEPENDENCIES=${DEPENDENCIES} DEFINITIONS=${DEFINITIONS}")
add_dependencies( map-server ${DEPENDENCIES} )
target_link_libraries( map-server ${LIBRARIES} ${DEPENDENCIES} )
set_target_properties( map-server PROPERTIES COMPILE_FLAGS "${DEFINITIONS}" )
if( INSTALL_COMPONENT_RUNTIME )
	cpack_add_component( Runtime_mapserver DESCRIPTION "map-server" DISPLAY_NAME "map-server" GROUP Runtime )
	install( TARGETS map-server
		DESTINATION "."
		COMPONENT Runtime_mapserver )
endif( INSTALL_COMPONENT_RUNTIME )

message( STATUS "Creating target map-server-generator" )
add_executable( map-server-generator ${MAP_GENERATOR_SOURCE_FILES} )
add_dependencies( map-server-generator ${DEPENDENCIES} )
target_link_libraries( map-server-generator ${LIBRARIES} ${DEPENDENCIES} )
set_target_properties( map-server-generator PROPERTIES COMPILE_FLAGS "${DEFINITIONS} -DMAP_GENERATOR" )
message( STATUS "Creating target map-server-generator - done" )

set( TARGET_LIST ${TARGET_LIST} map-server map-server-generator  CACHE INTERNAL "" )
message( STATUS "Creating target map-server - done" )
endif( BUILD_SERVERS )
