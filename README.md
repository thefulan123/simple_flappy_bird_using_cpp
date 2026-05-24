# Flappy Bird C++ — Game Programming dengan C++ & SDL2

[![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![SDL2](https://img.shields.io/badge/SDL2-2.0-green.svg)](https://www.libsdl.org/)
[![Build](https://img.shields.io/badge/Build-passing-brightgreen.svg)]()
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)]()

> **Sebuah proyek pembelajaran pemrograman game menggunakan C++ dan SDL2.**
> Cocok untuk pemula yang ingin memahami konsep *game development*, *game loop*, *collision detection*, dan *state machine*.

---

## 📚 Daftar Isi

- [Tentang Proyek Ini](#tentang-proyek-ini)
- [Apa yang Akan Kamu Pelajari](#apa-yang-akan-kamu-pelajari)
- [Prasyarat](#prasyarat)
- [Instalasi SDL2](#instalasi-sdl2)
- [Cara Build & Menjalankan](#cara-build--menjalankan)
- [Cara Bermain](#cara-bermain)
- [Struktur Proyek](#struktur-proyek)
- [Penjelasan Kode Mendalam](#penjelasan-kode-mendalam)
  - [`config.h` — Pusat Konfigurasi Game](#configh--pusat-konfigurasi-game)
  - [`bird.h` / `bird.cpp` — Fisika Burung](#birdh--birdcpp--fisika-burung)
  - [`pipe.h` / `pipe.cpp` — Sistem Pipa & Score](#pipeh--pipecpp--sistem-pipa--score)
  - [`game.h` / `game.cpp` — Game State Machine](#gameh--gamecpp--game-state-machine)
  - [`main.cpp` — Entry Point](#maincpp--entry-point)
- [Alur Eksekusi Program](#alur-eksekusi-program)
- [Kustomisasi Game](#kustomisasi-game)
- [Latihan untuk Kamu](#latihan-untuk-kamu)
- [Lisensi](#lisensi)

---

## 🎯 Tentang Proyek Ini

Proyek ini adalah implementasi **Flappy Bird** — game klasik mobile yang viral — ditulis ulang dalam **C++** menggunakan library **SDL2** untuk grafis dan input.

Tujuan proyek ini **bukan** sekadar membuat game yang bisa dimainkan, melainkan menjadi **media belajar** yang terstruktur. Setiap baris kode ditulis dengan sengaja untuk mengajarkan konsep fundamental dalam pemrograman game:

| Konsep | Implementasi |
|--------|-------------|
| **Game Loop** | Loop `while(running)` dengan fixed timestep |
| **State Machine** | `MENU → PLAYING → GAME_OVER` |
| **Fisika Sederhana** | Gravitasi, velocity, delta position |
| **Collision Detection** | Axis-Aligned Bounding Box (AABB) via `SDL_HasIntersection` |
| **Object Pooling** | Vector of pipes yang di-reuse |
| **Event-Driven Input** | SDL Event loop untuk keyboard |

---

## 📖 Apa yang Akan Kamu Pelajari

Setelah mempelajari kode ini, kamu akan memahami:

1. **Bagaimana game loop bekerja** — otak dari setiap game
2. **Cara mensimulasikan gravitasi** — dengan rumus fisika sederhana `v += g; y += v`
3. **Cara mendeteksi tabrakan** — apakah dua kotak saling bertumpuk?
4. **Cara mengelola state game** — menu, gameplay, game over
5. **Bagaimana membuat objek muncul secara procedural** — pipe yang spawn-nya acak
6. **Cara merender grafis 2D** — menggambar persegi panjang, garis, dan bentuk dasar
7. **Cara mengatur framerate** — supaya game berjalan konsisten di semua komputer

---

## ✅ Prasyarat

Sebelum memulai, pastikan lingkungan kamu sudah siap:

| Software | Cek Instalasi | Catatan |
|----------|---------------|---------|
| **Compiler C++** | `g++ --version` | Minimal GCC 4.8 (C++11) |
| **SDL2 Development Libraries** | `sdl2-config --version` | Versi 2.0.x |
| **Make** | `make --version` | Build automation |
| **Git** (opsional) | `git --version` | Version control |

> 💡 **Untuk pengguna Windows:** Gunakan [MSYS2](https://www.msys2.org/) atau WSL untuk mendapatkan environment Linux-like.

---

## 🔧 Instalasi SDL2

<details>
<summary><b>🟢 Ubuntu / Debian</b></summary>

```bash
sudo apt update
sudo apt install libsdl2-dev
```
</details>

<details>
<summary><b>🔵 Arch Linux</b></summary>

```bash
sudo pacman -S sdl2
```
</details>

<details>
<summary><b>🍎 macOS (Homebrew)</b></summary>

```bash
brew install sdl2
```
</details>

<details>
<summary><b>🟦 Windows (MSYS2)</b></summary>

```bash
pacman -S mingw-w64-x86_64-SDL2
```
</details>

Verifikasi instalasi:
```bash
sdl2-config --version
# Output: 2.0.x
```

---

## 🚀 Cara Build & Menjalankan

```bash
# 1. Clone repositori
git clone https://github.com/thefulan123/simple_flappy_bird_using_cpp.git
cd simple_flappy_bird_using_cpp

# 2. Build project
make

# 3. Jalankan game
make run

# Atau jalankan binary langsung
./flappy_bird
```

**Perintah Makefile:**
| Perintah | Fungsi |
|----------|--------|
| `make` | Build game (compile + link) |
| `make run` | Build lalu jalankan |
| `make clean` | Hapus semua file hasil build |

**Output yang diharapkan:**
Jendela game berjudul **"Flappy Bird C++"** akan muncul dengan latar biru langit dan tulisan "FLAPPY BIRD" di tengah.

---

## 🎮 Cara Bermain

| Tombol | Aksi |
|--------|------|
| `SPACE` atau `↑` (Panah Atas) | **Mulai game** / **Flap (terbang)** / **Restart** |
| `ESC` | Keluar dari game |

### Aturan Main

1. **Burung terus jatuh** karena gravitasi — kamu harus menekan SPACE untuk membuatnya terbang
2. **Hindari pipa hijau** yang datang dari kanan — jangan sampai menyentuhnya
3. **Jangan menyentuh tanah** (garis batas bawah) atau **batas atas layar**
4. Setiap berhasil **melewati celah pipa**, kamu mendapat **1 poin**
5. Skor ditampilkan di bagian atas layar
6. Jika game over, tekan **SPACE** untuk memulai ulang

> 🎯 **Tips:** Tekan SPACE secara ritmis, jangan panik! Amati celah pipa dan atur timing flap-mu.

---

## 📁 Struktur Proyek

```
simple_flappy_bird_using_cpp/
│
├── Makefile               # Build system — otomatisasi kompilasi & linking
├── README.md              # Dokumentasi ini
│
├── src/                   # ✨ Semua source code ada di sini
│   ├── config.h           # Konfigurasi & konstanta global game
│   ├── bird.h             # Deklarasi class Bird
│   ├── bird.cpp           # Implementasi class Bird (fisika, render)
│   ├── pipe.h             # Deklarasi class PipeManager & struct Pipe
│   ├── pipe.cpp           # Implementasi PipeManager (spawn, gerak, collision)
│   ├── game.h             # Deklarasi class Game
│   ├── game.cpp           # Implementasi Game (game loop, state machine)
│   └── main.cpp           # Entry point — memulai eksekusi
│
├── build/                 # File objek (.o) — hasil kompilasi (auto-generated)
└── flappy_bird            # Binary executable (auto-generated)
```

> 📌 **Konsep penting:** Setiap file `.cpp` memiliki pasangan `.h` (header). Header berisi **deklarasi** (apa yang ada), file `.cpp` berisi **implementasi** (bagaimana cara kerjanya). Ini adalah prinsip **separasi of concerns** dalam C++.

---

## 🔍 Penjelasan Kode Mendalam

### `config.h` — Pusat Konfigurasi Game

**Apa itu?** File yang berisi semua konstanta yang mengatur perilaku game. Dengan memisahkan konfigurasi ke file terpisah, kita bisa mengubah perilaku game tanpa harus mengotak-atik logika di file lain.

```cpp
// Ukuran layar game
const int SCREEN_WIDTH  = 400;
const int SCREEN_HEIGHT = 600;
```

**Mengapa 400×600?** Proporsi 2:3 mirip dengan layar smartphone portrait, tempat Flappy Bird asli dimainkan.

```cpp
// Fisika burung
const float GRAVITY       = 0.5f;   // Pixel per frame^2
const float FLAP_STRENGTH = -8.0f;  // Pixel per frame (negatif = ke atas)
const float BIRD_MAX_VEL  = 10.0f;  // Kecepatan terminal (biar ga jatuh terlalu cepat)
```

> 🔬 **Penjelasan Fisika:**
> - Setiap frame, kecepatan burung bertambah sebesar `GRAVITY` (simulasi gravitasi)
> - Saat flap, velocity langsung di-set ke `FLAP_STRENGTH` (negatif = lompat ke atas)
> - `BIRD_MAX_VEL` membatasi kecepatan maksimum agar burung tidak jatuh dengan kecepatan tak terbatas

```cpp
// Pipa
const int PIPE_WIDTH      = 52;    // Lebar pipa dalam pixel
const int PIPE_GAP        = 150;   // Celah antara pipa atas dan bawah
const int PIPE_SPEED      = 3;     // Pixel per frame — kecepatan pipa bergerak
const int PIPE_SPAWN_INTERVAL = 120; // Berapa frame sekali pipa baru muncul
```

```cpp
// Warna (format SDL_Color: R, G, B, A)
const SDL_Color COLOR_SKY = {135, 206, 235, 255};  // Biru langit
const SDL_Color COLOR_BIRD = {255, 255, 0, 255};   // Kuning
const SDL_Color COLOR_PIPE = {0, 150, 0, 255};     // Hijau
```

---

### `bird.h` / `bird.cpp` — Fisika Burung

**Apa itu `class Bird`?** Sebuah blueprint untuk objek burung. Class ini bertanggung jawab atas:
1. Posisi burung di layar
2. Fisika gravitasi dan flap
3. Render (menggambar) burung

#### Konstruktor & Reset

```cpp
Bird::Bird() {
    reset();  // Set posisi awal
}

void Bird::reset() {
    x = BIRD_X;           // Posisi X tetap (80 pixel dari kiri)
    y = SCREEN_HEIGHT / 2; // Mulai dari tengah layar
    velocity = 0;          // Diam
    rotation = 0;          // Tidak miring
}
```

#### Fisika — Update Setiap Frame

```cpp
void Bird::update() {
    // 1. Gravitasi menarik burung ke bawah
    velocity += GRAVITY;

    // 2. Batasi kecepatan maksimum (terminal velocity)
    if (velocity > BIRD_MAX_VEL) velocity = BIRD_MAX_VEL;

    // 3. Posisi berubah berdasarkan kecepatan
    y += velocity;

    // 4. Efek visual: rotasi burung sesuai arah gerak
    if (velocity < -2) rotation = -25;  // Terbang ke atas → miring ke atas
    else if (velocity > 2) rotation = 25; // Jatuh → miring ke bawah
    else rotation = 0;
}
```

> 🧠 **Konsep Kunci — Euler Integration:**
> Rumus `velocity += acceleration; position += velocity` disebut **Euler integration** — metode numerik paling sederhana untuk mensimulasikan fisika. Setiap frame adalah satu "step" simulasi.

#### Render — Menggambar Burung

```cpp
void Bird::render(SDL_Renderer* renderer) {
    // Badan burung — kotak kuning
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &getRect());

    // Paruh — garis oranye dari tengah burung
    SDL_SetRenderDrawColor(renderer, 200, 100, 0, 255);
    SDL_RenderDrawLine(renderer, x + 10, y + 10, x + 28, y + 10);

    // Mata — kotak hitam kecil
    SDL_Rect eye = {static_cast<int>(x + 14), static_cast<int>(y + 4), 4, 4};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &eye);
}
```

> 🎨 **Catatan:** Karena ini adalah proyek pembelajaran, kita menggambar burung dengan bentuk geometris dasar (kotak, garis) tanpa menggunakan file gambar (sprite). Prinsip yang sama tetap berlaku jika nanti kamu ingin menggunakan texture.

---

### `pipe.h` / `pipe.cpp` — Sistem Pipa & Score

#### Struct Pipe

```cpp
struct Pipe {
    int x;       // Posisi X (bergerak ke kiri setiap frame)
    int gapY;    // Posisi Y celah (ditentukan random saat spawn)
    bool scored; // Apakah pipa ini sudah pernah memberikan score?
};
```

`struct` vs `class`: Di C++, `struct` sama dengan `class` — bedanya default access-nya `public`. Kita pakai `struct` untuk data sederhana tanpa method kompleks.

#### Spawn Pipa — Procedural Generation

```cpp
void PipeManager::update() {
    frameCounter++;

    // Apakah sudah waktunya spawn pipa baru?
    if (frameCounter >= PIPE_SPAWN_INTERVAL) {
        frameCounter = 0;

        // Tentukan posisi celah secara acak
        int gapY = std::rand() % (SCREEN_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 100) + 80;
        pipes.push_back({SCREEN_WIDTH, gapY, false});
    }
    // ...
}
```

**Logika celah acak:**
```
Rentang Y yang memungkinkan = SCREEN_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 100
                            = 600 - 80 - 150 - 100
                            = 270 pixel
Nilai gapY akan berada di antara 80 dan 350 (80 + 270)
```

#### Collision Detection — AABB (Axis-Aligned Bounding Box)

```cpp
bool PipeManager::checkCollision(const SDL_Rect& birdRect) const {
    for (const auto& pipe : pipes) {
        SDL_Rect topPipe = {pipe.x, 0, PIPE_WIDTH, pipe.gapY};
        SDL_Rect bottomPipe = {pipe.x, pipe.gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT};

        if (SDL_HasIntersection(&birdRect, &topPipe) ||
            SDL_HasIntersection(&birdRect, &bottomPipe)) {
            return true;  // TABRAKAN!
        }
    }
    return false;
}
```

> 🧠 **Konsep AABB:** Setiap objek dianggap sebagai kotak (bounding box). Dua kotak bertabrakan jika proyeksi sumbu X dan Y mereka saling tumpang tindih. Ini adalah metode collision detection paling sederhana dan paling cepat.

#### Scoring

```cpp
for (auto& pipe : pipeManager.getPipes()) {
    if (!pipe.scored && pipe.x + PIPE_WIDTH < BIRD_X) {
        pipe.scored = true;
        score++;
    }
}
```

**Logika:** Jika pipa sudah melewati posisi X burung (`pipe.x + PIPE_WIDTH < BIRD_X`) dan belum pernah dihitung (`!pipe.scored`), tambahkan score. Flag `scored` mencegah penghitungan ganda.

---

### `game.h` / `game.cpp` — Game State Machine

#### Game Loop

Ini adalah **jantung** dari setiap game:

```cpp
void Game::run() {
    running = true;
    lastFrameTime = SDL_GetTicks();

    while (running) {
        handleEvents();  // 1. Baca input pemain
        update();         // 2. Update logika game
        render();         // 3. Gambar ke layar

        // 4. Atur framerate — delay jika terlalu cepat
        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < 1000 / FPS) {
            SDL_Delay((1000 / FPS) - frameTime);
        }
    }
}
```

**Mengapa game loop penting?** Tanpa game loop, program akan berjalan sekali lalu selesai. Game loop membuat program terus berjalan (~60 kali per detik), memperbarui posisi objek, dan merender ulang layar, menciptakan ilusi gerakan.

#### State Machine

Game kita memiliki 3 state:

```
                    ┌─────────┐
                    │  MENU   │ ← Tampilan awal "FLAPPY BIRD"
                    └────┬────┘
                         │ SPACE ditekan
                         ▼
                    ┌─────────┐
                    │ PLAYING │ ← Gameplay aktif
                    └────┬────┘
                         │ Tabrakan / jatuh
                         ▼
                    ┌─────────┐
                    │GAME OVER│ ← Tampilkan skor akhir
                    └────┬────┘
                         │ SPACE ditekan → reset
                         └──→ kembali ke PLAYING
```

**Implementasi:**

```cpp
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Di handleEvents():
if (state == GameState::MENU || state == GameState::GAME_OVER) {
    if (tombol SPACE ditekan) {
        state = GameState::PLAYING;
        bird.reset();
        pipeManager.reset();
        score = 0;
    }
} else if (state == GameState::PLAYING) {
    if (tombol SPACE ditekan) {
        bird.flap();
    }
}
```

> 🧠 **Konsep State Machine:** State machine memisahkan perilaku game berdasarkan state. Logika menu, gameplay, dan game over tidak tercampur aduk — masing-masing punya "ruang" sendiri.

#### Event Handling

```cpp
void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;  // Tombol close (X) ditekan
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                case SDLK_UP:
                    // ... flap / start / restart
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
            }
        }
    }
}
```

---

### `main.cpp` — Entry Point

```cpp
int main(int, char*[]) {
    Game game;        // Buat objek game
    if (!game.init()) {  // Inisialisasi SDL, window, renderer
        return 1;
    }
    game.run();       // Mulai game loop
    return 0;
}
```

**Mengapa hanya 7 baris?** Semua logika kompleks sudah dibungkus di dalam class `Game`. Ini adalah prinsip **abstraksi** — `main.cpp` tidak perlu tahu detail bagaimana game bekerja, cukup panggil `init()` dan `run()`.

---

## 🔄 Alur Eksekusi Program

```
main()
  │
  ├─ Game game;            → Constructor: bird.reset(), pipeManager.reset()
  │
  ├─ game.init()           → SDL_Init(), SDL_CreateWindow(), SDL_CreateRenderer()
  │
  └─ game.run()            → GAME LOOP dimulai
        │
        ├─ while (running) {
        │   ├─ handleEvents()    → Baca input keyboard, update state
        │   ├─ update()          → Update posisi burung & pipa, deteksi collision
        │   │   ├─ bird.update()       → velocity += gravity; y += velocity
        │   │   ├─ pipeManager.update() → spawn, move, cleanup pipes
        │   │   └─ cek collision       → SDL_HasIntersection() atau boundary
        │   │
        │   ├─ render()          → Gambar semua objek
        │   │   ├─ SDL_RenderClear()
        │   │   ├─ pipeManager.render()
        │   │   ├─ bird.render()
        │   │   ├─ renderGround()
        │   │   ├─ renderScore()
        │   │   └─ SDL_RenderPresent()
        │   │
        │   └─ SDL_Delay()      → Atur framerate 60 FPS
        │}
        │
        └─ running = false  → Game loop berhenti
                                → Destructor: SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Quit()
```

---

## ⚙️ Kustomisasi Game

Salah satu tujuan pembelajaran adalah **experimentasi**. Coba ubah nilai-nilai di `src/config.h` dan lihat bagaimana game berubah:

| Variabel | Default | Efek jika diperkecil | Efek jika diperbesar |
|----------|---------|---------------------|---------------------|
| `SCREEN_WIDTH` | `400` | Layar lebih sempit | Layar lebih lebar |
| `SCREEN_HEIGHT` | `600` | Layar lebih pendek | Layar lebih tinggi |
| `GRAVITY` | `0.5f` | Burung jatuh lebih lambat (lebih mudah) | Burung jatuh lebih cepat (lebih susah) |
| `FLAP_STRENGTH` | `-8.0f` | Lompatan lebih rendah (lebih susah) | Lompatan lebih tinggi (lebih mudah) |
| `PIPE_GAP` | `150` | Celah sempit (lebih susah) | Celah lebar (lebih mudah) |
| `PIPE_SPEED` | `3` | Pipa bergerak lambat (lebih mudah) | Pipa bergerak cepat (lebih susah) |
| `PIPE_SPAWN_INTERVAL` | `120` | Pipa lebih sering muncul (lebih susah) | Pipa jarang muncul (lebih mudah) |
| `BIRD_MAX_VEL` | `10.0f` | Kecepatan jatuh terbatas | Kecepatan jatuh bisa lebih tinggi |

> 💡 **Saran belajar:**
> 1. Ubah `GRAVITY` jadi `0.8f` — rasakan perbedaan kesulitannya
> 2. Ubah `PIPE_GAP` jadi `100` — hampir mustahil!
> 3. Ubah `PIPE_SPAWN_INTERVAL` jadi `60` — pipa datang dua kali lebih cepat

---

## 🧪 Latihan untuk Kamu

Setelah memahami kode ini, coba tantang dirimu dengan latihan berikut:

### Level 1 — Mudah
- [ ] Ubah warna burung dari kuning menjadi merah
- [ ] Ubah warna langit dari biru menjadi oranye (sunset)
- [ ] Tambah kecepatan pipa setiap kali score bertambah 5

### Level 2 — Sedang
- [ ] Tambahkan efek **screen shake** saat game over
- [ ] Implementasikan **high score** yang disimpan dan ditampilkan
- [ ] Tambahkan suara menggunakan SDL_mixer (flutter sound saat flap, crash sound saat game over)

### Level 3 — Sulit
- [ ] Ganti burung kotak dengan **sprite** (gambar PNG) menggunakan SDL_image
- [ ] Tambahkan **particle effect** saat burung menabrak pipa
- [ ] Buat **mode 2 pemain** — dua burung di layar yang sama, masing-masing punya kontrol sendiri

> 🚀 **Ingin belajar lebih lanjut?** Setelah menguasai Flappy Bird, coba buat game lain:
> - **Space Invaders** — pelajari array of enemies, shooting mechanics
> - **Snake** — pelajari linked list, grid-based movement
> - **Pong** — pelajari AI sederhana, ball physics
> - **Platformer** — pelajari tilemap, scrolling camera, jumping physics

---

## 📄 Lisensi

Proyek ini dirilis di bawah lisensi **MIT**. Silakan:
- ✅ Clone dan fork repositori ini
- ✅ Gunakan kodenya untuk belajar
- ✅ Modifikasi dan distribusikan ulang
- ❌ Tidak ada batasan — gunakan untuk apapun

---

> **💪 Terakhir — Pesan dari Pengajar:**
>
> *"Kode ini mungkin sederhana, tapi di dalamnya terkandung konsep-konsep yang menjadi fondasi dari setiap game yang pernah kamu mainkan. Jangan puas hanya membuatnya berjalan — bongkar, ubah, rusak, lalu perbaiki lagi. Itulah satu-satunya cara untuk benar-benar belajar."*
>
> Selamat berkoding! 🚀
