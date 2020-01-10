{
    "targets": [
        {
            "target_name": "<(module_name)",
            "sources": [
                "src/wx.cpp",
                "src/misc.cpp",
                "src/widgets/wxApp.cpp",
                "src/widgets/wxFrame.cpp",
                "src/widgets/wxPanel.cpp",
                "src/widgets/wxButton.cpp",
                "src/utils/unwrapper.cpp",
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
                "_UNICODE",
                "UNICODE"
            ],
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1}
            },
            'msbuild_settings': {
                'Link': {
                    'AdditionalLibraryDirectories': [
                        '../deps/3.1.3/win32/lib/vc14x_x64_dll'
                    ],
                },
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
                        'deps/3.1.3/win32/include/msvc',
                        'deps/3.1.3/win32/include'
                    ],
                    "defines": [
                        "WXUSINGDLL",
                        "wxMSVC_VERSION_AUTO",
                        "wxMSVC_VERSION_ABI_COMPAT"
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
                                "deps/3.1.3/win32/vccorlib140.dll",
                                "deps/3.1.3/win32/msvcp140.dll",
                                "deps/3.1.3/win32/vcruntime140.dll",

                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313ud_net_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313ud_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313ud_xml_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313u_net_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313u_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxbase313u_xml_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_adv_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_aui_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_core_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_adv_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_aui_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_core_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_gl_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_html_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_media_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_propgrid_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_qa_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_ribbon_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_richtext_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_stc_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_webview_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313ud_xrc_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_gl_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_html_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_media_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_propgrid_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_qa_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_ribbon_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_richtext_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_stc_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_webview_vc14x_x64.dll",
                                "deps/3.1.3/win32/lib/vc14x_x64_dll/wxmsw313u_xrc_vc14x_x64.dll",
                            ],
                            "destination": "<(module_path)"
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
