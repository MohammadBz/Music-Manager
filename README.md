# Music Library Data Structures Project

This repository contains a C++ console application built for a university data structures course. The app manages singers, songs, playlists, and a playlist playback queue using custom sparse set and linked list data structures.

## Tech Stack

- **Language:** C++
- **Standard Library:** `<iostream>`, `<string>`, `<math.h>`
- **Platform-specific header:** `<windows.h>` (used for console coloring on Windows)
- **Custom structures:** sparse set, linked list, queue

## Key Features

- Add, find, and delete singers and songs in a music library.
- Create playlists, add/remove songs, and display playlist contents sorted by release year.
- Manage a listening queue of playlists and show the current playlist.
- Search song lyrics for a word and count all word occurrences using suffix-array search logic.
- Store data using custom sparse set containers for singers, music, and playlists.

## Getting Started

### Prerequisites

- A C++ compiler such as `g++`, `clang++`, or Microsoft Visual C++.
- Windows command prompt or terminal environment.

### Build and Run

From the project root, compile the source files with a command like:

```bash
g++ src/app/main.cpp src/app/functions.cpp src/models/music.cpp src/models/singer.cpp src/models/playList.cpp src/datastructures/sparseSet.cpp src/datastructures/MSparseSet.cpp src/datastructures/PLSparseSet.cpp -o music_app
```

Then run the application:

```bash
./music_app
```

On Windows PowerShell or Command Prompt:

```powershell
.\music_app.exe
```

## Data Structures Overview

This project implements and demonstrates several key data structures covered in a computer science course:

### Sparse Set (sparseSet)
A space-efficient data structure for storing singers by ID. Uses two arrays:
- **Dense array:** Stores actual `singer*` pointers in contiguous memory.
- **Sparse array:** Maps singer ID to index in the dense array for O(1) lookup.

**Usage:** Manages all singers in the library. Supports insertion, deletion, and search in **O(1)** time.

### Music Sparse Set (MSparseSet)
Specialized sparse set for storing `music*` pointers indexed by music ID.
- Same two-array design as sparseSet for O(1) insert/delete/search.
- Includes `searchMusicShowOnly()` for filtering music by name.

**Usage:** Stores all songs in the library and enables fast lookups by music ID from anywhere in the application.

### Playlist Sparse Set (PLSparseSet)
Sparse set for storing `playList*` pointers indexed by playlist ID.
- Uses binary search in the dense array for additional search safety.
- Includes left-shift deletion to maintain contiguous storage.

**Usage:** Manages all playlists; allows instant retrieval of any playlist by ID.

### Linked List (linkList)
Generic template-based linked list with head pointer traversal.
- Supports `add()`, `remove()`, `search()`, and `display()` operations.
- Used for flexible storage where the maximum size isn't known in advance.

**Usage:**
- Stores lyrics (string) for each song with line-by-line access.
- Stores music IDs for each singer (which songs they have).
- Stores playlist IDs for each song (which playlists contain it).

### Generic Queue (QueueT)
Template-based circular queue using a fixed-size array.
- Supports `enqueue()` and `dequeue()` operations.
- Tracks front and rear pointers to manage the queue state.

**Usage:** Manages the listening queue of playlists. Users add playlists to the queue, and the app displays the currently playing (front) playlist.

## How They Work Together

1. **Singer Management:** `sparseSet` holds all singers. Each singer has a `linkList<int>` of music IDs.
2. **Music Management:** `MSparseSet` holds all songs. Each song has a `linkList<string>` for lyrics and a `linkList<int>` for playlist IDs.
3. **Playlist Management:** `PLSparseSet` holds all playlists. Each playlist has a sparse set of music IDs internally.
4. **Playback Queue:** `QueueT<int>` stores playlist IDs in a listening queue for sequential playback.

## Project Structure

```
Project/
  README.md                 # Project documentation
  src/
    app/
      main.cpp              # Console menu and command loop
      functions.cpp         # Application command handlers and helpers
    models/
      music.cpp             # Music entity implementation
      music.h               # Music entity interface
      singer.cpp            # Singer entity implementation
      singer.h              # Singer entity interface
      playList.cpp          # Playlist implementation and sorting logic
      playList.h            # Playlist interface
    datastructures/
      sparseSet.cpp         # Singer sparse set storage implementation
      sparseSet.h           # Singer sparse set interface
      MSparseSet.cpp        # Music sparse set storage implementation
      MSparseSet.h          # Music sparse set interface
      PLSparseSet.cpp       # Playlist sparse set storage implementation
      PLSparseSet.h         # Playlist sparse set interface
      linkList.h            # Generic linked list template
      QueueT.h              # Generic queue template
```

## Course Context

This project was created for a data structures course and demonstrates practical use of custom sparse sets, linked lists, and search algorithms in a small music management system.
