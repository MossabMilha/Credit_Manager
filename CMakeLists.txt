cmake_minimum_required(VERSION 3.10)
project(C_UI C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Find GTK4 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

# Check if GTK4 was found
if (NOT GTK_FOUND)
    message(FATAL_ERROR "GTK4 not found. Please install it.")
endif()

# Include GTK include directories
include_directories(${GTK_INCLUDE_DIRS})

# Add your source files
set(SOURCE_FILES
        main.c         # Your main file
        # Add other source files here if needed, e.g., patient.c
)

# Add your executable and link it with GTK4 libraries
add_executable(C_UI ${SOURCE_FILES})

# Link the GTK libraries
target_link_libraries(C_UI ${GTK_LIBRARIES})

# Additional settings for UCRT (if needed)
set_target_properties(C_UI PROPERTIES
        LINK_FLAGS "-Wl,--enable-auto-import"
)


