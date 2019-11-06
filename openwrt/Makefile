include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=wuci
PKG_VERSION:=1.0
PKG_RELEASE:=1

# Source settings (i.e. where to find the source codes)
# This is a custom variable, used below
#SOURCE_DIR:=/home/buildbot/wuci

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/wuci
  SECTION:=libs
  CATEGORY:=Libraries
  SUBMENU:=Web toolkit
  TITLE:=WUCI
  DEPENDS:=+wt
  MENU:=1
endef

# Package description; a more verbose description on what our package does
define Package/wuci/description
  Webtoolkit based uci
endef

# Package preparation instructions; create the build directory and copy the source code. 
# The last command is necessary to ensure our preparation instructions remain compatible with the patching system.
#define Build/Prepare
#        mkdir -p $(PKG_BUILD_DIR)
#        cp $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
#        $(Build/Patch)
#endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/wuci/install
endef

$(eval $(call BuildPackage,wuci))