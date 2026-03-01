# windowskill

這是我大二時使用 C++ 撰寫的遊戲專案，靈感來自當時知名的 steam 小遊戲[《windowskill》](https://store.steampowered.com/app/2726450/Windowkill/)。在傳統的射擊、打怪、與升級要素之外，本專案實作了一個核心機制：**遊戲邊界會持續縮小**。玩家必須透過擊打牆壁來擴張生存空間與走位範圍，為射擊遊戲增添了獨特的空間管理挑戰。

---------

## 🏗️ 專案架構 (Project Architecture)

本專案採用 **物件導向程式設計 (OOP)** 進行模組化開發，確保各個系統之間的權責分明：

### 1. 核心實體 (Core Entities)
- **`Player`**: 封裝玩家狀態（血量、經驗、技能）與移動邏輯。
- **`Enemy` & `EnemyManager`**: 藉由 `EnemyManager` 統一管理敵人的生成、行為模式更新（AI）與渲染，並包含進階的 `EliteEnemy` 變體。
- **`Bullet`**: 實作彈幕邏輯，支持多種類型的子彈路徑與效果。

### 2. 系統管理 (Systems Management)
- **`CollisionManager`**: 核心碰撞偵測引擎，處理子彈與敵人、玩家與敵人、以及玩家與視窗邊界之間的物理互動。
- **`Window` 與 `ShowWindow`**: 管理多視窗狀態與渲染流程，包含主遊戲畫面、技能樹、暫停選單及遊戲結束畫面。
- **`LTexture` & `LTimer`**: 封裝 SDL2 的底層繪圖與計時功能，提供更直覺的 API 進行資源管理與幀率控制。

### 3. 多視窗驅動機制 (Multi-Window UI)
- 遊戲中的不同狀態（如技能升級、暫停設定）並非單純的疊層，而是透過多視窗切換與焦點管理來達成，模擬作業系統視窗操作的體感。

---

## 🚀 技術能力 (Technical Capabilities)

### 1. 動態視窗邊界互動
- 實作了「視窗邊界縮減」演算法，並與碰撞系統整合。玩家的攻擊會對座標空間產生動態影響，這需要精確的坐標轉換與物理邊界判定。

### 2. 技能升級系統
- 內建完整的技能樹（Skill Tree）邏輯，包含：
  - **數值增益**: 跑速提升（speedUp）、掉錢率增加（wealth++）、射速增加（fireRate）、最大血量（maxHP）。
  - **特殊能力**: 凍結敵方（freeze）、子彈彈跳（bounce）、多重射擊（multiShot）。
- 實作了基於金幣（Coin）的經濟體系與升級冷卻機制。

### 3. 多媒體與資源優化
- **圖形渲染**: 使用 SDL2 實作 Alpha Blending 與紋理映射，支援 PNG 透明背景。
- **音效系統**: 透過 SDL_mixer 實作背景音樂（BGM）與多軌道音效播放，並具備即時音量切換功能。
- **文字渲染**: 整合 SDL_ttf 處理動態數值與 UI 文字呈現。

### 4. 難度曲線設計
- 程式內建 7 個難度等級（Grades），隨遊戲時間自動調整敵人強度與生成頻率，確保遊戲體驗具備挑戰性。

---

## 🛠️ 技術棧 (Tech Stack)

- **語言**: C++11/17
- **底層庫**: [SDL2](https://www.libsdl.org/) (Core, Image, Mixer, TTF)
- **其他**: SDL_bgi (圖形處理輔助)
- **開發平台**: Windows (Dev-C++ / MingW), 支援 macOS 編譯 (進行中)

---

## � 執行與部署 (Installation & Execution)

### Windows (現已支援)
1. **下載專案**: 請確保下載所有檔案，包含 `final.exe`、所有核心 `.dll` 檔案，以及 `img/` 和 `sound/` 資產資料夾（缺一不可）。
2. **直接執行**: 在資料夾內雙擊 `final.exe` 即可直接開始遊戲。
3. **編譯開發**: 專案原始碼支援使用 Dev-C++ (TDM-GCC) 環境開啟 `final.dev` 進行重新編譯。

### macOS (施工中 🚧)
- **目前狀態**: 尚未支援。
- 由於開發初期使用了較多 Windows 特有的函式庫與編譯設定，目前正在針對 macOS 進行 SDL2 環境的適配與跨平台改寫，完成後將會更新編譯指南。

---

## �🔗 相關連結

- [YouTube 影片介紹](https://youtu.be/5KqB1U-Wxk0)
- [設計藍圖 (PDF)](https://drive.google.com/file/d/1eI-FP6_iqsu2RvfaDJvw7OnXkyP9XYPv/view?usp=sharing)
- [原始遊戲 Steam 連結](https://store.steampowered.com/app/2726450/Windowkill/)