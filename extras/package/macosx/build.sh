#!/bin/sh
set -e

info()
{
    local green="\033[1;32m"
    local normal="\033[0m"
    echo "[${green}build${normal}] $1"
}

<<<<<<< master
SCRIPTDIR=$(dirname "$0")
source "$SCRIPTDIR/env.build.sh" "none"

=======
ARCH="x86_64"
MINIMAL_OSX_VERSION="10.7"
OSX_KERNELVERSION=`uname -r | cut -d. -f1`
BUILD_ARCH=`uname -m | cut -d. -f1`
>>>>>>> origin/3.0.x
SDKROOT=$(xcrun --show-sdk-path)
VLCBUILDDIR=""

CORE_COUNT=`getconf NPROCESSORS_ONLN 2>&1`
let JOBS=$CORE_COUNT+1

if [ ! -z "$VLC_FORCE_KERNELVERSION" ]; then
    OSX_KERNELVERSION="$VLC_FORCE_KERNELVERSION"
fi

usage()
{
cat << EOF
usage: $0 [options]

Build vlc in the current directory

OPTIONS:
   -h            Show some help
   -q            Be quiet
   -j            Force number of cores to be used
   -r            Rebuild everything (tools, contribs, vlc)
   -c            Recompile contribs from sources
   -p            Build packages for all artifacts
<<<<<<< master
   -i <n|u|z>    Create an installable package
                     n: nightly
                     u: unsigned stripped release archive
                     z: zip
=======
   -i <n|u>      Create an installable package (n: nightly, u: unsigned stripped release archive)
>>>>>>> origin/3.0.x
   -k <sdk>      Use the specified sdk (default: $SDKROOT)
   -a <arch>     Use the specified arch (default: $HOST_ARCH)
   -C            Use the specified VLC build dir
   -b <url>      Enable breakpad support and send crash reports to this URL
<<<<<<< master
   -d            Disable debug mode (on by default)
=======
>>>>>>> origin/3.0.x
EOF

}

spushd()
{
    pushd "$1" > /dev/null
}

spopd()
{
    popd > /dev/null
}

<<<<<<< master
while getopts "qhvrcdpi:k:a:j:C:b:" OPTION
=======
get_actual_arch() {
    if [ "$1" = "aarch64" ]; then
        echo "arm64"
    else
        echo "$1"
    fi
}

get_buildsystem_arch() {
    if [ "$1" = "arm64" ]; then
        echo "aarch64"
    else
        echo "$1"
    fi
}

while getopts "hvrcpi:k:a:j:C:b:" OPTION
>>>>>>> origin/3.0.x
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         q)
             set +x
             QUIET="yes"
         ;;
         d)
             NODEBUG="yes"
         ;;
         r)
             REBUILD="yes"
         ;;
         c)
             CONTRIBFROMSOURCE="yes"
         ;;
         p)
             PACKAGE="yes"
         ;;
         i)
             PACKAGETYPE=$OPTARG
         ;;
         a)
             HOST_ARCH=$OPTARG
         ;;
         k)
             SDKROOT=$OPTARG
         ;;
         j)
             JOBS=$OPTARG
         ;;
         C)
             VLCBUILDDIR=$OPTARG
         ;;
         b)
             BREAKPAD=$OPTARG
         ;;
         *)
             usage
             exit 1
         ;;
     esac
done
shift $(($OPTIND - 1))

if [ "x$1" != "x" ]; then
    usage
    exit 1
fi

#
# Various initialization
#

out="/dev/stdout"
if [ "$QUIET" = "yes" ]; then
    out="/dev/null"
fi

<<<<<<< master
ACTUAL_HOST_ARCH=`get_actual_arch $HOST_ARCH`
=======
ACTUAL_ARCH=`get_actual_arch $ARCH`
BUILD_ARCH=`get_buildsystem_arch $BUILD_ARCH`
BUILD_TRIPLET=$BUILD_ARCH-apple-darwin$OSX_KERNELVERSION
HOST_TRIPLET=$ARCH-apple-darwin$OSX_KERNELVERSION

