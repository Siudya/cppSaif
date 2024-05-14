add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

set_languages("c11", "cxx20")
set_toolchains("clang")

target("saif")
  set_kind("static")
  add_includedirs("include")
  add_rules("yacc")
  add_files("src/saif/*.y")
  add_files("src/saif/*.cpp")

target("main")
  add_includedirs("include")
  add_files("src/main.cpp")
  add_deps("saif")
