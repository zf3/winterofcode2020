if ! codesign --force --deep --sign "Apple Development: fengzhou@gmail.com (J9GF8BDE5Y)" build/Test_Game_6.app; then
	echo "codesign failed"
	exit 1
fi
cd build
zip -r Test_Game_6.zip Test_Game_6.app
scp Test_Game_6.zip 192.168.1.200:/var/www/html/tmp

