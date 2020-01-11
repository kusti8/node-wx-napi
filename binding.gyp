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
                        "xcode_settings": { # Mac doesn't like cflags
                            "GCC_SYMBOLS_PRIVATE_EXTERN": "YES",
                            "OTHER_CFLAGS": [
                                "-I../deps/3.1.3/darwin/lib/wx/include/osx_cocoa-unicode-3.1",
                                "-I../deps/3.1.3/darwin/include",
                                "-D_FILE_OFFSET_BITS=64",
                                "-DWXUSINGDLL",
                                "-D__WXMAC__",
                                "-D__WXOSX__",
                                "-D__WXOSX_COCOA__"
                            ]
                        },
                        'ldflags': [
                            '-L../deps/3.1.3/darwin/lib',
                            '-framework IOKit',
                            '-framework Carbon',
                            '-framework Cocoa',
                            '-framework AudioToolbox',
                            '-framework System',
                            '-framework OpenGL',
                            '-lwx_osx_cocoau_xrc-3.1',
                            '-lwx_osx_cocoau_html-3.1',
                            '-lwx_osx_cocoau_qa-3.1',
                            '-lwx_osx_cocoau_core-3.1',
                            '-lwx_baseu_xml-3.1',
                            '-lwx_baseu_net-3.1',
                            '-lwx_baseu-3.1'
                        ],
                        'libraries': [
                            '-L../deps/3.1.3/darwin/lib',
                            '-framework IOKit',
                            '-framework Carbon',
                            '-framework Cocoa',
                            '-framework AudioToolbox',
                            '-framework System',
                            '-framework OpenGL',
                            '-lwx_osx_cocoau_xrc-3.1',
                            '-lwx_osx_cocoau_html-3.1',
                            '-lwx_osx_cocoau_qa-3.1',
                            '-lwx_osx_cocoau_core-3.1',
                            '-lwx_baseu_xml-3.1',
                            '-lwx_baseu_net-3.1',
                            '-lwx_baseu-3.1'
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
                                "deps/3.1.3/darwin/lib",
                            ],
                            "destination": "<(module_path)"
                        }
                    ]
                }]
            ]
        }
    ]
}
