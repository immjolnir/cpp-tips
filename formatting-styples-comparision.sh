#!/bin/bash -x

styles=( LLVM Google Chromium Mozilla WebKit )
for style in ${styles[@]};
do
  # generate default styles
  clang-format -style=$style -dump-config > $style.clang-format

  # Apply the code style on a file
  # clang-format -style=$style a.h > formatted.a.h
done
