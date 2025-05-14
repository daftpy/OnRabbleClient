# WindeployQt

windeployQt is a Qt deployment tool which bundles the related project 
.dll files into the build/release folder.

It should be important to note it could copy unecessary .dll files 
without proper configuration. My examples do not apply these 
configurations and as a result some of the .dll files can be deleted.

## Example

After building the project, navigate to the specific kit's build 
folder inside the build/ directory. For example, this might be:

`build/Desktop_Qt_6_9_0_MSVC2022_64bit-Release`

Then follow these steps:

1. Create a new subdirectory called `RC1`
2. Copy the executable to `RC1`
3. Run the following command
  
`windeployqt --qmldir ../../ ./RC2 --release`

You should see all of the necessary .dll files copied to the `RC2`
folder which is ready for distribution.

**Note**: windeployqt is th deploy tool, `--qmldir` points to where 
the QML lives, `./RC2` is the directory with the executable to scan, 
and `--release` tells the tool the executable executable is the 
release build.

## Release Size

The release build currently stands at about ~334mb. This is primarily
from the inclusion of the QtWebEngine, which powers the WebEngineView
in the AuthBrowserPage. This choice was made to integrate the 
authentication flow inside the application instead of delegating it 
through a web browser.

## Contribution
Anyone who is able to reduce the size of this release by a substantial
degree is free to reach out through:

https://github.com/daftpy/OnRabbleClient
