{
    "targets": [
        {
            "target_name": "<(module_name)",
            "sources": [
                "src/wx.cpp",
                "src/widgets/wxApp.cpp",
                "src/widgets/wxFrame.cpp",
            ],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7"
            },
            "defines": [
                "NAPI_VERSION=<(napi_build_version)",
            ],
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1}
            },
            "conditions": [
                [
                    "OS==\"mac\"",
                    {
                        "cflags+": ["-fvisibility=hidden"],
                        "xcode_settings": {
                            "GCC_SYMBOLS_PRIVATE_EXTERN": "YES"
                        },
                        'include_dirs': [
                            'deps/5.12.3/darwin/include',
                            'deps/5.12.3/darwin/include/QtCore',
                            'deps/5.12.3/darwin/include/QtGui',
                            'deps/5.12.3/darwin/include/QtWidgets'
                        ],
                        'libraries': [
                            '../deps/5.12.3/darwin/lib/QtCore.framework/QtCore',
                            '../deps/5.12.3/darwin/lib/QtGui.framework/QtGui',
                            '../deps/5.12.3/darwin/lib/QtWidgets.framework/QtWidgets',
                        ]
                    }
                ],
                [
                    "OS==\"linux\"",
                    {
                        "sources": [
                        ],
                        "cflags": ["<!@(wx-config --cxxflags)"],
                        "ldflags": [
                            "<!@(wx-config --libs)"
                        ],
                        # check if right
                        "libraries": ["<!@(wx-config --libs)"],
                    }
                ],
                ['OS=="win"', {
                    'include_dirs': [
                        'deps/5.12.3/win32/include',
                        'deps/5.12.3/win32/include/QtCore',
                        'deps/5.12.3/win32/include/QtGui',
                        'deps/5.12.3/win32/include/QtWidgets',
                    ],
                    'libraries': [
                        # TODO: fix node-gyp behavior that requires ../
                        '../deps/5.12.3/win32/lib/Qt5Core.lib',
                        '../deps/5.12.3/win32/lib/Qt5Gui.lib',
                        '../deps/5.12.3/win32/lib/Qt5Widgets.lib',
                    ]
                }]
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": ["<(module_name)"],
            "copies": [
                {
                    "files": ["<(PRODUCT_DIR)/<(module_name).node"],
                    "destination": "<(module_path)"
                }
            ],
            'conditions': [
                ['OS == "win"', {
                    "copies": [
                        {
                            "files": [
                                "deps/5.12.3/win32/Qt5Core.dll",
                                "deps/5.12.3/win32/Qt5Gui.dll",
                                "deps/5.12.3/win32/Qt5Widgets.dll",
                                "deps/5.12.3/win32/vccorlib140.dll",
                                "deps/5.12.3/win32/msvcp140.dll",
                                "deps/5.12.3/win32/vcruntime140.dll"
                            ],
                            "destination": "<(module_path)"
                        },
                        {
                            "files": [
                                "deps/5.12.3/win32/platforms/qwindows.dll"
                            ],
                            "destination": "<(module_path)/platforms/"
                        }
                    ]
                }
                ],
                ['OS == "mac"', {
                    "copies": [
                        {
                            "files": [
                                "deps/5.12.3/darwin/lib",
                                "deps/5.12.3/darwin/platforms"
                            ],
                            "destination": "<(module_path)"
                        }
                    ]
                }]
            ]
        }
    ]
}
