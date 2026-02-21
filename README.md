# HTTP Server in C (Windows 10)

A simple HTTP server built **from scratch in C using Winsock**, without using external frameworks. This project demonstrates low-level socket programming and how HTTP works internally.

---

# 📌 Features

* Built completely from scratch in C
* Uses Windows Winsock API
* Handles HTTP requests from browser
* Sends valid HTTP responses
* Lightweight and beginner-friendly
* No external libraries required

---

# 📂 Project Structure

```
project/
│
├── Server.c        # Main HTTP server source code
├── README.md       # Documentation
└── .gitignore      # Ignored files
```

---

# ⚙️ Requirements (Windows 10)

You need:

* Windows 10
* MinGW (GCC compiler)
* Git Bash or Command Prompt

---

# 🛠 Step 1: Install MinGW (Compiler)

1. Download MinGW-w64
   https://www.mingw-w64.org/downloads/

2. Install it to:

```
C:\mingw64
```

3. Add to PATH:

```
C:\mingw64\bin
```

4. Verify installation:

```
gcc --version
```

---

# ▶️ Step 2: Compile the Server

Open Git Bash or Command Prompt in the project folder.

Git Bash example:

```
cd /c/Users/your-username/path/to/project
```

Compile:

```
gcc Server.c -o Server.exe -lws2_32
```

This creates:

```
Server.exe
```

---

# ▶️ Step 3: Run the Server

In Git Bash:

```
./Server.exe
```

In Command Prompt:

```
Server.exe
```

You should see:

```
Server running on port 8080...
```

---

# 🌐 Step 4: Test the Server

Open your browser and go to:

```
http://localhost:8080
```

You will see:

```
Hello from C server
```

---

# 🧠 How it Works (Architecture)

The server follows these steps:

```
Initialize Winsock
      ↓
Create Socket
      ↓
Bind Socket to Port
      ↓
Listen for Connections
      ↓
Accept Client Connection
      ↓
Receive HTTP Request
      ↓
Send HTTP Response
      ↓
Close Connection
```

---

# 🔧 Important Compile Flag

Always compile with:

```
-lws2_32
```

This links the Windows socket library.

---

# ❗ Troubleshooting

## Error: undefined reference to WSAStartup

Fix:

```
gcc Server.c -o Server.exe -lws2_32
```

---

## Error: command not found (Git Bash)

Run using:

```
./Server.exe
```

---

