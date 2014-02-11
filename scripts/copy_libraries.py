#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import shutil
import sys
import infos

if not len(sys.argv) >= 2:
    raise Exception("You need to give the dist path!")

current_directory = os.getcwd()
destination_path = sys.argv[1]
constants = infos.VARIABLES

if current_directory.endswith("scripts"):
    os.chdir("./..")
    current_directory = os.getcwd()

_3rdparty_list = constants["3rdparty"]
for _3rdparty in _3rdparty_list:
    copy_path = constants["3rdparty_dist_dir"] + _3rdparty["dir"] + "/debug/" + _3rdparty["lib"]
    shutil.copyfile(copy_path, destination_path + _3rdparty["lib"].replace(".0.0", ""))

public_system_library_path = "dist/"
public_system_library = "libPublic-Server-System.1.0.0.dylib"
shutil.copyfile(copy_path, destination_path + public_system_library.replace(".0.0", ""))
