# 🚗 Parking Management System (C++ Console Application)

## 📌 Overview
This is a simple **Parking Management System** built in C++ that allows users to:
- Park vehicles
- Generate unique ticket numbers
- View currently parked vehicles
- Save and load parking records from a file

The system uses **file handling** to persist data and simulates a real-world parking workflow through a console-based interface.

---

## ✨ Features

### ✅ Implemented Features
- **Vehicle Parking System**
  - Input vehicle type and plate number
  - Automatically records time-in
  - Generates a unique ticket number

- **Ticket Generation**
  - Format: `TKT-<timestamp>-<sequence>`
  - Ensures uniqueness using system time

- **View Parked Vehicles**
  - Displays all vehicles currently parked
  - Filters using `isParked` flag

- **File Persistence**
  - Saves records to `parking_records.txt`
  - Loads existing records on startup

- **Loading Animation**
  - Simulated progress bar for ticket generation

- **Console UI Enhancements**
  - Colored text using ANSI escape codes
  - Structured menu system

---

### ⚠️ Experimental / Incomplete Features
- View Parked Cars (basic implementation, still improving UI)
  
### ❌ Not Yet Implemented
- Exit Vehicle (fee calculation & timeout handling)
- Search Vehicle
- Input validation improvements

---

## 🧱 Project Structure

### 🔹 `struct Vehicle`
Stores parking data:
- `timeIn` → Entry time
- `timeOut` → Exit time
- `plateNum` → Vehicle plate number
- `ticketNum` → Unique ticket ID
- `vehicleType` → Type of vehicle
- `fee` → Parking fee
- `isParked` → Status (true/false)

---

## ⚙️ Functions

| Function | Description |
|--------|-------------|
| `parkvehicle()` | Handles vehicle entry |
| `generateTicket()` | Creates unique ticket number |
| `viewParked()` | Displays parked vehicles |
| `savetoFile()` | Saves latest record to file |
| `loadFromFile()` | Loads records from file |
| `generatingLoad()` | Simulates loading animation |
| `delay()` | Adds delay for UI smoothness |

---

## 💾 File Storage

- File used: `parking_records.txt`
- Format (space-separated):
