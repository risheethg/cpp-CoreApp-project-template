
# C++ Core-App Project Template

A clean, modular **C++ project template** that follows a **Core–App architecture**. Uses  **Premake5** for easy project generation across different platforms and IDEs. [The included `premake5.lua` file is **mainly** configured for **Windows Only**. You are free to modify the file to suit your OS as you see fit! ] 
This template is designed to help you quickly bootstrap new C++ projects with a structured setup that separates reusable engine/core code from application-specific logic.

---

## Architecture Overview

The repository follows a **Core–App structure**, where:

* **Core**
  A **static library** that contains reusable systems, utilities, and base engine components (like logging, event handling, or platform abstraction).

  * Independent of any specific application logic
  * Can be reused across multiple projects
  * Typically includes third-party dependencies (e.g., `spdlog`)

* **App**
  A **console application** that links against the Core library.
  * Implements the actual project-specific logic
  * Uses Core’s functionality to build upon

**Directory Layout:**

```
cpp-CoreApp-project-template/
│
├── Core
│    └── src
│        ├── Application
│        │    ├── Core
│        │    │   ├── Events
│        │    │   │   ├── Event.h
│        │    │   │   ├── MouseEvents.h
│        │    │   │   └── WindowEvents.h
│        │    │   │
│        │    │   ├── Layers
│        │    │   │   ├── Layer.cpp
│        │    │   │   ├── Layer.h
│        │    │   │   ├── LayerStack.cpp
│        │    │   │   └── LayerStack.h
│        │    │   │
│        │    │   ├── Log.cpp
│        │    │   └── Log.h
│        │    │
│        │    ├── Application.cpp
│        │    ├── Application.h
│        │    ├── EntryPoint.h
│        │    ├── pch.cpp
│        │    └── pch.h
│        │ 
│        └── CoreHeader.h
│
├── vendor/
│   └── spdlog/
│       └── ...
│
├── CoreHeader.h
│
├── App/
│   └── src/
│       └── SandBox.cpp
│
├── vendor/
│   └── bins/
│       └── premake/
│           └── premake5.lua    
│
├── GenerateProjet.bat
├── premake5.lua
└── README.md
```

---

## Requirements

Before setting up, make sure you have the following installed:

* **C++20-compatible compiler**
  (MSVC Recommended)
* **Visual Studio / Visual Studio Code / Xcode / Make** — depending on your build system

---

## Setup Instructions (Windows)

Follow these steps to set up and run the project:

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/cpp-CoreApp-project-template.git
cd cpp-CoreApp-project-template
```

### 2. Generate Project Files

Use the `GenerateProject.bat` file to generate your IDE or build system files [Set to Visual Studio 2022 by default].

```bash
GenerateProject.bat
```

You may modify/replace the file with one that's appropriate for your OS and IDE.

This will create a solution/workspace containing both **Core** and **App** projects.

---

### 3. Build the Project

Once the files are generated:

* **Visual Studio:** Open the `.sln` file and build both configurations (Debug/Release)

---

### 4. Run the App

After building, binaries will be located in:

```
bin/Debug-x64/App/
bin/Release-x64/App/
```

Run your compiled executable:

```bash
./bin/Debug-x64/App/App.exe
```

---

## Build Configuration Summary

* **Debug Mode**

  * `symbols On`
  * `defines _DEBUG`
  * Assertions enabled

* **Release Mode**

  * `optimize On`
  * `defines _RELEASE`
  * Assertions disabled

---

## Dependencies

* **[spdlog](https://github.com/gabime/spdlog)** — A fast C++ logging library
  Included under `Core/vendor/spdlog/`

---

## Customization

You can easily extend the template:

* Add your own modules inside `Core/src/Application/`
* Include more dependencies under `Core/vendor/`
* Create multiple apps linking against the same Core library
* Modify the `premake5.lua` to add configurations or new platforms

---
