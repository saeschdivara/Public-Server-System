import os
import sys

# Webserver
os.chdir("./dist/3rdparty/qt-http-server/release/")
try:
    os.system("rm -r *.*")
except:
    pass
os.system("qmake ./../../../../3rdparty/Qt-Http-Server/")
os.system("make -j8")

# ArangoDB
os.chdir("./../../arangodb-driver/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../3rdparty/arangodb-driver/src")
os.system("make -j8")

# smpt-client-qt
os.chdir("./../../smpt-client-qt/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../3rdparty/smpt-client-qt/")
os.system("make -j8")

# grantlee
os.chdir("./../../grantlee/template_library/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../../3rdparty/grantlee/templates/lib/")
os.system("make -j8")

os.chdir("./../../defaulttags/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../../3rdparty/grantlee/templates/defaulttags/")
os.system("make -j8")

os.chdir("./../../defaultfilters/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../../3rdparty/grantlee/templates/defaultfilters/")
os.system("make -j8")

os.chdir("./../../loadertags/release")
os.system("rm -r *.*")
os.system("qmake ./../../../../../3rdparty/grantlee/templates/loadertags/")
os.system("make -j8")

# Public-Server-System
os.chdir("./../../../../Public-Server-System/release")
os.system("rm -r *.*")
os.system("qmake ./../../../src/")
os.system("make -j8")