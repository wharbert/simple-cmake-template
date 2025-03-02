#Generate and symlink compile_commands.json for clangd LS - may be replaced with .clangd
if (PROJECT_IS_TOP_LEVEL AND UNIX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()