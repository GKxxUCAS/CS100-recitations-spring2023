## settings.json:

```json
{
    "code-runner.executorMap": {
        "cpp": "cd $dir && g++ '$fileName' -o '$fileNameWithoutExt' -std=c++17 -Wall -Wpedantic -Wextra && echo 'compilation ends.' && ./'$fileNameWithoutExt'",
        "c": "cd $dir && gcc '$fileName' -o '$fileNameWithoutExt' -std=c17 -Wall -Wpedantic -Wextra && echo 'compilation ends.' && ./'$fileNameWithoutExt'"
    }
}
```

## c_cpp_properties.json: （用于配置"C/C++"插件）

### Windows:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "compilerPath": "C:\\mingw64\\bin\\gcc.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64",
            "compilerArgs": [
                "-Wall",
                "-Wpedantic",
                "-Wextra"
            ]
        }
    ],
    "version": 4
}
```

### Mac:

```json
{
    "configurations": [
        {
            "name": "Mac",
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-x64",
            "compilerArgs": [
                "-Wall",
                "-Wpedantic",
                "-Wextra"
            ]
        }
    ],
    "version": 4
}
```

注意事项：
* `code-runner.executorMap` 中的指令就是编译的时候在终端输入的指令，其中的编译选项可以根据需要自行调整。
* 建议始终将 `code-runner.executorMap` 中的语言标准与 `c_cpp_properties.json` 里的 `cStandard` 和 `cppStandard` 保持一致。
* 建议始终将 `code-runner.executorMap` 中的编译选项与 `c_cpp_properties.json` 里的 `compilerArgs` 保持一致。
* `c_cpp_properties.json` 里的 `compilerPath` 需要设置为编译器所在的位置。