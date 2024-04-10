#!/bin/sh

OPTIONS="
      --enable-update-check
      --enable-lua
      --enable-flac
      --enable-theora
      --enable-avcodec --enable-merge-ffmpeg
      --enable-dca
      --enable-libass
      --enable-schroedinger
      --enable-live555
      --enable-shout
      --enable-goom
<<<<<<< master
      --enable-sse
=======
      --enable-sse --enable-mmx
>>>>>>> origin/3.0.x
      --enable-libcddb
      --enable-zvbi --disable-telx
      --enable-nls"

sh "$(dirname $0)"/../../../configure ${OPTIONS}  "$@"
