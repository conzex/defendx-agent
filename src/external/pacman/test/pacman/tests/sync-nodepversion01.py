self.description = "nodepversion: -Sd works"

p1 = pmpkg("pkg1", "1.0-2")
p1.depends = ["provision>1.0-1"]
self.addpkg2db("sync", p1)

p2 = pmpkg("pkg2", "1.0-2")
p2.provides = ["provision=1.0-1"]
self.addpkg2db("sync", p2)

self.args = "-Sd %s" % p1.name

self.addrule("PACMAN_RETCODE=0")
self.addrule("PKG_EXIST=pkg1")
self.addrule("PKG_EXIST=pkg2")
self.addrule("PKG_DEPENDS=pkg1|provision>1.0-1")