info "Building VLC for macOS for architecture ${ACTUAL_ARCH} on a ${BUILD_ARCH} device"
>>>>>>> origin/3.0.x

info "Building VLC for macOS, architecture ${HOST_ARCH} (aka: ${ACTUAL_HOST_ARCH}) on a ${BUILD_ARCH} device"

BUILD_TRIPLET=$(vlcGetBuildTriplet)
HOST_TRIPLET=$(vlcGetHostTriplet)
export SDKROOT
vlcSetBaseEnvironment
vlcroot="$(vlcGetRootDir)"

# Checking prerequisites
info "Checking for python3 ..."
python3 --version || { echo "python3 not found. Please install from python.org, or set" \
	"VLC_PATH environment variable to include python3." \
	; exit 1; }

<<<<<<< master

builddir="$(pwd)"
info "Building in \"$builddir\""
=======
python3Path=$(echo /Library/Frameworks/Python.framework/Versions/3.*/bin | awk '{print $1;}')
if [ ! -d "$python3Path" ]; then
	python3Path=""
fi

export AR="`xcrun --find ar`"
export CC="`xcrun --find clang`"
export CXX="`xcrun --find clang++`"
export NM="`xcrun --find nm`"
export OBJC="`xcrun --find clang`"
export RANLIB="`xcrun --find ranlib`"
export STRINGS="`xcrun --find strings`"
export STRIP="`xcrun --find strip`"
export SDKROOT
export PATH="${vlcroot}/extras/tools/build/bin:${vlcroot}/contrib/${BUILD_TRIPLET}/bin:$python3Path:${VLC_PATH}:/bin:/sbin:/usr/bin:/usr/sbin"

# Select avcodec flavor to compile contribs with
export USE_FFMPEG=1

# The following symbols do not exist on the minimal macOS version (10.7), so they are disabled
# here. This allows compilation also with newer macOS SDKs.

# Added symbols in macOS 10.15 / iOS 13 / tvOS 13
export ac_cv_func_aligned_alloc=no
export ac_cv_func_timespec_get=no

# Added symbol in macOS 10.14 / iOS 12 / tvOS 9
export ac_cv_func_thread_get_register_pointer_values=no

# Added symbols in macOS 10.13 / iOS 11 / tvOS 11
export ac_cv_func_utimensat=no
export ac_cv_func_futimens=no

# Added symbols in 10.13
export ac_cv_func_open_wmemstream=no
export ac_cv_func_fmemopen=no
export ac_cv_func_open_memstream=no
export ac_cv_func_futimens=no
export ac_cv_func_utimensat=no

# Added symbols between 10.11 and 10.12
export ac_cv_func_basename_r=no
export ac_cv_func_clock_getres=no
export ac_cv_func_clock_gettime=no
export ac_cv_func_clock_settime=no
export ac_cv_func_dirname_r=no
export ac_cv_func_getentropy=no
export ac_cv_func_mkostemp=no
export ac_cv_func_mkostemps=no
export ac_cv_func_timingsafe_bcmp=no

# Added symbols between 10.7 and 10.11
export ac_cv_func_ffsll=no
export ac_cv_func_flsll=no
export ac_cv_func_fdopendir=no
export ac_cv_func_openat=no
export ac_cv_func_fstatat=no
export ac_cv_func_readlinkat=no
export ac_cv_func_linkat=no
export ac_cv_func_unlinkat=no

# Added symbols between 10.7 and 10.9
export ac_cv_func_memset_s=no

# libnetwork does not exist yet on 10.7 (used by libcddb)
export ac_cv_lib_network_connect=no
>>>>>>> origin/3.0.x

#
# vlc/extras/tools
#

info "Building building tools"
spushd "${vlcroot}/extras/tools"
./bootstrap > $out
if [ "$REBUILD" = "yes" ]; then
    make clean
    ./bootstrap > $out
fi
make > $out
spopd

#
# vlc/contribs
#

vlcSetSymbolEnvironment
vlcSetContribEnvironment "$MINIMAL_OSX_VERSION"

