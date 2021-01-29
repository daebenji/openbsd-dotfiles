#!/bin/sh
set -x

# Script to install environment
SCRIPT_DIR=$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )
REPO_ROOT_DIR=$(dirname $(dirname $SCRIPT_DIR) )

ZSH_BIN=/usr/local/bin/zsh
DWM_BUILD_DIR=$REPO_ROOT_DIR/.config/dwm
ST_BUILD_DIR=$REPO_ROOT_DIR/.config/st
DMENU_BUILD_DIR=$REPO_ROOT_DIR/.config/dmenu


function checkExitCode {
  	local ec=$?
  	local errorMessage=$1
  	if [ $ec -ne 0 ]; then
  	  echo "Error: $errorMessage. EC=$ec"
  	  exit 1
  	fi
}

# rm .git because permission problem
rm -rf $REPO_ROOT_DIR/.git

# copy files from git repo into home directory
cp -r $REPO_ROOT_DIR/.* ~/ || checkExitCode "Failed to copy files to ~/"

# package to install with root
case $1 in
	root)
		pkg_add neovim zsh colorls ranger || checkExitCode "Failed to install Packages"
		doas echo "permit nopass :wheel" > /etc/doas.conf

		# build dwm
		cd $DWM_BUILD_DIR || checkExitCode "Directory $DWM_BUILD_DIR not found"
		make || checkExitCode "Failed to build DWM in $DWM_BUILD_DIR"
		make install || checkExitCode "Failed to install DWM"

		# build st
		cd $ST_BUILD_DIR || checkExitCode "Directory $ST_BUILD_DIR not found"
		make || checkExitCode "Failed to build ST in $ST_BUILD_DIR"
		make install || checkExitCode "Failed to install ST"

		# build dmenu
		cd $DMENU_BUILD_DIR || checkExitCode "Directory $DMENU_BUILD_DIR not found"
		make || checkExitCode "Failed to build DMENU in $DMENU_BUILD_DIR"
		make install || checkExitCode "Failed to install DMENU"
		;;
esac

# switch default shell to zsh
chsh -s $ZSH_BIN || checkExitCode "Failed to set $ZSH_BIN as new Shell"
$ZSH_BIN || checkExitCode "Failed to set $ZSH_BIN as new Shell"

# enable xenodm
rcctl enable xenodm || checkExitCode "Failed to start xenodm"

# start xenodm
rcctel start xenodm || checkExitCode "Failed to start xenodm"

echo done.
exit 0
