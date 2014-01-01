import os
import sys

if not len(sys.argv) >= 2:
    raise Exception("You need to give the name of the example as argument!")

current_directory = os.getcwd()

if current_directory.endswith("scripts"):
    os.chdir("./..")
    current_directory = os.getcwd()

example_name = sys.argv[1]
example_path = "examples/" + example_name

if os.path.exists(example_path):
    dist_path = "dist/" + example_path
    grantlee_path = "dist/3rdparty/grantlee"

    # Standard plugins
    standard_plugin_names = [
        "defaultfilters",
        "defaulttags",
        "i18n",
        "loadertags",
    ]

    plugin_link_names = {
        "defaultfilters": "grantlee_defaultfilters",
        "defaulttags"   : "grantlee_defaulttags",
        "loadertags"    : "grantlee_loadertags",
        "i18n"          : "grantlee_i18n",
    }

    for plugin_name in standard_plugin_names:
        plugin_path = grantlee_path + "/" + plugin_name
        if not os.path.exists(plugin_path):
            raise Exception("Path (" + plugin_path + ") doesn't exists!")

        debug_path = plugin_path + "/debug/lib" + plugin_name + ".so.1.0.0"
        release_path = plugin_path + "/release/lib" + plugin_name + ".so.1.0.0"

        debug_plugin_dist_path = dist_path + "/debug/plugins/grantlee/0.1/"
        release_plugin_dist_path = dist_path + "/release/plugins/grantlee/0.1/"

        if not os.path.exists(debug_plugin_dist_path):
            os.makedirs(debug_plugin_dist_path)

        if not os.path.exists(release_plugin_dist_path):
            os.makedirs(release_plugin_dist_path)

        link_name = plugin_link_names[plugin_name]
        debug_link_path = debug_plugin_dist_path + link_name
        release_link_path = release_plugin_dist_path + link_name

        if not os.path.lexists(debug_link_path):
            os.symlink(os.path.abspath(debug_path), debug_link_path)

        if not os.path.lexists(release_link_path):
            os.symlink(os.path.abspath(release_path), release_link_path)

else:
    raise Exception("Path (" + example_path + ") doesn't exists!")