export EXTRA_CFLAGS="-isysroot $SDKROOT -mmacosx-version-min=$MINIMAL_OSX_VERSION -DMACOSX_DEPLOYMENT_TARGET=$MINIMAL_OSX_VERSION -arch $ACTUAL_ARCH"
export EXTRA_LDFLAGS="-Wl,-syslibroot,$SDKROOT -mmacosx-version-min=$MINIMAL_OSX_VERSION -isysroot $SDKROOT -DMACOSX_DEPLOYMENT_TARGET=$MINIMAL_OSX_VERSION -arch $ACTUAL_ARCH"
# xcodebuild only allows to set a build-in sdk, not a custom one. Therefore use the default included SDK here
export XCODE_FLAGS="MACOSX_DEPLOYMENT_TARGET=$MINIMAL_OSX_VERSION -sdk macosx WARNING_CFLAGS=-Werror=partial-availability"

info "Building contribs"
spushd "${vlcroot}/contrib"
<<<<<<< master

=======
mkdir -p contrib-$HOST_TRIPLET && cd contrib-$HOST_TRIPLET
../bootstrap --build=$BUILD_TRIPLET --host=$HOST_TRIPLET > $out
>>>>>>> origin/3.0.x
if [ "$REBUILD" = "yes" ]; then
    rm -rf contrib-$HOST_TRIPLET
    rm -rf $HOST_TRIPLET
fi
mkdir -p contrib-$HOST_TRIPLET && cd contrib-$HOST_TRIPLET
../bootstrap --build=$BUILD_TRIPLET --host=$HOST_TRIPLET > $out

make list
if [ "$CONTRIBFROMSOURCE" != "yes" ]; then
    if [ ! -e "../$HOST_TRIPLET" ]; then
        if [ -n "$VLC_PREBUILT_CONTRIBS_URL" ]; then
            make prebuilt PREBUILT_URL="$VLC_PREBUILT_CONTRIBS_URL" || PREBUILT_FAILED=yes
        else
            make prebuilt || PREBUILT_FAILED=yes
        fi
    fi
else
    PREBUILT_FAILED=yes
fi
if [ -n "$PREBUILT_FAILED" ]; then
    make fetch
    make -j$JOBS .gettext
    make -j$JOBS -k || make -j1

    if [ "$PACKAGE" = "yes" ]; then
        make package
    fi
else
<<<<<<< master
    make -j$JOBS tools
=======
if [ ! -e "../$HOST_TRIPLET" ]; then
    if [ -n "$VLC_PREBUILT_CONTRIBS_URL" ]; then
        make prebuilt PREBUILT_URL="$VLC_PREBUILT_CONTRIBS_URL"
        make .luac
    else
        make prebuilt
        make .luac
    fi
fi
>>>>>>> origin/3.0.x
fi
spopd


<<<<<<< master
vlcUnsetContribEnvironment
vlcSetLibVLCEnvironment
=======
unset EXTRA_CFLAGS
unset EXTRA_LDFLAGS
unset XCODE_FLAGS

# Enable debug symbols by default
export CFLAGS="-g -arch $ACTUAL_ARCH"
export CXXFLAGS="-g -arch $ACTUAL_ARCH"
export OBJCFLAGS="-g -arch $ACTUAL_ARCH"
export LDFLAGS="-arch $ACTUAL_ARCH"
>>>>>>> origin/3.0.x

#
# vlc/bootstrap
#

info "Bootstrap-ing configure"
spushd "${vlcroot}"
if ! [ -e "${vlcroot}/configure" ]; then
    ${vlcroot}/bootstrap > $out
fi
spopd


if [ ! -z "$VLCBUILDDIR" ];then
    mkdir -p $VLCBUILDDIR
    pushd $VLCBUILDDIR
fi
#
# vlc/configure
#

CONFIGFLAGS=""
if [ ! -z "$BREAKPAD" ]; then
     CONFIGFLAGS="$CONFIGFLAGS --with-breakpad=$BREAKPAD"
fi
<<<<<<< master
if [ "$NODEBUG" = "yes" ]; then
     CONFIGFLAGS="$CONFIGFLAGS --disable-debug"
fi
=======
>>>>>>> origin/3.0.x

