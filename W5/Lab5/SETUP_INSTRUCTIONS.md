# FreeGLUT Setup Instructions for Lab5

**Board does not show after building?** The project must use **vcpkg's freeglut** (Option 1 below). The manual freeglut package causes "fghGenBuffers is NULL" and the chess window never appears. Complete Option 1 once, then rebuild and run.

**This project is configured to use vcpkg only.** You must complete Option 1 below before the project will build.

## Option 1: Using vcpkg (Required)

Visual Studio will install freeglut from `vcpkg.json` when you build (manifest mode). You only need to install vcpkg and integrate it once.

### Step 1: Install vcpkg (if not already installed)

1. Open PowerShell as Administrator
2. Navigate to where you want to install vcpkg (e.g., `C:\dev\`)
3. Run:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

### Step 2: Integrate vcpkg with Visual Studio

```powershell
.\vcpkg integrate install
```

### Step 3: Install freeglut

From the vcpkg directory:
```powershell
.\vcpkg install freeglut:x64-windows
```

Or, if building for x86:
```powershell
.\vcpkg install freeglut:x86-windows
```

### Step 4: Restart Visual Studio

Close and reopen Visual Studio for the changes to take effect.

### Step 5: Build the Project

Open the Lab5 solution in Visual Studio and build (e.g. Build → Rebuild Solution). The first build may take a few minutes while vcpkg installs freeglut from `vcpkg.json`. vcpkg will also copy the required DLL next to your `.exe`, so the chess window should open when you run.

---

## Option 2: Manual Installation (Alternative)

If you prefer not to use vcpkg:

1. Download freeglut from: https://www.transmissionzero.co.uk/software/freeglut-devel/
2. Extract to `C:\Libraries\freeglut\freeglut\`
3. Ensure the structure is:
   ```
   C:\Libraries\freeglut\freeglut\
   ├── include\
   │   └── GL\
   │       └── glut.h
   └── lib\
       └── x64\
           └── freeglutd.lib (Debug) or freeglut.lib (Release)
   ```

---

## Troubleshooting

If you still get errors after following these steps:

1. **Check vcpkg installation**: Open Visual Studio Developer Command Prompt and run `vcpkg list`. If it says "vcpkg is not recognized", vcpkg is not installed or not in PATH.

2. **Verify vcpkg integration**: In Visual Studio, go to Tools → Options → vcpkg and ensure vcpkg is detected.

3. **Check build configuration**: Make sure you're building for the same architecture (x64 or x86) that you installed freeglut for.

4. **Clean and rebuild**: In Visual Studio, go to Build → Clean Solution, then Build → Rebuild Solution.

