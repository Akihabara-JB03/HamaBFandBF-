# HamaBF

拡張Brainfuckインタプリタ **HamaBF** です。

標準Brainfuckに加えて、いくつかの拡張命令を追加した実装になっています。

## Features

* Brainfuck実行エンジン
* デバッグモード対応
* メモリ状態表示
* 拡張命令対応
* 軽量なC実装

## Build

```Powershell
gcc main.c jmp.c -o brainfuck
```

## Usage

```Powershell
./brainfuck <file.bf> -nodebug
```

デバッグモード：

```Powershell
./brainfuck <file.bf> -debug
```

## Extended Commands

HamaBFでは、以下の追加命令が使えます。

|Command|Description|
|-|-|
|`$`|ポインタをセル0へ移動|
|`/`|現在のセルを0にする|
|`^`|現在のセルを2倍にする|
|`#`|現在のセルが1なら終了|
|`\\`|プログラムを終了|

## Example

### Output A

```brainfuck
+^^^^^^+.
```

実行結果：

```
A
```

解説：

```
1 → 2 → 4 → 8 → 16 → 32 → 64 → 65
```

ASCIIコード65を作成して出力します。

## Cell Size

デフォルトでは16bitセルを使用します。
**ASCIIは、もう関係ないのかな...**
## License

This project is licensed under the GNU General Public License v3.0.

## Author

Akihabara-JB03