if [ "${vlcroot}/configure" -nt Makefile ]; then

  ${vlcroot}/extras/package/macosx/configure.sh \
      --build=$BUILD_TRIPLET \
      --host=$HOST_TRIPLET \
      --with-macosx-version-min=$MINIMAL_OSX_VERSION \
      --with-macosx-sdk=$SDKROOT \
      $CONFIGFLAGS \
      $VLC_CONFIGURE_ARGS > $out
fi

#
# make
#

if [ "$REBUILD" = "yes" ]; then
    info "Running make clean"
    make clean
fi

info "Running make -j$JOBS"
make -j$JOBS

info "Preparing VLC.app"
make VLC.app

<<<<<<< master
=======
# Workaround for macOS 10.7: CFNetwork only exists as part of CoreServices framework
if [ "$ARCH" = "x86_64" ]; then
    install_name_tool -change /System/Library/Frameworks/CFNetwork.framework/Versions/A/CFNetwork /System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices VLC.app/Contents/MacOS/lib/libvlccore.dylib
fi

>>>>>>> origin/3.0.x
if [ "$PACKAGETYPE" = "u" ]; then
    info "Copying app with debug symbols into VLC-debug.app and stripping"
    rm -rf VLC-debug.app
    cp -Rp VLC.app VLC-debug.app
<<<<<<< master

    # Workaround for breakpad symbol parsing:
    # Symbols must be uploaded for libvlc(core).dylib, not libvlc(core).x.dylib
    (cd VLC-debug.app/Contents/MacOS/lib/ && rm libvlccore.dylib && mv libvlccore.*.dylib libvlccore.dylib)
    (cd VLC-debug.app/Contents/MacOS/lib/ && rm libvlc.dylib && mv libvlc.*.dylib libvlc.dylib)

    find VLC.app/ -name "*.dylib" -exec strip -x {} \;
    find VLC.app/ -type f -name "VLC" -exec strip -x {} \;
    find VLC.app/ -type f -name "Sparkle" -exec strip -x {} \;
    find VLC.app/ -type f -name "Growl" -exec strip -x {} \;
    find VLC.app/ -type f -name "Breakpad" -exec strip -x {} \;

    if [ "$BUILD_TRIPLET" = "$HOST_TRIPLET" ]; then
        bin/vlc-cache-gen VLC.app/Contents/MacOS/plugins
    fi

    info "Building VLC release archive"
    make package-macosx-release
    make package-macosx-sdk

    shasum -a 512 vlc-*-release.zip
    shasum -a 512 vlc-macos-sdk-*.tar.gz

elif [ "$PACKAGETYPE" = "z" ]; then
    info "Packaging VLC zip archive"
    make package-macosx-zip
=======

    # Workaround for breakpad symbol parsing:
    # Symbols must be uploaded for libvlc(core).dylib, not libvlc(core).x.dylib
    (cd VLC-debug.app/Contents/MacOS/lib/ && rm libvlccore.dylib && mv libvlccore.*.dylib libvlccore.dylib)
    (cd VLC-debug.app/Contents/MacOS/lib/ && rm libvlc.dylib && mv libvlc.*.dylib libvlc.dylib)


    find VLC.app/ -name "*.dylib" -exec strip -x {} \;
    find VLC.app/ -type f -name "VLC" -exec strip -x {} \;
    find VLC.app/ -type f -name "Sparkle" -exec strip -x {} \;
    find VLC.app/ -type f -name "Growl" -exec strip -x {} \;
    find VLC.app/ -type f -name "Breakpad" -exec strip -x {} \;

if [ "$BUILD_TRIPLET" = "$HOST_TRIPLET" ]; then
    bin/vlc-cache-gen VLC.app/Contents/MacOS/plugins
fi

    info "Building VLC release archive"
    make package-macosx-release
    shasum -a 512 vlc-*-release.zip
>>>>>>> origin/3.0.x
elif [ "$PACKAGETYPE" = "n" -o "$PACKAGE" = "yes" ]; then
    info "Building VLC dmg package"
    make package-macosx
    make package-macosx-sdk
fi

if [ ! -z "$VLCBUILDDIR" ]; then
    popd
fi
