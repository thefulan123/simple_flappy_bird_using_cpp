# 🐦 Flappy Bird C++

Game Flappy Bird sederhana yang dibuat dengan **C++** dan **SDL2**.

---

## 📋 Daftar Isi

- [Prasyarat](#prasyarat)
- [Cara Build & Run](#cara-build--run)
- [Cara Bermain](#cara-bermain)
- [Struktur Project](#struktur-project)
- [Penjelasan Kode](#penjelasan-kode)
- [Cara Push ke GitHub](#cara-push-ke-github)
- [Kustomisasi](#kustomisasi)

---

## Prasyarat

Pastikan kamu sudah menginstal:

| Software    | Cek Instalasi            |
|-------------|--------------------------|
| **g++**     | `g++ --version`          |
| **SDL2**    | `dpkg -l \| grep sdl2`    |
| **make**    | `make --version`         |
| **git**     | `git --version`          |

### Instalasi SDL2 (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install libsdl2-dev
```

### Instalasi SDL2 (Arch Linux)

```bash
sudo pacman -S sdl2
```

### Instalasi SDL2 (macOS)

```bash
brew install sdl2
```

---

## Cara Build & Run

```bash
# Masuk ke folder project
cd flappy-bird-cpp

# Build
make

# Jalankan
make run

# Atau langsung
./flappy_bird

# Bersihkan file build
make clean
```

---

## Cara Bermain

| Tombol          | Aksi                              |
|-----------------|-----------------------------------|
| `SPACE` / `↑`   | **Mulai game** / **Lompat** / **Restart** |
| `ESC`           | Keluar game                        |

**Aturan:**
- Tekan SPACE untuk membuat burung terbang ke atas
- Jangan sampai burung menyentuh pipa, tanah, atau batas atas layar
- Setiap berhasil melewati pipa = 1 poin
- Game over? Tekan SPACE lagi untuk restart

---

## Struktur Project

```
flappy-bird-cpp/
├── Makefile         # Build system
├── README.md        # Dokumentasi ini
├── flappy_bird      # Binary hasil build (setelah make)
├── src/
│   ├── config.h     # Konfigurasi & konstanta game
│   ├── bird.h       # Header class Bird
│   ├── bird.cpp     # Implementasi Bird
│   ├── pipe.h       # Header class PipeManager
│   ├── pipe.cpp     # Implementasi PipeManager
│   ├── game.h       # Header class Game
│   ├── game.cpp     # Implementasi Game (loop utama)
│   └── main.cpp     # Entry point
└── build/           # File object (.o) hasil kompilasi
```

---

## Penjelasan Kode

### `config.h` — Konfigurasi Game

File ini berisi semua konstanta yang mengatur perilaku game:

```cpp
const int SCREEN_WIDTH = 400;    // Lebar layar
const int SCREEN_HEIGHT = 600;   // Tinggi layar
const float GRAVITY = 0.5f;       // Gravitasi (pixel/frame^2)
const float FLAP_STRENGTH = -8.0f; // Kekuatan lompatan (negatif = ke atas)
const int PIPE_GAP = 150;         // Celah antar pipa atas-bawah
const int PIPE_SPEED = 3;         // Kecepatan pipa bergerak ke kiri
```

> **💡 Tips:** Kamu bisa mengubah nilai-nilai ini untuk mengubah kesulitan game!

### `bird.h` / `bird.cpp` — Burung

Class `Bird` menangani:

- **Posisi & Fisika:** Posisi burung di-*update* setiap frame dengan rumus:
  ```
  velocity += GRAVITY
  y += velocity
  ```
- **Flap:** Saat pemain menekan SPACE, `velocity` di-set ke `FLAP_STRENGTH` (negatif), sehingga burung terbang ke atas.
- **Render:** Menggambar burung sebagai kotak kuning dengan mata dan paruh.

### `pipe.h` / `pipe.cpp` — Pipa

Class `PipeManager` menangani:

- **Spawn:** Pipa baru dibuat setiap `PIPE_SPAWN_INTERVAL` frame (120 frame ≈ 2 detik) di posisi Y acak.
- **Gerakan:** Semua pipa bergerak ke kiri dengan kecepatan `PIPE_SPEED`.
- **Collision:** Deteksi tabrakan menggunakan `SDL_HasIntersection()`.
- **Scoring:** Pipa yang sudah dilewati burung akan memberi 1 poin.

### `game.h` / `game.cpp` — Game Loop

Class `Game` adalah inti dari game dengan **Game State Machine**:

```
MENU → PLAYING → GAME_OVER → MENU (restart)
```

- **handleEvents():** Membaca input keyboard
- **update():** Mengupdate posisi burung & pipa, deteksi tabrakan
- **render():** Menggambar semua objek ke layar

### `main.cpp` — Entry Point

Fungsi `main()` membuat objek `Game`, inisialisasi, lalu menjalankan loop utama.

---

## Cara Push ke GitHub

### 1. Buat Repository di GitHub

Buka [github.com/new](https://github.com/new), buat repo baru (misal: `flappy-bird-cpp`), **jangan centang** "Add a README" karena sudah punya.

### 2. Push dari Terminal

```bash
# Pindah ke folder project
cd /mnt/e/Project\ 2\ \(Software\)/flappy-bird-cpp

# Init git
git init

# Tambah semua file
git add .

# Commit pertama
git commit -m "feat: Flappy Bird C++ with SDL2"

# Tambah remote (ganti USER dengan username GitHub kamu)
git remote add origin https://github.com/USER/flappy-bird-cpp.git

# Push
git branch -M main
git push -u origin main
```

### 3. Update selanjutnya

```bash
git add .
git commit -m "pesan perubahan"
git push
```

---

## Kustomisasi

| Variabel di `config.h` | Default     | Fungsi                          |
|------------------------|-------------|---------------------------------|
| `SCREEN_WIDTH`         | `400`       | Lebar jendela                   |
| `SCREEN_HEIGHT`        | `600`       | Tinggi jendela                  |
| `GRAVITY`              | `0.5f`      | Gravitasi (makin besar = makin berat) |
| `FLAP_STRENGTH`        | `-8.0f`     | Kekuatan flap (makin negatif = makin tinggi) |
| `PIPE_GAP`             | `150`       | Celah pipa (makin kecil = makin susah) |
| `PIPE_SPEED`           | `3`         | Kecepatan pipa (makin besar = makin cepat) |
| `PIPE_SPAWN_INTERVAL`  | `120`       | Interval spawn pipa (frame)     |

---

## Lisensi

Project ini bebas digunakan untuk belajar. Silakan clone, fork, dan modifikasi!

---

**Selamat belajar coding! 🚀**
