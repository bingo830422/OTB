INCLUDE_ONCE_MACRO(GEOS)

SETUP_SUPERBUILD(GEOS)

if(MSVC)

  set(GEOS_URL "  https://github.com/libgeos/libgeos/archive/714127ef49087634e7f6687424fdf041d18c3d0f.zip")
  set(GEOS_URL_MD5 "d4bc49008dc712e8c612e8b8a91030c0")
  set(GEOS_SB_CONFIG "-DProject_WC_REVISION:STRING=99999")
  list(APPEND GEOS_SB_CONFIG "-DGEOS_BUILD_PACKAGED:BOOL=OFF")
else()
  set(GEOS_URL "http://download.osgeo.org/geos/geos-3.4.2.tar.bz2")
  set(GEOS_URL_MD5 "fc5df2d926eb7e67f988a43a92683bae")
  set(GEOS_SB_CONFIG)
endif()

ExternalProject_Add(GEOS
  PREFIX GEOS
  URL "${GEOS_URL}"
  URL_MD5 ${GEOS_URL_MD5}
  SOURCE_DIR ${GEOS_SB_SRC}
  BINARY_DIR ${GEOS_SB_BUILD_DIR}
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
  CMAKE_CACHE_ARGS
  ${SB_CMAKE_CACHE_ARGS}
  -DBUILD_TESTING:BOOL=OFF
  -DGEOS_ENABLE_TESTS:BOOL=OFF
  ${GEOS_SB_CONFIG}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND} )

SUPERBUILD_UPDATE_CMAKE_VARIABLES(GEOS FALSE)