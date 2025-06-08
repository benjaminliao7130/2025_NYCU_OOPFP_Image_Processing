2025_NYCU_OOPFP_Image_Processing 影像處理專案

專案簡介
這個專案旨在探索如何在不大幅改變圖片視覺效果的前提下，將文字訊息隱藏於圖像之中，並能夠成功解碼還原。除了基本的加密解密功能，我們也鼓勵融入各種影像處理演算法，讓專案更加有趣且具挑戰性。

想像一下，您需要隱藏一段文字，除了將其背誦或藏匿於某處，還有什麼辦法？沒錯，就是透過加密！本專案結合了影像處理，將文字訊息加密嵌入圖片，如範例所示，即使圖片中隱藏了「I love OOP」字串，外觀也幾乎沒有變化，避免引起他人注意。當然，我們也能從加密後的圖片中解碼出原始字串。

除了核心功能，專案也鼓勵實作多種影像處理、文字加密演算法。演示時若能展示這些功能並詳述於結報中，將依內容豐富度與難度給予額外加分！

什麼是數位影像？
數位影像是電腦處理的視覺資訊表現形式，它與傳統類比影像不同，由離散的像素構成，每個像素包含特定的顏色和亮度資訊，這些像素的排列共同形成了影像的整體視覺內容。

例如：8 位元灰階影像

位元深度：「8 位元」指每個像素的位深度。在 8 位元的灰階影像中，每個像素有 2 
8
  (256) 種可能的值，範圍從 0 (黑色) 到 255 (白色)。
灰階（明暗程度）：與彩色影像不同，灰階影像包含各種灰色調。在 8 位元灰階影像中，每個像素代表不同的強度水平，其中 0 為黑色，255 為白色，中間為不同深淺的灰色調。
因此，在電腦圖形中表示灰階影像非常簡單：使用一個二維陣列，每個數值皆落在 0 到 255 的範圍。若是彩色圖片，則將其擴展為包含 RGB 三個通道的三維陣列即可。

專案設定與執行
本專案已預先設定好開發環境，讓您能快速開始。

1. 取得專案程式碼
請先登入 140.113.201.197 伺服器，然後使用 Git 複製專案：

Bash

# 登入伺服器 (若尚未登入)
$ ssh your_username@140.113.201.197

# 複製專案 (來自您的 GitHub repository)
$ git clone https://github.com/benjaminliao7130/2025_NYCU_OOPFP_Image_Processing.git
$ cd 2025_NYCU_OOPFP_Image_Processing/
2. 安裝第三方套件
專案依賴一些第三方函式庫來處理圖片 I/O。請執行 make install 來安裝這些必要的套件：

Bash

$ make install
這會自動執行 scripts/clone_env.sh 腳本，配置好編譯所需的環境。

3. 編譯專案
完成程式碼撰寫後（您可能會修改 inc/ 中的 .h 檔案、src/ 中的 .cpp 檔案以及 main.cpp），您可以使用 make 指令來編譯專案：

Bash

# 預設編譯
$ make

# 查看 make 實際執行了哪些指令 (除錯用)
$ make VERBOSE=1

# 平行編譯 (建議使用，可節省時間)
$ make -j
Makefile 會自動識別檔案的依賴關係，在您修改部分檔案後，只會重新編譯需要更新的部分，搭配平行編譯，能顯著提升開發效率。

4.創建資料夾
$ mkdir puzzle 
用於存放每一塊拼圖

5. 執行程式
編譯成功後，您可以執行 Image_Processing 可執行檔：

Bash

$ ./Image_Processing
程式操作介面說明 (UI 流程)
執行 ./Image_Processing 後，程式會引導您進行以下操作：

1. 選擇模式
===== Image System =====
Select mode:
1. Puzzle Game
2. Image Processor
Choice:
1. Puzzle Game：選擇此項將進入拼圖遊戲模式。
2. Image Processor：選擇此項將進入影像處理與加解密模式。
若選擇 1. Puzzle Game：
程式將直接進入拼圖遊戲的執行流程，您可以根據遊戲提示進行操作，拼圖會存放於puzzle資料夾中。

若選擇 2. Image Processor：
程式將進入影像處理功能，並開始引導您選擇圖片和操作。

2. 載入圖片
===== Image Processor =====
Enter image filename (in Image-Folder):
請輸入您要處理的圖片檔名（例如：lena.jpg）。請確保該圖片檔已放置在專案根目錄下的 Image-Folder/ 資料夾內。

3. 選擇圖片類型
Select image type:
1. Gray Image
2. RGB Image
Choice:
1. Gray Image：處理灰階圖片。
2. RGB Image：處理彩色圖片。
特殊情況處理：
如果您輸入的檔名包含 _enc 字樣（表示此圖片可能已被加密，例如：my_image_enc.png），並且您此時選擇了「Gray Image」，系統會提示：

