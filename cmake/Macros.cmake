# Macro that helps defining an option
macro(ime_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Set the compile options used by all targets
function(ime_set_global_compile_flags target)
    if(IME_COMPILER_MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target}
            PRIVATE
            #-Wall
            #-Wextra
            #-Wshadow
            -Wnon-virtual-dtor
            #-Wold-style-cast
            #-Wcast-align
            #-Wunused
            -Woverloaded-virtual
            #-Wpedantic
            #-Wdouble-promotion
            #-Wformat=2
            )
    endif()

    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_${IME_CXX_STANDARD})
endfunction()

# Set the appropriate standard library on each platform for the given target
function(ime_set_stdlib target)

    # Apply the IME_USE_STATIC_STD_LIBS option on windows when using GCC (already done earlier when using VC++ which requires a global change)
    if(IME_OS_WINDOWS AND IME_COMPILER_GCC)
        if(IME_USE_STATIC_STD_LIBS AND NOT IME_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-static-libgcc" "-static-libstdc++")
        elseif(NOT IME_USE_STATIC_STD_LIBS AND IME_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-shared-libgcc" "-shared-libstdc++")
        endif()
    endif()
endfunction()

# Generate a IMEConfig.cmake file (and associated files)
function(ime_export_target export_name)
    include(CMakePackageConfigHelpers)
    if(CMAKE_VERSION VERSION_LESS 3.11)
        set(CVF_VERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH})
        configure_file("${PROJECT_SOURCE_DIR}/cmake/IMEConfigVersion.cmake.in" "${PROJECT_BINARY_DIR}/IMEConfigVersion.cmake" @ONLY)
    else()
        write_basic_package_version_file("${PROJECT_BINARY_DIR}/IMEConfigVersion.cmake"
        VERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH}
        COMPATIBILITY SameMinorVersion)
    endif()

    if (IME_SHARED_LIBS)
        set(targets_config_filename IMESharedTargets.cmake)
    else()
        set(targets_config_filename IMEStaticTargets.cmake)
    endif()

    export(EXPORT ${export_name}
            FILE "${PROJECT_BINARY_DIR}/${targets_config_filename}")

    if (IME_BUILD_FRAMEWORK)
        set(config_package_location "IME.framework/Resources/CMake")
    else()
        set(config_package_location ${CMAKE_INSTALL_LIBDIR}/cmake/IME)
    endif()
    configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/IMEConfig.cmake.in" "${PROJECT_BINARY_DIR}/IMEConfig.cmake"
        INSTALL_DESTINATION "${config_package_location}")

    install(EXPORT ${export_name}
            FILE ${targets_config_filename}
            DESTINATION ${config_package_location})

    install(FILES "${PROJECT_BINARY_DIR}/IMEConfig.cmake"
            "${PROJECT_BINARY_DIR}/IMEConfigVersion.cmake"
            DESTINATION ${config_package_location}
            COMPONENT devel)
endfunction()
