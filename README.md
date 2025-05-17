# ATM Management System

> **Note:** This project aims to strengthen your C programming logic and test your ability to understand and improve existing code.

## 🎯 Objective

This project involves completing and improving an Automated Teller Machine (ATM) management system in **C language**. You won't be starting from scratch - a skeleton application is provided with basic functionalities such as:
- Login / Registration
- Account creation
- Listing existing accounts

The remaining functionalities must be **implemented by you**, while adhering to C programming best practices.

## 🗂 Project Structure

```
.
├── data
│   ├── records.txt  # Information about user accounts
│   └── users.txt    # Information about users
├── Makefile         # Project compilation
└── src
    ├── auth.c       # Authentication management
    ├── header.h     # Declarations and constants  
    ├── main.c       # Entry point
    └── system.c     # Main management functions
```

## 🧾 File Formats

**`users.txt`**  
Format: `id name password`  
Example:
```
0 Alice 1234password
1 Michel password1234
```

**`records.txt`**  
Format: `record_id user_id name account_id date country phone balance account_type`  
Example:
```
0 0 Alice 0 10/02/2020 german 986134231 11090830.00 current
1 1 Michel 2 10/10/2021 portugal 914134431 1920.42 savings
2 0 Alice 1 10/10/2000 finland 986134231 1234.21 savings
```

## ✅ Features to Implement

### 1. 🔐 New User Registration
- Username must be **unique**
- Data must be saved in `users.txt`

### 2. ✏️ Account Information Update
- User specifies the `account_id`
- They choose which field to modify: **country** or **phone number**
- Changes are saved in `records.txt`

### 3. 🔍 Account Details Inquiry
- User enters the `account_id` to view
- If the account type is:
  - `savings` → interest rate **7%**
  - `fixed01` (1 year) → **4%**
  - `fixed02` (2 years) → **5%**
  - `fixed03` (3 years) → **8%**
  - `current` → **No interest**
- Example message:
  > "You will get $5.97 as interest on day 10 of every month."

### 4. 💸 Transaction Processing
- Deposits or withdrawals are possible for `current` and `savings` accounts
- `fixed01`, `fixed02`, `fixed03` accounts **do not allow transactions**
- Changes are saved in `records.txt`

### 5. ❌ Account Deletion
- User can delete **their own accounts**
- The operation updates `records.txt`

### 6. 🔁 Account Ownership Transfer
- User specifies the `account_id` and the recipient's name
- Updates appropriate files

## ⭐ Bonus (optional)

- ⚠️ **Instant notification** when an account is transferred  
  *(using pipes and child processes for inter-process communication)*
- 💄 Improved terminal interface (TUI)
- 🔐 Password encryption
- 📁 Adding a **custom Makefile**
- 🗃️ Integration with a relational database (e.g., **SQLite**)

## 🔧 Technologies and Concepts Covered

- 🧠 **C** programming logic
- 📂 File manipulation
- 🧱 Data structures
- 💬 Terminal User Interface (TUI)
- 🔁 Memory management
- 🔀 Inter-process communication (`pipes`)

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make utility
- Basic understanding of C programming

### Installation

1. Clone this repository
2. Navigate to the project directory
3. Run `make` to compile the project
4. Execute with `./atm`

## ⚙️ Usage

After launching the application, follow the on-screen prompts to:
1. Register or log in
2. Access various functionalities through the main menu
3. Perform operations on accounts

## 📝 Development Guidelines

1. Maintain clean code structure and proper indentation
2. Add comments to explain complex logic
3. Handle errors gracefully
4. Free allocated memory properly to avoid leaks
5. Validate user inputs to prevent buffer overflows
6. Ensure atomicity of file operations to maintain data integrity

## 🧪 Testing

Test your implementation thoroughly with various scenarios:
- Account creation with different types
- Transaction processing with edge cases (insufficient funds, etc.)
- Account transfers between different users
- Error handling with invalid inputs

## 📚 Learning Outcomes

By completing this project, you will gain experience in:
- Working with file I/O in C
- Implementing user authentication
- Managing complex data structures
- Handling financial transaction logic
- Applying security best practices