This file seems to be encrypted. Gray Image cannot be decrypted.
Are you sure you want to choose Gray Image? (y/n):
這是因為灰階圖片通常不支援本專案的解密操作。此時，若您確認要繼續處理為灰階圖片，請輸入 y；否則輸入 n 將會讓您重新選擇圖片類型。

4. 選擇濾鏡 (Bit-field 操作)
Select filters to apply (bitfield, e.g., 3 = Flip + Mosaic):
0. Skip
1. Flip
2. Mosaic
4. Gaussian
8. Laplacian
16. Restore
Enter:
請輸入一個整數作為 bitfield 值，以啟用一個或多個濾鏡。每個濾鏡對應一個特定的位元值，您可以將它們的位元值相加來組合多重效果（例如輸入 3 代表同時啟用 Flip (1) 和 Mosaic (2)）。

濾鏡功能說明：

Flip (1)：水平翻轉圖片。
Mosaic (2)：對圖片區域打上馬賽克效果。
Gaussian (4)：應用高斯模糊濾鏡，通常用於圖片降噪。
Laplacian (8)：應用拉普拉斯銳化濾鏡，常用於增強圖片邊緣細節。
Restore (16)：此為還原濾鏡，您可以根據專案實作自行定義其具體功能（例如：逆向濾鏡、去噪等）。
加密圖片與濾鏡的交互提示：
如果載入的圖片檔名包含 _enc 且您選擇了任何濾鏡（即 bitfield > 0），系統會提示：

This file seems to be encrypted. Applying filters may destroy the hidden message.
Are you sure you want to apply bitfield value [bitfield]? (y/n):
此提示旨在提醒您，濾鏡操作可能會破壞隱藏在圖片中的訊息。若您確認要繼續應用濾鏡，請輸入 y；否則輸入 n 將取消濾鏡應用。

5. 圖片加解密操作 (僅限 RGB 圖片)
此步驟僅在您選擇了 RGB Image 且在步驟 4 中未選擇任何濾鏡 (bitfield == 0) 時才會觸發。

5.1. 解密已加密圖片
如果載入的圖片檔名包含 _enc 字樣，程式會詢問：

This file seems to be encrypted. Do you want to attempt decryption? (y/n):
輸入 y 將嘗試解密。解密結果（原始訊息）會直接顯示在終端機上。若解密成功，程式會跳過後續的儲存步驟。若解密失敗，會提示相應的錯誤訊息。

5.2. 加密新訊息
如果載入的圖片檔名不包含 _enc 字樣，且 bitfield == 0，程式會詢問：

Encrypt a message? (y/n):
輸入 y 後，程式會提示您輸入要加密的訊息（請注意訊息長度限制 &lt; 100 字元）：

Enter message (length < 100):
若加密成功，程式會將圖片內部標記為已加密狀態，並在後續的儲存步驟中將輸出檔名自動改為 _enc 結尾。若加密失敗（例如訊息過長），會提示錯誤並詢問您是否要重試。

6. 濾鏡應用與結果預覽
根據您在步驟 4 中選擇的 bitfield 值，程式會對圖片應用相應的濾鏡效果。
在圖片儲存之前，您可以選擇預覽處理後的結果：

View result before saving?
0. Skip
1. Show by XServer
2. Show by ASCII
Choice:
0. Skip：不進行預覽。
1. Show by XServer：使用 X Server 顯示圖片。請確保您的本機環境（如 MobaXterm 等）已正確配置 X Server，否則可能無法正常顯示。重要提示：在進行記憶體檢查 (valgrind) 時，請務必避免使用此功能，以避免產生誤報。
2. Show by ASCII：在終端機中以 ASCII 字符藝術形式顯示圖片的簡略預覽。
7. 儲存圖片
Save result? (y/n):
輸入 y 將會把處理後的圖片儲存到 Image-Folder/ 資料夾中。輸出檔名會根據您執行的操作自動加上後綴（例如：lena_rgb_flip_enc.png）。如果圖片經過加密，最終會儲存為 .png 格式；否則，會儲存為 .jpg 格式。

專案結構
Bash

# 在專案根目錄執行 'tree -L 2' 可查看
.
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
說明：
我們將 class 的頭文件介面定義在 inc/ 資料夾內部，並將其原始碼實作放在 src/ 資料夾內部。Makefile 會自動識別文件間的依賴關係，當您修改部分檔案後，make 指令將只會重新編譯需要更新的部分，搭配 -j 參數進行平行編譯，能讓您在開發上節省不少時間。