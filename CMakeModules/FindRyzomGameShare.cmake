INCLUDE(FindHelpers)

FIND_PACKAGE_HELPER(RyzomGameShare game_share/continent.h RELEASE ryzom_gameshare_r ryzom_gameshare DEBUG ryzom_gameshare_d DIR ${NEL_DIR} ${RYZOM_DIR} SUFFIXES ryzom)

IF(RYZOMGAMESHARE_FOUND)
  SET(RYZOM_GAMESHARE_LIBRARIES ${RYZOMGAMESHARE_LIBRARIES})
  SET(RYZOM_GAMESHARE_FOUND ${RYZOMGAMESHARE_FOUND})
  SET(RYZOM_GAMESHARE_INCLUDE_DIR ${RYZOMGAMESHARE_INCLUDE_DIR})
  SET(RYZOM_GAMESHARE_INCLUDE_DIRS ${RYZOMGAMESHARE_INCLUDE_DIRS})
ENDIF()
