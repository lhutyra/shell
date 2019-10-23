cmake_minimum_required(VERSION 3.10)

project(shell LANGUAGES C VERSION 0.1.0)

# Compile Application

set(SOURCES src/buffer.c
            src/command.c
            src/execute.c
            src/main.c
            src/parse.c
            src/prompt.c
            src/command_table.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

# Install Application

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)

# Package Application

set(CPACK_PACKAGE_VENDOR "George Fotopoulos")
set(CPACK_PACKAGE_CONTACT "xorz57@protonmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Basic Shell Implementation in C99")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

include(CPack)
