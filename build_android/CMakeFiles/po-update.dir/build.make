# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ignat99/Projects/OpenCPN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ignat99/Projects/OpenCPN/build_android

# Utility rule file for po-update.

# Include the progress variables for this target.
include CMakeFiles/po-update.dir/progress.make

CMakeFiles/po-update: ../po/opencpn.pot
CMakeFiles/po-update: ../po/opencpn_ru_RU.po.dummy
CMakeFiles/po-update: ../po/opencpn_tr_TR.po.dummy
CMakeFiles/po-update: ../po/opencpn_zh_TW.po.dummy
CMakeFiles/po-update: ../po/opencpn_pt_BR.po.dummy
CMakeFiles/po-update: ../po/opencpn_et_ET.po.dummy
CMakeFiles/po-update: ../po/opencpn_sv_SE.po.dummy
CMakeFiles/po-update: ../po/opencpn_nl_NL.po.dummy
CMakeFiles/po-update: ../po/opencpn_cs_CZ.po.dummy
CMakeFiles/po-update: ../po/opencpn_es_ES.po.dummy
CMakeFiles/po-update: ../po/opencpn_it_IT.po.dummy
CMakeFiles/po-update: ../po/opencpn_fi_FI.po.dummy
CMakeFiles/po-update: ../po/opencpn_hu_HU.po.dummy
CMakeFiles/po-update: ../po/opencpn_fr_FR.po.dummy
CMakeFiles/po-update: ../po/opencpn_pt_PT.po.dummy
CMakeFiles/po-update: ../po/opencpn_nb_NO.po.dummy
CMakeFiles/po-update: ../po/opencpn_de_DE.po.dummy
CMakeFiles/po-update: ../po/opencpn_pl_PL.po.dummy
CMakeFiles/po-update: ../po/opencpn_ca_ES.po.dummy
CMakeFiles/po-update: ../po/opencpn_da_DK.po.dummy
CMakeFiles/po-update: ../po/opencpn_el_GR.po.dummy
CMakeFiles/po-update: ../po/opencpn_gl_ES.po.dummy
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update: Done."

../po/opencpn_ru_RU.po.dummy: ../po/opencpn.pot
../po/opencpn_ru_RU.po.dummy: ../po/opencpn_ru_RU.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_ru_RU]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_ru_RU.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_tr_TR.po.dummy: ../po/opencpn.pot
../po/opencpn_tr_TR.po.dummy: ../po/opencpn_tr_TR.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_tr_TR]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_tr_TR.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_zh_TW.po.dummy: ../po/opencpn.pot
../po/opencpn_zh_TW.po.dummy: ../po/opencpn_zh_TW.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_zh_TW]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_zh_TW.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_pt_BR.po.dummy: ../po/opencpn.pot
../po/opencpn_pt_BR.po.dummy: ../po/opencpn_pt_BR.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_pt_BR]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_pt_BR.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_et_ET.po.dummy: ../po/opencpn.pot
../po/opencpn_et_ET.po.dummy: ../po/opencpn_et_ET.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_et_ET]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_et_ET.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_sv_SE.po.dummy: ../po/opencpn.pot
../po/opencpn_sv_SE.po.dummy: ../po/opencpn_sv_SE.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_sv_SE]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_sv_SE.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_nl_NL.po.dummy: ../po/opencpn.pot
../po/opencpn_nl_NL.po.dummy: ../po/opencpn_nl_NL.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_nl_NL]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_nl_NL.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_cs_CZ.po.dummy: ../po/opencpn.pot
../po/opencpn_cs_CZ.po.dummy: ../po/opencpn_cs_CZ.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_cs_CZ]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_cs_CZ.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_es_ES.po.dummy: ../po/opencpn.pot
../po/opencpn_es_ES.po.dummy: ../po/opencpn_es_ES.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_es_ES]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_es_ES.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_it_IT.po.dummy: ../po/opencpn.pot
../po/opencpn_it_IT.po.dummy: ../po/opencpn_it_IT.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_it_IT]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_it_IT.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_fi_FI.po.dummy: ../po/opencpn.pot
../po/opencpn_fi_FI.po.dummy: ../po/opencpn_fi_FI.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_fi_FI]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_fi_FI.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_hu_HU.po.dummy: ../po/opencpn.pot
../po/opencpn_hu_HU.po.dummy: ../po/opencpn_hu_HU.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_hu_HU]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_hu_HU.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_fr_FR.po.dummy: ../po/opencpn.pot
../po/opencpn_fr_FR.po.dummy: ../po/opencpn_fr_FR.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_fr_FR]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_fr_FR.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_pt_PT.po.dummy: ../po/opencpn.pot
../po/opencpn_pt_PT.po.dummy: ../po/opencpn_pt_PT.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_pt_PT]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_pt_PT.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_nb_NO.po.dummy: ../po/opencpn.pot
../po/opencpn_nb_NO.po.dummy: ../po/opencpn_nb_NO.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_16)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_nb_NO]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_nb_NO.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_de_DE.po.dummy: ../po/opencpn.pot
../po/opencpn_de_DE.po.dummy: ../po/opencpn_de_DE.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_17)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_de_DE]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_de_DE.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_pl_PL.po.dummy: ../po/opencpn.pot
../po/opencpn_pl_PL.po.dummy: ../po/opencpn_pl_PL.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_18)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_pl_PL]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_pl_PL.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_ca_ES.po.dummy: ../po/opencpn.pot
../po/opencpn_ca_ES.po.dummy: ../po/opencpn_ca_ES.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_19)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_ca_ES]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_ca_ES.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_da_DK.po.dummy: ../po/opencpn.pot
../po/opencpn_da_DK.po.dummy: ../po/opencpn_da_DK.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_20)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_da_DK]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_da_DK.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_el_GR.po.dummy: ../po/opencpn.pot
../po/opencpn_el_GR.po.dummy: ../po/opencpn_el_GR.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_21)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_el_GR]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_el_GR.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

