if ! codesign --force --deep --sign "Apple Development: fengzhou@gmail.com (J9GF8BDE5Y)" build/Triangle_Dodge.app; then
	echo "codesign failed"
	exit 1
fi
cd build
zip -r Triangle_Dodge.zip Triangle_Dodge.app
scp Triangle_Dodge.zip 192.168.1.200:/var/www/html/tmp

