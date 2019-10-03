if (NOT EXISTS "/home/chaed/sources/SDL2-2.0.9/bin/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/home/chaed/sources/SDL2-2.0.9/bin/install_manifest.txt\"")
endif(NOT EXISTS "/home/chaed/sources/SDL2-2.0.9/bin/install_manifest.txt")

file(READ "/home/chaed/sources/SDL2-2.0.9/bin/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /home/chaed/programs/clion-2018.3.1/bin/cmake/linux/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

