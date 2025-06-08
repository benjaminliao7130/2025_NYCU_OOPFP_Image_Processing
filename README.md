# 2025_NYCU_OOPFP_Image_Processing 影像處理專案

## 📌 專案簡介
本專案旨在探索如何在**不明顯改變圖片外觀**的前提下，將**文字訊息加密藏入圖像中**並能成功還原。  
除了基本的加密/解密功能，也鼓勵加入各種影像處理濾鏡，提升專案的趣味性與挑戰性。

範例：將 "I love OOP" 藏入圖片中，但外觀幾乎沒有變化。

---

## 🖼️ 什麼是數位影像？

### 灰階影像（8 位元）
- 每個像素使用 8 位元（0 ~ 255，黑至白）
- 可用二維陣列儲存灰階影像  
- 彩色圖片則為三維陣列（RGB 三通道）

---

## 🚀 開始使用

### 1️⃣ 登入伺服器並複製專案

ssh your_username@140.113.201.197

git clone https://github.com/benjaminliao7130/2025_NYCU_OOPFP_Image_Processing.git

cd 2025_NYCU_OOPFP_Image_Processing-main/

2️⃣ 安裝依賴套件
bash
複製
編輯
make install

3️⃣ 編譯專案
bash
複製
編輯
make           # 一般編譯
make -j        # 平行編譯（建議）
make VERBOSE=1 # 顯示詳細指令（除錯用）

4️⃣ 建立拼圖儲存資料夾（Puzzle 模式使用）
bash
複製
編輯
mkdir puzzle

5️⃣ 執行程式
bash
複製
編輯
./Image_Processing
## 🧩 程式操作流程
### 📍 選擇模式
mathematica
複製
編輯
===== Image System =====
Select mode:
1. Puzzle Game
2. Image Processor
1. Puzzle Game：進入拼圖遊戲，拼圖會輸出到 puzzle/ 資料夾中

2. Image Processor：進入影像處理與加解密模式

### 📂 載入圖片
請輸入圖片檔名（需放在 Image-Folder/ 目錄中），例如：

mathematica
複製
編輯
Enter image filename (in Image-Folder): lena.jpg
### 🎨 選擇圖片類型
mathematica
複製
編輯
1. Gray Image
2. RGB Image
### ⚠️ 若圖片檔名包含 _enc 且選擇 Gray Image，會提示：
This file seems to be encrypted. Gray Image cannot be decrypted.

### 🧪 濾鏡選擇（bitfield）
markdown
複製
編輯
Select filters to apply (bitfield, e.g., 3 = Flip + Mosaic):
0. Skip
1. Flip
2. Mosaic
4. Gaussian
8. Laplacian
16. Restore
可以輸入整數組合多個濾鏡（例如輸入 3 → 套用 Flip + Mosaic）

整數值	濾鏡功能
1	水平翻轉 (Flip)
2	馬賽克 (Mosaic)
4	模糊 (Gaussian)
8	銳化 (Laplacian)
16	還原 (Restore)

### ⚠️ 若圖片含 _enc 且選擇濾鏡，系統會警告：
Applying filters may destroy the hidden message.

### 🔐 加解密功能（僅 RGB 圖片，且未套用濾鏡）
1️⃣ 解密已加密圖片
pgsql
複製
編輯
This file seems to be encrypted. Do you want to attempt decryption? (y/n):
成功：直接輸出訊息至終端機

失敗：顯示錯誤並跳出

2️⃣ 加密新訊息
mathematica
複製
編輯
Encrypt a message? (y/n):
Enter message (length < 100):
成功：將圖檔改名為 _enc 結尾後輸出

失敗：顯示錯誤並提示是否重新輸入

### 👀 預覽處理後圖片
pgsql
複製
編輯
View result before saving?
0. Skip
1. Show by XServer
2. Show by ASCII
0：略過預覽

1：使用 X Server 顯示圖片（需本地配置）

2：以 ASCII 在 terminal 中輸出圖形

### ⚠️ 使用 valgrind 記憶體檢查時請勿選擇 XServer 預覽，否則會產生誤報。

### 💾 儲存圖片
bash
複製
編輯
Save result? (y/n):
若圖片為加密 → 儲存為 .png

若未加密 → 儲存為 .jpg

檔名會自動加上後綴，如 _flip, _enc 等

### ✅ 小提醒
所有圖片檔請放置於 Image-Folder/ 資料夾

拼圖會儲存在 puzzle/ 資料夾中

預設使用 PNG 格式儲存加密圖，JPG 格式儲存一般圖
專案結構
Bash

### 在專案根目錄執行 'tree -L 2' 可查看
<pre> ``` 
├── Data-Loader            # 處理圖片 I/O 相關功能
│   ├── data_loader.cpp
│   └── data_loader.h
├── data_loader_demo.cpp   # 示範如何使用 data_loader (Step 1)
├── Image-Folder           # 預設存放圖片的資料夾，您的圖片應放置於此
│   ├── 1-1.jpg
│   ├── ...
│   └── truck.png
├── puzzle                 # 變成拼圖的圖片會存放於此
├── inc                    # 存放所有頭文件 (.h)
│   ├── bit_field_filter.h
│   ├── gray_image.h
│   ├── image_encryption.h
│   ├── image.h
│   ├── image_restore.h    # 新增的圖片還原濾鏡頭文件
│   ├── puzzle_game.h      # 新增的拼圖遊戲頭文件
│   └── rgb_image.h
├── LICENSE
├── main.cpp               # 專案主程式 (Driven code)
├── Makefile               # 自動化編譯流程設定
├── README.md              # 本說明文件
├── scripts
│   └── clone_env.sh       # 環境設置腳本，由 make install 呼叫
├── src                    # 存放所有實作檔案 (.cpp)
│   ├── bit_field_filter.cpp
│   ├── gray_image.cpp
│   ├── image.cpp
│   ├── image_encryption.cpp
│   ├── image_restore.cpp  # 新增的圖片還原濾鏡實作
│   ├── puzzle_game.cpp    # 新增的拼圖遊戲實作
│   └── rgb_image.cpp
└── third-party            # 第三方開源圖片處理函式庫
    ├── catimg
    ├── CImg
    └── libjpeg
``` </pre>
說明：
我們將 class 的頭文件介面定義在 inc/ 資料夾內部，並將其原始碼實作放在 src/ 資料夾內部。Makefile 會自動識別文件間的依賴關係，當您修改部分檔案後，make 指令將只會重新編譯需要更新的部分，搭配 -j 參數進行平行編譯，能讓您在開發上節省不少時間。
