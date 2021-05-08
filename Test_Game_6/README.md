
Code signing:
```
codesign --force --deep --sign "Apple Development: fengzhou@gmail.com (J9GF8BDE5Y)" build/Test_Game_6.app
codesign -dv build/Test_Game_6.app
```

Verify access control
```
spctl -a -vvvv build/Test_Game_6.app
```

Notorization:

