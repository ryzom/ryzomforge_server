#!/bin/bash
# ______                           _____ _                   _   _____           _
# | ___ \                         /  ___| |                 | | |_   _|         | |
# | |_/ /   _ _______  _ __ ___   \ `--.| |__   __ _ _ __ __| |   | | ___   ___ | |___
# |    / | | |_  / _ \| '_ ` _ \   `--. \ '_ \ / _` | '__/ _` |   | |/ _ \ / _ \| / __|
# | |\ \ |_| |/ / (_) | | | | | | /\__/ / | | | (_| | | | (_| |   | | (_) | (_) | \__ \
# \_| \_\__, /___\___/|_| |_| |_| \____/|_| |_|\__,_|_|  \__,_|   \_/\___/ \___/|_|___/
#        __/ |
#       |___/
#
# Ryzom - MMORPG Framework <https://ryzom.com/dev/>
# Copyright (C) 2019  Winch Gate Property Limited
# This program is free software: read https://ryzom.com/dev/copying.html for more details
#
# Script to build Rocketchat with ryzombridge
#

VERSION="1.0.0-rc.0"
BUILD_PATH=~/builds

echo "INSTALLATION OF VERSION $VERSION !!!!"

echo "If you don't have install all requirements check at:"
echo "https://rocket.chat/docs/installation/manual-installation/ubuntu/"
echo "To install meteor : curl https://install.meteor.com/ | sh"
echo "Ctrl+c to abort..."
read

echo "Erasing old..."
rm -rf $BUILD_PATH/RocketChat/Rocket.Chat.old

mv Rocket.Chat Rocket.Chat.old

cd ~/builds/RocketChat/
if [[ ! -d "megacorp" ]]
	echo "Missing megacorp. Cloning it.."
	hg clone ssh://hg@bitbucket.org/ryzom/megacorp
fi

cd megacorp
hg pull
hg update -v
cd ..

git clone https://github.com/RocketChat/Rocket.Chat.git

cd Rocket.Chat
git checkout $VERSION

cp $BUILD_PATH/RocketChat/megacorp/ryzom-rocket-bridge/ packages/
echo -e "\nryzom-rocket-bridge" >> .meteor/packages

npm install --production

rm -rf ../rc-bundle
meteor build ../rc-bundle --architecture os.linux.x86_64
meteor build ../rc-bundle --architecture os.linux.x86_64

cd ../rc-bundle
tar xvfz Rocket.Chat.tar.gz

cd ~
mv Rocket.Chat/ Rocket.Chat.old
cp -r src/rc-bundle/bundle/ Rocket.Chat/

cd ~/Rocket.Chat/programs/server
npm install

