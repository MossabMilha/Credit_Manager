cmake_minimum_required(VERSION 3.10)
project(C_UI C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Find GTK4 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Check if GTK4 was found
if (NOT GTK4_FOUND)
    message(FATAL_ERROR "GTK4 not found. Please install it.")
endif()

# Include GTK include directories
include_directories(${GTK4_INCLUDE_DIRS})

# Add your source files
set(SOURCE_FILES
        main.c  # Your main file
        Most_Used_Password.txt
        # Add other source files here if needed
)

# Add your executable
add_executable(C_UI ${SOURCE_FILES})

# Link the GTK libraries
target_link_libraries(C_UI ${GTK4_LIBRARIES})

# Ensure the executable uses the GTK framework correctly
target_compile_options(C_UI PRIVATE ${GTK4_CFLAGS})

# Optional: Add additional settings for linking, if needed
set_target_properties(C_UI PROPERTIES
        LINK_FLAGS "-Wl,--enable-auto-import"
)


