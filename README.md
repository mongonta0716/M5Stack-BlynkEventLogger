# M5Stack-BlynkEventLogger

Blynkと連携し、スマホでボタンを押すとイベント名と日時を記録するロガーです。
SDカード上にCSVファイルを作成します。

# 使い方(Usage)
生成したbinファイルはSD-Updater対応です。（LovyanLauncherで使用可能）

## スマホ側で設定
Blynkアプリをインストールしてください。
VとはVirtual PINのことです。
ボタン３つ（V3、V4、V5）とLCDを２個（AdvancedでV1,V2PINを設定）で画面を作ります。(作成方法は[Blynk.io](https://blynk.io/)を見てください。)


## ソースの変更
自身の環境に合わせてソースを変更する必要があります。
### 通信に必要な情報
* Blynkアプリでプロジェクトを作成した際のAuth token
* SSID
* WiFi Password
```
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "XXXXXXXXXXXXXXXXXXXX";
char pass[] = "XXXXXXXXXXXXXXXXXXXX";
```

### イベント名の設定
ボタンを押した際に、CSVに記録するイベント名を設定します。
```
// { V3 pin, V4 pin, V5 pin }'s eventName
char *eventName[] = { "event1", "event2", "event3" };
```
## コンパイルして書き込み
ArduinoIDEでコンパイルしてM5Stackへ書き込みます。
binファイルを作成してLovyanLauncherから呼び出すことも可能です。

# Requirement

コンパイルする場合は、以下のライブラリが必要です。
* [M5Stack](https://github.com/m5stack/M5Stack)
* [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater)
* [Blynk](https://github.com/blynkkk/blynk-library)


# Licence
[MIT](https://github.com/mongonta0716/M5Stack-BlynkEventLogger/blob/master/LICENSE)

# Author
[Takao Akaki](https://twitter.com/mongonta555)
