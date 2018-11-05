#!/bin/bash

echo "Copying ./SFML-2.5.0-macOS-clang/Frameworks/. => /Library/Frameworks/"
sudo cp -a ./SFML-2.5.0-macOS-clang/Frameworks/. /Library/Frameworks/

echo "Copying ./SFML-2.5.0-macOS-clang/lib/. => /usr/local/lib/"
sudo cp -a ./SFML-2.5.0-macOS-clang/lib/. /usr/local/lib/

echo "Copying ./SFML-2.5.0-macOS-clang/include/. => /usr/local/include/"
sudo cp -a ./SFML-2.5.0-macOS-clang/include/. /usr/local/include/

echo "Copying ./SFML-2.5.0-macOS-clang/extlibs/. => /Library/Frameworks"
sudo cp -a ./SFML-2.5.0-macOS-clang/extlibs/. /Library/Frameworks/