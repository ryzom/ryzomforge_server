FIND_PACKAGE_HELPER(Mongo mongo/client/dbclient.h RELEASE mongoclient DEBUG mongoclientd)

IF(MONGO_FOUND)
  FIND_PACKAGE(OpenSSL REQUIRED)
  FIND_PACKAGE(MyBoost COMPONENTS system filesystem thread REQUIRED)
  FIND_PACKAGE(Threads REQUIRED)

  SET(MONGO_LIBRARIES ${MONGO_LIBRARIES} ${BOOST_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF()
