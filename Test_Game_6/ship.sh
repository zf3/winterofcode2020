if ! codesign --force --deep --sign "Apple Development: fengzhou@gmail.com (J9GF8BDE5Y)" build/Triangle_Dodge.app; then
	echo "codesign failed"
	exit 1
fi
if ! codesign --force --deep --sign "Apple Development: fengzhou@gmail.com (J9GF8BDE5Y)" build/Triangle_Dodge.dmg; then
	echo "codesign failed"
	exit 1
fi
cd build
ditto -c -k --sequesterRsrc --keepParent Triangle_Dodge.app Triangle_Dodge.zip
scp Triangle_Dodge.zip Triangle_Dodge.dmg 192.168.1.200:/var/www/html/tmp

