set_project("Telly")

target("Telly")
    set_kind("binary")
    set_rundir("$(projectdir)")

    set_languages("cxx17")
    set_warnings("all")

    add_includedirs("src", "include")

    add_files("src/*.cpp")

    add_linkdirs("lib")

    add_links("SDL3", "SDL3_ttf", "SDL3_image")
