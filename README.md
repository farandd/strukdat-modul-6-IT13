# Sistem Manajemen Rute Bus

Program ini memungkinkan Anda untuk menambahkan kota, mendefinisikan rute antar kota, dan menampilkan rute tersebut. Selain itu, program ini dapat menemukan dan menampilkan rute terpendek antara dua kota dan mencantumkan semua rute yang mungkin di antara keduanya.

## Penjelasan Kelas

### Kelas BusNode
Mewakili sebuah node dalam graf rute bus, yang sesuai dengan sebuah kota.

### Kelas BusGraph
Kelas dasar abstrak untuk graf bus.

### Kelas BusGraphAdjacencyMatrix
Mengimplementasikan graf bus menggunakan matriks ketetanggaan (adjacency matrix).

### Kelas BusTransRoute
Mewakili rute bus dari lokasi awal ke lokasi tujuan.

### Kelas BusRoute
Mewarisi dari `BusGraphAdjacencyMatrix` dan menyediakan fungsionalitas tambahan seperti menemukan rute terpendek dan menampilkan semua rute antara dua kota.

## Penjelasan Kode

### Fungsi Utama

Fungsi utama menyediakan antarmuka berbasis menu untuk berinteraksi dengan sistem manajemen rute bus. Ini memungkinkan pengguna untuk:
1. Menampilkan rute terpendek antara dua kota.
2. Menampilkan semua rute yang mungkin antara dua kota.
3. Menambahkan kota baru.
4. Menambahkan rute antara dua kota.
5. Menghapus rute antara dua kota.
6. Menampilkan matriks ketetanggaan dari graf rute bus.

### Pilihan Menu

#### 1. Tampilkan Rute Terpendek
Meminta pengguna untuk memasukkan lokasi awal dan akhir dan menampilkan rute terpendek antara keduanya.

#### 2. Tampilkan Semua Rute
Meminta pengguna untuk memasukkan lokasi awal dan akhir dan menampilkan semua rute yang mungkin antara keduanya.

#### 3. Tambah Kota
Meminta pengguna untuk memasukkan nama kota baru yang akan ditambahkan ke graf.

#### 4. Tambah Rute
Meminta pengguna untuk memasukkan nama dua kota untuk menambahkan rute di antara keduanya.

#### 5. Hapus Rute
Meminta pengguna untuk memasukkan nama dua kota untuk menghapus rute di antara keduanya.

#### 6. Tampilkan Matriks Ketetanggaan
Menampilkan matriks ketetanggaan yang mewakili graf rute bus.

### Fungsi dalam Kelas `BusRoute`

- `findNodeIndex(const string &nodeName)`: Menemukan indeks dari sebuah node berdasarkan namanya.
- `displayShortestRoute(const string &startLocation, const string &endLocation)`: Menampilkan rute terpendek antara dua kota menggunakan algoritma Dijkstra.
- `displayAllRoutes(const string &startLocation, const string &endLocation)`: Menampilkan semua rute yang mungkin antara dua kota menggunakan DFS.
- `deleteRoute(int node1Index, int node2Index)`: Menghapus rute antara dua kota.
- `addRoute(int node1Index, int node2Index)`: Menambahkan rute antara dua kota.
- `displayAdjacencyMatrix() const`: Menampilkan matriks ketetanggaan.
- `dfs(int currentNode, int targetNode, vector<int> &visited, vector<int> &path, bool &found)`: Fungsi pembantu untuk DFS.
- `minDistance(const vector<int> &distance, const vector<bool> &visited)`: Menemukan node dengan jarak minimum.
- `printShortestRoute(int start, int end, const vector<int> &parent)`: Mencetak rute terpendek.
- `dfsAllRoutes(int currentNode, int targetNode, vector<int> &visited, vector<int> &path)`: Fungsi pembantu untuk menemukan semua rute menggunakan DFS.
- `printRouteHeader() const`: Mencetak header untuk tampilan rute.
- `printDeletedRoute(int node1Index, int node2Index)`: Mencetak pesan yang menunjukkan rute telah dihapus.
- `printAddedRoute(int node1Index, int node2Index)`: Mencetak pesan yang menunjukkan rute telah ditambahkan.

## Contoh Output

```
-------------------------------------------------------
Bus Route Graph (Adjacency Matrix):
Jakarta connected to: Bandung - 
Bandung connected to: Jakarta - Cirebon - 
Cirebon connected to: Bandung - Pekalongan - 
Pekalongan connected to: Cirebon - Semarang - 
Semarang connected to: Pekalongan - Magelang - 
Magelang connected to: Semarang - Jogja - 
Jogja connected to: Magelang - Madiun - 
Madiun connected to: Jogja - Tulungagung - 
Tulungagung connected to: Madiun - Kediri - 
Kediri connected to: Tulungagung - Surabaya - 
Surabaya connected to: Kediri - Malang - 
Malang connected to: Surabaya - Jember - 
Jember connected to: Malang - 
-------------------------------------------------------

Menu:
1. Tampilkan Rute Terpendek
2. Tampilkan Semua Rute
3. Tambah Kota
4. Tambah Rute
5. Hapus Rute
6. Tampilkan Matriks Ketetanggaan
0. Keluar
Masukkan pilihan Anda: 1
Masukkan lokasi awal: Jakarta
Masukkan lokasi akhir: Jogja
-------------------------------------------------------
Rute Terpendek dari Jakarta ke Jogja: Jakarta - Bandung - Cirebon - Pekalongan - Semarang - Magelang - Jogja
-------------------------------------------------------

Menu:
1. Tampilkan Rute Terpendek
2. Tampilkan Semua Rute
3. Tambah Kota
4. Tambah Rute
5. Hapus Rute
6. Tampilkan Matriks Ketetanggaan
0. Keluar
Masukkan pilihan Anda: 2
Masukkan lokasi awal: Jakarta
Masukkan lokasi akhir: Jogja
-------------------------------------------------------
Semua rute yang mungkin dari Jakarta ke Jogja:
Rute: Jakarta - Bandung - Cirebon - Pekalongan - Semarang - Magelang - Jogja
-------------------------------------------------------

Menu:
1. Tampilkan Rute Terpendek
2. Tampilkan Semua Rute
3. Tambah Kota
4. Tambah Rute
5. Hapus Rute
6. Tampilkan Matriks Ketetanggaan
0. Keluar
Masukkan pilihan Anda: 0
Keluar...
```

## Penulis

- Farand Febriasnyah (5027231084)
