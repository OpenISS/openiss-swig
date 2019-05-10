install_name_tool -change libOpenNI2.dylib @loader_path/./libOpenNI2.dylib libNiTE2.dylib

install_name_tool -change libFreenectDriver.0.6.0.dylib @loader_path/./libFreenectDriver.0.6.0.dylib libFreenectDriver.0.6.0.dylib

install_name_tool -change libNiTE2.dylib @loader_path/./osx/libNiTE2.dylib liboigesturecxx.dylib

install_name_tool -change libOpenNI2.dylib @loader_path/./osx/libOpenNI2.dylib liboigesturecxx.dylib

install_name_tool -change libNiTE2.dylib @loader_path/./osx/libNiTE2.dylib liboigesture.jnilib

install_name_tool -change libOpenNI2.dylib @loader_path/./osx/libOpenNI2.dylib liboigesture.jnilib

install_name_tool -change @rpath/liboigesturecxx.dylib @loader_path/./liboigesturecxx.dylib liboigesture.jnilib
