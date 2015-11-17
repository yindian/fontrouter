You may experience some errors when building against standard SDKs for the first time. This is because FontRouter use a few treaked header files.

For errors indicating access violence, you need to add corresponding FontRouter classes to the class declaration in SDK header as friend classes. This will get all the private/protected members accessable to FontRouter classes.

If you experience loading problem (FontRouter.dll is not loaded) in emulator, please try clean ECom cache first, just remove all files in folder Epoc32\winscw\c\private\10009D8F.