../po/opencpn_gl_ES.po.dummy: ../po/opencpn.pot
../po/opencpn_gl_ES.po.dummy: ../po/opencpn_gl_ES.po
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles $(CMAKE_PROGRESS_22)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "po-update [opencpn_gl_ES]: Updated po file."
	/usr/bin/msgmerge --width=80 --strict --quiet --update --backup=none --no-location -s /home/ignat99/Projects/OpenCPN/po/opencpn_gl_ES.po /home/ignat99/Projects/OpenCPN/po/opencpn.pot

po-update: CMakeFiles/po-update
po-update: ../po/opencpn_ru_RU.po.dummy
po-update: ../po/opencpn_tr_TR.po.dummy
po-update: ../po/opencpn_zh_TW.po.dummy
po-update: ../po/opencpn_pt_BR.po.dummy
po-update: ../po/opencpn_et_ET.po.dummy
po-update: ../po/opencpn_sv_SE.po.dummy
po-update: ../po/opencpn_nl_NL.po.dummy
po-update: ../po/opencpn_cs_CZ.po.dummy
po-update: ../po/opencpn_es_ES.po.dummy
po-update: ../po/opencpn_it_IT.po.dummy
po-update: ../po/opencpn_fi_FI.po.dummy
po-update: ../po/opencpn_hu_HU.po.dummy
po-update: ../po/opencpn_fr_FR.po.dummy
po-update: ../po/opencpn_pt_PT.po.dummy
po-update: ../po/opencpn_nb_NO.po.dummy
po-update: ../po/opencpn_de_DE.po.dummy
po-update: ../po/opencpn_pl_PL.po.dummy
po-update: ../po/opencpn_ca_ES.po.dummy
po-update: ../po/opencpn_da_DK.po.dummy
po-update: ../po/opencpn_el_GR.po.dummy
po-update: ../po/opencpn_gl_ES.po.dummy
po-update: CMakeFiles/po-update.dir/build.make
.PHONY : po-update

# Rule to build all files generated by this target.
CMakeFiles/po-update.dir/build: po-update
.PHONY : CMakeFiles/po-update.dir/build

CMakeFiles/po-update.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/po-update.dir/cmake_clean.cmake
.PHONY : CMakeFiles/po-update.dir/clean

CMakeFiles/po-update.dir/depend:
	cd /home/ignat99/Projects/OpenCPN/build_android && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ignat99/Projects/OpenCPN /home/ignat99/Projects/OpenCPN /home/ignat99/Projects/OpenCPN/build_android /home/ignat99/Projects/OpenCPN/build_android /home/ignat99/Projects/OpenCPN/build_android/CMakeFiles/po-update.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/po-update.dir/depend
